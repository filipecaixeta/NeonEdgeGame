#include "PressurePlateOneTime.h"
#include "Camera.h"

PressurePlateOneTime::PressurePlateOneTime(int x, int y, Interactive* d):
	Interactive(x,y,"PressurePlateOneTime")
{
	name = "PressurePlateOneTime";
	door = d;
}

PressurePlateOneTime::~PressurePlateOneTime()
{

}

void PressurePlateOneTime::Trigger()
{
	if(Active())
	{
		door->On();
	}
}

void PressurePlateOneTime::NotifyObjectCollision(GameObject* other)
{
	if(other->IsPlayer())
		On();
}

void PressurePlateOneTime::Update(TileMap* map, float dt)
{
	Interactive::Update(map,dt);
	Trigger();
}
