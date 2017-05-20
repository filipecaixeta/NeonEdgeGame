#include "LancelotGraphicsComponent.h"

LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseName_):
	sp(new Sprite()),
	baseName(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sp = sprites["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent()
{
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
}

void LancelotGraphicsComponent::Update(GameObject *obj, float dt)
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

	sp->Mirror(mirror);
	sp->Update(dt);
}

void LancelotGraphicsComponent::Render(Vec2 position)
{
	sp->Render(position);
}

Vec2 LancelotGraphicsComponent::GetSize()
{
	return sp->GetSize();
}

void LancelotGraphicsComponent::UpdateSprite(GameObject* obj, std::string sprite)
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
