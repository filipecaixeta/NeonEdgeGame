#include "LancelotGraphicsComponent.h"
#include "Lancelot.h"

LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",8,80);
	AddSprite(baseName,"Running",8,80);
	AddSprite(baseName,"Crouching",4,80,true);
	AddSprite(baseName,"Jumping",8,80,true);
	AddSprite(baseName,"Attacking",11,80);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent()
{

}

void LancelotGraphicsComponent::Update(Character* obj, float dt)
{
	Lancelot* l = (Lancelot*) obj;

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
