#include "Door.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

Door::Door(int x, int y, TileMap* world, std::string sprite, bool locked)
{
	name = "Door";
	sp = Sprite(sprite);
	Vec2 size = sp.GetSize();
	box.SetXY(Vec2(x,y));
	box.SetWH(size);
	Door::locked = locked;
}

Door::~Door()
{

}

bool Door::IsDead()
{
	return dead;
}

void Door::NotifyObjectCollision(GameObject* other)
{
	if(locked)
	{
		if(1)
		{
			
		}
	}
	else
	{
		dead = true;
		
	}
}

void Door::Update(TileMap* map, float dt)
{

}

void Door::Render()
{
	sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
