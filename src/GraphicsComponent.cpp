#include <GraphicsComponent.h>
#include <Camera.h>

GraphicsComponent::GraphicsComponent(std::string baseName_):
	sp(new Sprite()),
	box(),
	baseName(baseName_)
{
	sprites.emplace("Idle", new Sprite(baseName+"Idle.png", 8, 120, true));
	sprites.emplace("Running", new Sprite(baseName+"Running.png", 8, 120, true));
	sp = sprites["Idle"];
}

GraphicsComponent::~GraphicsComponent()
{
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
}

void GraphicsComponent::Update(GameObject *obj, float dt)
{
	if (obj->speed.x < 0)
	{
		UpdateSprite("Running");
		mirror = true;
	}
	else if (obj->speed.x > 0)
	{
		UpdateSprite("Running");
		mirror = false;
	}
	else if (obj->speed.x == 0.0f)
	{
		UpdateSprite("Idle");
	}

	sp->Mirror(mirror);
	sp->Update(dt);

}

void GraphicsComponent::Render(Vec2 position)
{
	sp->Render(position);
}

Vec2 GraphicsComponent::GetSize()
{
	return sp->GetSize();
}

void GraphicsComponent::UpdateSprite(std::string sprite)
{
	if(sp != sprites[sprite])
	{
		int w = sp->GetWidth();
		int h = sp->GetHeight();
		sp = sprites[sprite];
		box.x += (w-sp->GetWidth())/2;
		box.y += h-sp->GetHeight();
		box.SetWH(sp->GetSize());
	}
}
