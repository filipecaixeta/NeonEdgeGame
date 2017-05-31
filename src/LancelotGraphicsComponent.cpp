#include "LancelotGraphicsComponent.h"
#include "Lancelot.h"

LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sprites.emplace("Crouching", new Sprite(baseName+"Crouching.png", 4, 120, true, false));
	sp = sprites["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent()
{
}

void LancelotGraphicsComponent::Update(GameObject* obj, float dt)
{
	Lancelot* l = (Lancelot*) obj;
	
	mirror = (l->facing == GameObject::LEFT);
	if(l->Crouching())
	{
		UpdateSprite(obj, "Crouching");
	}
	else if(l->physicsComponent.velocity.x == 0)
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
