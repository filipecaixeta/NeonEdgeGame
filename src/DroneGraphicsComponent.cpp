#include "DroneGraphicsComponent.h"
#include "Drone.h"

DroneGraphicsComponent::DroneGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",8,80);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

DroneGraphicsComponent::~DroneGraphicsComponent()
{

}

void DroneGraphicsComponent::Update(Character* obj, float dt)
{
	Drone* l = (Drone*) obj;

	mirror = (obj->facing == GameObject::LEFT);
	if(l->Attacking())
	{
		UpdateSprite(obj, "Attacking");
	}
	else if(l->Crouching())
	{
		UpdateSprite(obj, "Crouching");
	}
	else if(obj->footing == GameObject::AIRBORNE)
	{
		UpdateSprite(obj, "Jumping");
	}
	else if(obj->physicsComponent.velocity.x == 0)
	{
		UpdateSprite(obj, "Idle");
	}
	else
	{
		UpdateSprite(obj, "Running");
	}

	sp->Mirror(mirror);
	sp->Update(dt);
}
