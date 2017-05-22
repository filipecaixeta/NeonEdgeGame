#include "GallahadGraphicsComponent.h"

GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseName_):
	sp(new Sprite()),
	baseName(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sprites.emplace("Jumping", new Sprite(baseName+"Jumping.png", 8, 120, true));
	sp = sprites["Idle"];
}

GallahadGraphicsComponent::~GallahadGraphicsComponent()
{
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
}

void GallahadGraphicsComponent::Update(GameObject *obj, float dt)
{
	if (obj->speed.x < 0)
	{
		UpdateSprite(obj, "Running");
		mirror = true;
	}
	else if (obj->speed.x > 0)
	{
		UpdateSprite(obj, "Running");
		mirror = false;
	}
	else
	{
		UpdateSprite(obj, "Idle");
	}
	if(obj->jumping)
	{
		UpdateSprite(obj, "Jumping");
		mirror = (obj->facing == GameObject::LEFT);
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
	if(sp != sprites[sprite])
	{
		int w = sp->GetWidth();
		int h = sp->GetHeight();
		sp = sprites[sprite];
		obj->box.x += (w-sp->GetWidth())/2;
		obj->box.y += h-sp->GetHeight();
		obj->box.SetWH(GetSize());
	}
}
