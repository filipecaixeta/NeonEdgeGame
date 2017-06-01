#include "LancelotGraphicsComponent.h"
#include "Lancelot.h"

LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",8,80);
	AddSprite(baseName,"Running",8,80);
	AddSprite(baseName,"Crouching",4,80);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent()
{
}

void LancelotGraphicsComponent::Update(Character* obj, float dt)
{
	mirror = (obj->facing == GameObject::LEFT);
	if(obj->Crouching())
	{
		UpdateSprite(obj, "Crouching");
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
