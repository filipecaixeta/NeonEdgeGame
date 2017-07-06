#include "DroneGraphicsComponent.h"
#include "Drone.h"

DroneGraphicsComponent::DroneGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",6,80);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

DroneGraphicsComponent::~DroneGraphicsComponent()
{

}

void DroneGraphicsComponent::Update(GameObject* obj, float dt)
{
	Drone* l = (Drone*) obj;

	mirror = (obj->facing == GameObject::LEFT);
	
	UpdateSprite(obj, "Idle");

	sp->Mirror(mirror);
	sp->Update(dt);
}
