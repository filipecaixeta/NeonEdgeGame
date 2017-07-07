#include "BoxSpawner.h"
#include "StageState.h"

BoxSpawner::BoxSpawner(int x, int y)
{
	name = "BoxSpawner";
	box.SetXY(Vec2(x,y));
	spawn = nullptr;
}

BoxSpawner::~BoxSpawner()
{

}

void BoxSpawner::Update(TileMap* map, float dt)
{
	if(!spawn)
	{
		spawn = new Box(box.x,box.y);
		StageState::AddObject(BoxSpawner::spawn);
	}
	if(spawn->GetHealth() == 1)
	{
		spawn->Kill();
		spawn = new Box(box.x,box.y);
		StageState::AddObject(BoxSpawner::spawn);
	}
}

void BoxSpawner::Render()
{

}
