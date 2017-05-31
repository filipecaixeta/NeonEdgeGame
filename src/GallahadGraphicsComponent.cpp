#include "GallahadGraphicsComponent.h"
#include "Gallahad.h"
#include "Rect.h"

GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	surfaces.emplace("Idle",Resources::GetSurface(baseName+"Idle.png"));
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 80, true));
	surfaces.emplace("Running",Resources::GetSurface(baseName+"Running.png"));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 80, true));
	surfaces.emplace("Jumping",Resources::GetSurface(baseName+"Jumping.png"));
	sprites.emplace("Jumping", new Sprite(baseName+"Jumping.png", 8, 80, true, false));
	surfaces.emplace("Crouching",Resources::GetSurface(baseName+"Crouching.png"));
	sprites.emplace("Crouching", new Sprite(baseName+"Crouching.png", 4, 80, true, false));
	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

GallahadGraphicsComponent::~GallahadGraphicsComponent()
{
}

void GallahadGraphicsComponent::Update(GameObject* obj, float dt)
{
	Gallahad* g = (Gallahad*) obj;
	
	mirror = (g->facing == GameObject::LEFT);
	if(g->Crouching())
	{
		UpdateSprite(obj, "Crouching");
	}
	else if(g->footing == GameObject::AIRBORNE)
	{
		UpdateSprite(obj, "Jumping");
	}
	else if(g->physicsComponent.velocity.x == 0)
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
