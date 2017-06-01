#include "GraphicsComponent.h"
#include "Rect.h"

GraphicsComponent::GraphicsComponent(std::string baseName_):
	sp(new Sprite()),
	baseName(baseName_)
{
}

GraphicsComponent::~GraphicsComponent()
{
	for(auto& i: sprites)
		delete i.second;
	sprites.clear();
}

void GraphicsComponent::Render(Vec2 position)
{
	sp->Render(position);
}

Vec2 GraphicsComponent::GetSize()
{
	return sp->GetSize();
}

SDL_Surface *GraphicsComponent::GetSurface()
{
	return surface;
}

SDL_Rect GraphicsComponent::GetClip()
{
	return sp->GetClip();
}

bool GraphicsComponent::GetMirror()
{
	return mirror;
}

void GraphicsComponent::UpdateSprite(GameObject* obj, std::string sprite)
{
	if(sp != sprites[sprite])
	{
		int w = sp->GetWidth();
		int h = sp->GetHeight();
		sp = sprites[sprite];
		surface = surfaces[sprite];
		obj->box.x += (w-sp->GetWidth())/2;
		obj->box.y += h-sp->GetHeight();
		obj->box.SetWH(GetSize());
		sp->SetFrame(1);
	}
}

void GraphicsComponent::AddSprite(std::string baseName, std::string name, int frameCount, int frameTime)
{
	surfaces.emplace(name,Resources::GetSurface(baseName+name+".png"));
	sprites.emplace(name, new Sprite(baseName+name+".png", frameCount, frameTime, true));
}
