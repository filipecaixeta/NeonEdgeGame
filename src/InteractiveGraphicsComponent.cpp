#include "InteractiveGraphicsComponent.h"
#include "Interactive.h"
#include "Rect.h"

InteractiveGraphicsComponent::InteractiveGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Off",1,0);
	AddSprite(baseName,"On",1,0);
	sp = sprites["Off"];
	surface = surfaces["Off"];
}

InteractiveGraphicsComponent::~InteractiveGraphicsComponent()
{

}

void InteractiveGraphicsComponent::Update(GameObject* obj, float dt)
{
	Interactive* i = (Interactive*) obj;

	mirror = (obj->facing == GameObject::LEFT);
	if(i->Active())
	{
		UpdateSprite(obj, "On");
	}
	else
	{
		UpdateSprite(obj, "Off");
	}
	
	sp->Mirror(mirror);
	sp->Update(dt);
}
