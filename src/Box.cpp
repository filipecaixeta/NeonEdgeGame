#include "Box.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"
/*
Box::Box(int x, int y, TileMap* world, std::string sprite)
{
	name = "Box";
	sp = Sprite(sprite);
	Vec2 size = sp.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
}

Box::~Box()
{

}

bool Box::IsDead()
{
	return false;
}

void Box::Trigger(TileMap* map) {
	
}

void Box::NotifyObjectCollision(GameObject* other)
{
	if(other->Is("Gallahad") || other->Is("Lancelot"))
	{
				if(other->facing == RIGHT)
				{
					box.x+=4;
				}
				else
				{
					box.x-=4;
				}
		}
}

void Box::Update(TileMap* map, float dt)
{
	Trigger(map);
	box.y+=
}

void Box::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
*/