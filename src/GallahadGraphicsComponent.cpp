#include "GallahadGraphicsComponent.h"
#include "Gallahad.h"
#include "Rect.h"

GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseName_):
	sp(new Sprite()),
	baseName(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sprites.emplace("Jumping", new Sprite(baseName+"Jumping.png", 8, 60, true));
	sp = sprites["Idle"];
}

GallahadGraphicsComponent::~GallahadGraphicsComponent()
{
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
}

void GallahadGraphicsComponent::Update(GameObject* obj, float dt)
{
	Gallahad* g = (Gallahad*) obj;
	
	mirror = (g->facing == GameObject::LEFT);
	if(g->physicsComponent.velocity.x == 0)
	{
		UpdateSprite(obj, "Idle");
	}
	else
	{
		UpdateSprite(obj, "Running");
	}
	if(g->footing == GameObject::AIRBORNE || g->jumping)
	{
		UpdateSprite(obj, "Jumping");
		mirror = (g->facing == GameObject::LEFT);
	}

	sp->Mirror(mirror);
	sp->Update(dt);
}

void GallahadGraphicsComponent::Render(Vec2 position)
{
	sp->Render(position);
}

Vec2 GallahadGraphicsComponent::GetSize()
{
	return sp->GetSize();
}

void GallahadGraphicsComponent::UpdateSprite(GameObject* obj, std::string sprite)
{
	Gallahad* g = (Gallahad*) obj;
	if(sp != sprites[sprite])
	{
		int w = sp->GetWidth();
		int h = sp->GetHeight();
		sp = sprites[sprite];
		g->box.x += (w-sp->GetWidth())/2;
		g->box.y += h-sp->GetHeight();
		g->box.SetWH(GetSize());
	}
}
