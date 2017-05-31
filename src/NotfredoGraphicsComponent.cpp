#include "NotfredoGraphicsComponent.h"
#include "Notfredo.h"

NotfredoGraphicsComponent::NotfredoGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 10, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sp = sprites["Idle"];
}

NotfredoGraphicsComponent::~NotfredoGraphicsComponent()
{
}

void NotfredoGraphicsComponent::Update(GameObject* obj, float dt)
{
	Notfredo* n = (Notfredo*) obj;
	
	mirror = (n->facing == GameObject::LEFT);
	if(n->physicsComponent.velocity.x == 0)
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
