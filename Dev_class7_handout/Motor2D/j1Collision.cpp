//#include "j1Collision.h"
//#include "j1App.h"
//#include "j1Input.h"
//#include "j1Render.h"
//#include "j1Player.h"
//#include "p2Log.h"
//
//
//j1Collision::j1Collision()
//{
//	name.create("collision");
//
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//		colliders[i] = nullptr;
//
//	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER] = false;
//	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
//
//	matrix[COLLIDER_PLAYER][COLLIDER_FLOOR] = true;
//	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
//
//
//}
//
//j1Collision::~j1Collision()
//{
//}
//
//bool j1Collision::PreUpdate()
//{
//
//	bool ret = true;
//
//	// Remove all colliders scheduled for deletion
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
//		{
//			delete colliders[i];
//			colliders[i] = nullptr;
//		}
//	}
//
//
//	return ret;
//}
//
//bool j1Collision::Update(float dt)
//{
//
//	int playertouched = 0;
//
//	// Calculate collisions
//	Collider* c1;
//	Collider* c2;
//
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		// skip empty colliders
//		if (colliders[i] == nullptr)
//			continue;
//
//		c1 = colliders[i];
//
//
//		// avoid checking collisions already checked
//		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
//		{
//			// skip empty colliders
//			if (colliders[k] == nullptr)
//				continue;
//
//			c2 = colliders[k];
//
//			if (c1->CheckCollision(c2->rect) == true)
//			{
//				if (c1->type == COLLIDER_PLAYER || c2->type == COLLIDER_PLAYER)
//				{
//					playertouched++;
//				}
//
//				if (matrix[c1->type][c2->type] && c1->callback)
//					c1->callback->OnCollision(c1, c2);
//
//				if (matrix[c2->type][c1->type] && c2->callback)
//					c2->callback->OnCollision(c2, c1);
//			}
//		}
//	}
//
//	if (playertouched == 0 && App->player->stateplayer != JUMPING)
//	{
//		/*App->player->playercolliding = false;*/
//		App->player->stateplayer = FALLING;
//	}
//
//
//	return true;
//}
//
//bool j1Collision::PostUpdate()
//{
//	DebugDraw();
//
//	return true;
//}
//
//
//bool j1Collision::CleanUp()
//{
//	LOG("Freeing all colliders");
//
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		if (colliders[i] != nullptr)
//		{
//			delete colliders[i];
//			colliders[i] = nullptr;
//		}
//	}
//
//	return true;
//
//}
//
//Collider * j1Collision::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module * callback)
//{
//	Collider* ret = nullptr;
//
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		if (colliders[i] == nullptr)
//		{
//			ret = colliders[i] = new Collider(rect, type, callback);
//			break;
//		}
//	}
//
//	return ret;
//}
//
//void j1Collision::DebugDraw()
//{
//
//	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
//		debug = !debug;
//
//	if (debug == false)
//		return;
//
//	Uint8 alpha = 80;
//	for (uint i = 0; i < MAX_COLLIDERS; ++i)
//	{
//		if (colliders[i] == nullptr)
//			continue;
//
//		switch (colliders[i]->type)
//		{
//		case COLLIDER_NONE: // white
//			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
//			break;
//		case COLLIDER_FLOOR: // blue
//			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
//			break;
//		case COLLIDER_PLAYER: // green
//			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
//			break;
//
//		}
//	}
//}
//
//
//bool Collider::CheckCollision(const SDL_Rect & r) const
//{
//	return (rect.x < r.x + r.w &&
//		rect.x + rect.w > r.x &&
//		rect.y < r.y + r.h &&
//		rect.h + rect.y > r.y);
//
//	// between argument "r" and property "rect"
//}
