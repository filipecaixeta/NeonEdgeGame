#include "Drone.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Attack.h"
#include "Melee.h"
#include "Projectile.h"

Drone::Drone(ItensManager* itemManager, int x, int y):
	Player(itemManager,x,y),
	active(false),
	dead(false)
{
	inputComponent = new DroneInputComponent();
	graphicsComponent = new DroneGraphicsComponent("Drone");
	physicsComponent.SetKinetic(true);
	name = "Drone";
	box.SetWH(graphicsComponent->GetSize());
}

Drone::~Drone()
{

}

void Drone::UpdateTimers(float dt)
{

}

void Drone::Update(TileMap* map, float dt){
	UpdateTimers(dt);

	if (StageState::GetPlayer()==nullptr)
	{
		dead=true;
		return;
	}
	inputComponent->Update(this,dt);
	if(active == true){
		physicsComponent.Update(this,map,dt);
		clamp(physicsComponent.velocity.x,-0.4f,0.4f);
		clamp(physicsComponent.velocity.y,-0.4f,0.4f);
	}
	else{
		box.x = StageState::GetPlayer()->box.x;
		box.y = StageState::GetPlayer()->box.y - 8;
	}
	if(OutOfBounds(map))
		SetPosition(Vec2(269,544));
	graphicsComponent->Update(this,dt);

}

bool Drone::IsDead()
{
	return dead;
}

void Drone::SetActive(bool active){
	this->active = active;
}

bool Drone::GetActive(){
	return active;
}

bool Drone::Is(std::string type)
{
	return type=="Drone";
}
