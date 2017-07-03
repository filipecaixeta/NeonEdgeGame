#include "BoxSpawner.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

BoxSpawner::BoxSpawner(int x, int y)
{
	spawn = new Box(x, y, "window.png");
	StageState::AddObject(spawn);
	name = "BoxSpawner";
	BoxSpawner::x = x;
	BoxSpawner::y = y;
}

BoxSpawner::~BoxSpawner()
{

}

bool BoxSpawner::IsDead()
{
	return false;
}

void BoxSpawner::NotifyObjectCollision(GameObject* other)
{

}

void BoxSpawner::Update(TileMap* map, float dt)
{
	if (spawn->hitpoints == 1)
	{
		spawn->hitpoints = 0;
		spawn = new Box(x, y, "window.png");
		StageState::AddObject(BoxSpawner::spawn);
	}
}

void BoxSpawner::Render()
{

}
