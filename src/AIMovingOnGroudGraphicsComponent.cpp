#include "AIMovingOnGroudGraphicsComponent.h"

AIMovingOnGroudGraphicsComponent::AIMovingOnGroudGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",1,80);
	AddSprite(baseName,"Running",6,80);
	AddSprite(baseName,"Dying",10,100);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

AIMovingOnGroudGraphicsComponent::~AIMovingOnGroudGraphicsComponent()
{

}

void AIMovingOnGroudGraphicsComponent::Update(GameObject* obj, float dt)
{
	Character* c = (Character*) obj;
	mirror = (obj->facing == GameObject::LEFT);
	if(c->physicsComponent.velocity.x == 0)
	{
		UpdateSprite(obj, "Idle");
	}
	else
	{
		UpdateSprite(obj, "Running");
	}

	if (obj->dieTimer.IsRunning())
	{
		UpdateSprite(obj, "Dying");
	}

	sp->Mirror(mirror);
	sp->Update(dt);
}
