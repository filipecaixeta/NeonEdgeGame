#include "BoxSpawner.h"
#include "Camera.h"
#include "InputManager.h"
#include "StageState.h"
#include "Character.h"
#include "Room.h"

BoxSpawner::BoxSpawner(int x, int y)
{
	spawn = new Box(x, y);
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
	if (spawn->GetHealth() == 1)
	{
		spawn->Kill();
		spawn = new Box(x, y);
		StageState::AddObject(BoxSpawner::spawn);
	}
}

void BoxSpawner::Render()
{

}
