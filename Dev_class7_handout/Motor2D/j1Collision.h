//#ifndef __j1Collision_H__
//#define __j1Collision_H__
//
//#define MAX_COLLIDERS 300
//
//#include "j1Module.h"
//#include "SDL/include/SDL_rect.h"
//#include "p2DynArray.h"
//
//enum COLLIDER_TYPE
//{
//	COLLIDER_NONE = -1,
//	COLLIDER_FLOOR,
//	COLLIDER_PLAYER,
//
//	COLLIDER_MAX
//
//};
//
//struct Collider
//{
//	SDL_Rect rect;
//	bool to_delete = false;
//	COLLIDER_TYPE type;
//	j1Module* callback = nullptr;
//
//	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
//		rect(rectangle),
//		type(type),
//		callback(callback)
//	{}
//
//	void SetPos(int x, int y)
//	{
//		rect.x = x;
//		rect.y = y;
//	}
//
//	bool CheckCollision(const SDL_Rect& r) const;
//
//};
//
//class j1Collision : public j1Module
//{
//public:
//
//	j1Collision();
//	~j1Collision();
//
//	bool PreUpdate();
//	bool Update(float dt);
//	bool PostUpdate();
//	bool CleanUp();
//
//	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
//	void DebugDraw();
//
//
//private:
//
//	/*p2DynArray <Collider*> colliders;*/
//	Collider* colliders[MAX_COLLIDERS];
//	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
//	bool debug = false;
//};
//
//#endif // __j1Collision_H__