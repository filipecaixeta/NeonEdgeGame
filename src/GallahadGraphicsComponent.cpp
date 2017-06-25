#include "GallahadGraphicsComponent.h"
#include "Gallahad.h"
#include "Rect.h"

GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Idle",8,80);
	AddSprite(baseName,"Running",8,80);
	AddSprite(baseName,"Crouching",4,80,true);
	AddSprite(baseName,"Jumping",8,80,true);
	AddSprite(baseName,"Shot",4,80, true);
	AddSprite(baseName,"RunningShot",8,80);
	AddSprite(baseName,"JumpingShot",8,80, true);
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

GallahadGraphicsComponent::~GallahadGraphicsComponent()
{

}

void GallahadGraphicsComponent::Update(Character* obj, float dt)
{
	Gallahad* g = (Gallahad*) obj;

	mirror = (obj->facing == GameObject::LEFT);
	if(g->Shooting())
	{
		if(obj->physicsComponent.velocity.x != 0)
			UpdateSprite(obj, "RunningShot");
		else if(obj->footing == GameObject::AIRBORNE)
			UpdateSprite(obj, "JumpingShot");
		else
			UpdateSprite(obj, "Shot");
	}
	else if(g->Crouching())
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
	
	if(g->Hiding())
	{
		sp->SetTransparency(0.3);
	}
	else
	{
		sp->SetTransparency(1);
	}

	sp->Mirror(mirror);
	sp->Update(dt);
}
