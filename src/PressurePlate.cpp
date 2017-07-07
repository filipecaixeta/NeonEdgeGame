#include "PressurePlate.h"
#include "Camera.h"

PressurePlate::PressurePlate(int x, int y, Interactive* d):
	Interactive(x,y,"PressurePlate")
{
	name = "PressurePlate";
	door = d;
}

PressurePlate::~PressurePlate()
{

}

void PressurePlate::Trigger()
{
	if(Active())
	{
		door->On();
	}
	else
	{
		door->Off();
	}
}

void PressurePlate::NotifyObjectCollision(GameObject* other)
{
	On();
}

void PressurePlate::Update(TileMap* map, float dt)
{
	Interactive::Update(map,dt);
	Trigger();
	Off();
}
