#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Button.h"
#include "j1Fonts.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if(App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if(App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// --- Loading UI config file ---
	pugi::xml_document	config_file;
	pugi::xml_node		config;

	config=App->LoadConfig(config_file, "UI_Elems.xml");
	App->gui->DeployUI(config);
	
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if(App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if(origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	// Gui ---
	
	// -------
	if(App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for(uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}


void j1Scene::ONhover(j1UI_Element & element)
{
	ELEMENTS TYPE = element.GetType();

	switch (TYPE)
	{
		case ELEMENTS::PANEL:

		break;

		case ELEMENTS::BUTTON:
			element.Getrects()->current_rect = element.Getrects()->rect_hover;
		break;

		case ELEMENTS::LABEL:
			//element.ShapeLabel(element.GetTexts()->text2);
		break;
	}

	element.GetBooleans()->hovering = true;
}

void j1Scene::OFFhover(j1UI_Element & element)
{
	ELEMENTS TYPE = element.GetType();

	switch (TYPE)
	{
		case ELEMENTS::PANEL:

		break;

		case ELEMENTS::BUTTON:
			element.Getrects()->current_rect = element.Getrects()->rect_normal;
		break;

		case ELEMENTS::LABEL:
			//element.ShapeLabel(element.GetTexts()->text);
		break;
	}

	element.GetBooleans()->hovering = false;
}

void j1Scene::ONclick(j1UI_Element & element)
{
	ELEMENTS TYPE = element.GetType();

	switch (TYPE)
	{
		case ELEMENTS::PANEL:

		break;

		case ELEMENTS::BUTTON:
			element.Getrects()->current_rect = element.Getrects()->rect_click;
		break;

		case ELEMENTS::LABEL:

		break;
	}

	element.GetBooleans()->clicking = true;
}

void j1Scene::OFFclick(j1UI_Element & element)
{
	ELEMENTS TYPE = element.GetType();

	switch (TYPE)
	{
		case ELEMENTS::PANEL:

		break;

		case ELEMENTS::BUTTON:
			element.Getrects()->current_rect = element.Getrects()->rect_normal;
		break;

		case ELEMENTS::LABEL:

		break;
	}

	element.GetBooleans()->clicking = false;
}
void j1Scene::ONdrag(j1UI_Element & element)
{
	ELEMENTS TYPE = element.GetType();

	switch (TYPE)
	{
	case ELEMENTS::PANEL:
		element.position.x = App->gui->mouse_pos.x - App->gui->drag_Ref.x;
		element.position.y = App->gui->mouse_pos.y - App->gui->drag_Ref.y;
		break;

	case ELEMENTS::BUTTON:
		element.position.x = App->gui->mouse_pos.x - App->gui->drag_Ref.x;
		element.position.y = App->gui->mouse_pos.y - App->gui->drag_Ref.y;
		break;

	case ELEMENTS::LABEL:
		element.position.x = App->gui->mouse_pos.x - App->gui->drag_Ref.x;
		element.position.y = App->gui->mouse_pos.y - App->gui->drag_Ref.y;
		break;
	}
}

void j1Scene::ONFocus()
{
	if (App->gui->focus_index < App->gui->UIelements.count())
	{
		App->gui->focus = App->gui->UIelements.At(App->gui->focus_index)->data;
		App->gui->Colorize(*App->gui->focus->GetTexture(), 255, 120, 120, 120);
		if (App->gui->focus_index != 0)
		App->gui->DeColorize(*App->gui->UIelements.At(App->gui->focus_index)->prev->data->GetTexture());
		App->gui->focus_index++;
	}
	else
	{
		App->gui->DeColorize(*App->gui->UIelements.At(App->gui->focus_index - 1)->data->GetTexture());
		App->gui->focus_index = 0;
	}
}
