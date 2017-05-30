#include "LancelotGraphicsComponent.h"
#include "Lancelot.h"

LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseName_):
	baseName(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sprites.emplace("Crouching", new Sprite(baseName+"Crouching.png", 4, 120, true, false));
	sp = sprites["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent()
{
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
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
	Lancelot* l = (Lancelot*) obj;
	
	if(sp != sprites[sprite])
	{
		int w = sp->GetWidth();
		int h = sp->GetHeight();
		sp = sprites[sprite];
		if(l->facing == GameObject::RIGHT)
			l->box.x += (w-sp->GetWidth());
		//l->box.x += (w-sp->GetWidth())/2;
		l->box.y += h-sp->GetHeight();
		l->box.SetWH(GetSize());
		sp->SetFrame(1);
	}
}
