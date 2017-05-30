#include "NotfredoGraphicsComponent.h"
#include "Notfredo.h"

NotfredoGraphicsComponent::NotfredoGraphicsComponent(std::string baseName_):
	baseName(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sp = sprites["Idle"];
}

NotfredoGraphicsComponent::~NotfredoGraphicsComponent()
{
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
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

void NotfredoGraphicsComponent::Render(Vec2 position)
{
	sp->Render(position);
}

Vec2 NotfredoGraphicsComponent::GetSize()
{
	return sp->GetSize();
}

void NotfredoGraphicsComponent::UpdateSprite(GameObject* obj, std::string sprite)
{
	Notfredo* n = (Notfredo*) obj;
	
	if(sp != sprites[sprite])
	{
		int w = sp->GetWidth();
		int h = sp->GetHeight();
		sp = sprites[sprite];
		if(n->facing == GameObject::RIGHT)
			n->box.x += (w-sp->GetWidth());
		//l->box.x += (w-sp->GetWidth())/2;
		n->box.y += h-sp->GetHeight();
		n->box.SetWH(GetSize());
		sp->SetFrame(1);
	}
}
