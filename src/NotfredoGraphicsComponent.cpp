#include "NotfredoGraphicsComponent.h"
#include "Notfredo.h"

NotfredoGraphicsComponent::NotfredoGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",10,80);
	AddSprite(baseName,"Running",8,80);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

NotfredoGraphicsComponent::~NotfredoGraphicsComponent()
{
}

void NotfredoGraphicsComponent::Update(GameObject* obj, float dt)
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

	sp->Mirror(mirror);
	sp->Update(dt);
}
