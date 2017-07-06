#include "Drone.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"

Drone::Drone(ItensManager* itemManager, int x, int y):
	Player(itemManager,x,y),
	active(false)
{
	name = "Drone";
	inputComponent = new DroneInputComponent();
	graphicsComponent = new DroneGraphicsComponent("Drone");
	physicsComponent.SetKinetic(true);
	box.SetWH(graphicsComponent->GetSize());
}

Drone::~Drone()
{

}

void Drone::Activate(bool on)
{
	active = on;
}

bool Drone::Active()
{
	return active;
}

void Drone::UpdateTimers(float dt)
{

}

void Drone::Update(TileMap* map, float dt)
{
	UpdateTimers(dt);
	if (StageState::GetPlayer() == nullptr)
	{
		isDead = true;
		return;
	}
	inputComponent->Update(this,dt);
	if(active == true)
	{
		physicsComponent.Update(this,map,dt);
	}
	else
	{
		facing = StageState::GetPlayer()->facing;
		if(StageState::GetPlayer()->facing == LEFT)
			box.x = StageState::GetPlayer()->box.x+StageState::GetPlayer()->box.w-box.w;
		else
			box.x = StageState::GetPlayer()->box.x;
		box.y = StageState::GetPlayer()->box.y - 5;
	}
	if(OutOfBounds(map))
		SetPosition(Vec2(269,544));
	graphicsComponent->Update(this,dt);
}
