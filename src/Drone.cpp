#include "Drone.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Drone::Drone(int x, int y):
	Player(x,y)
{
	inputComponent = new DroneInputComponent();
	graphicsComponent = new DroneGraphicsComponent("Drone");
	physicsComponent.SetKinetic(true);
	name = "Drone";
	box.SetWH(graphicsComponent->GetSize());
	active = false;
}

Drone::~Drone()
{

}

void Drone::UpdateTimers(float dt)
{

}

void Drone::Update(TileMap* map, float dt){
	UpdateTimers(dt);
	inputComponent->Update(this,dt);
	if(active == true)
		physicsComponent.Update(this,map,dt);
	else{
		box.x = StageState::GetPlayer()->box.x;
		box.y = StageState::GetPlayer()->box.y - 8;
	}
	if(OutOfBounds(map))
		SetPosition(Vec2(269,544));
	graphicsComponent->Update(this,dt);

}

void Drone::SetActive(bool active){
	this->active = active;
}

bool Drone::GetActive(){
	return active;
}