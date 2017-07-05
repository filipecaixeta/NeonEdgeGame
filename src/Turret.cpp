#include "Turret.h"

#include "AIMovingOnGroudGraphicsComponent.h"

Turret::Turret(int x, int y):
	Character(x,y)
{
	graphicsComponent = new AIMovingOnGroudGraphicsComponent("Turret");
	name = "Turret";
	box.SetWH(graphicsComponent->GetSize());
	attackCD.SetLimit(0);
}

void Turret::Update(TileMap* map, float dt)
{
	UpdateAI(map,dt);
	Character::Update(map,dt);
}

void Turret::UpdateAI(TileMap* map, float dt)
{
//	map->
//	physicsComponent.velocity.x = 0.003*dt;
}
