#include "GraphicsComponent.h"
#include "Rect.h"
#include "StageState.h"
#include "Character.h"

GraphicsComponent::GraphicsComponent(std::string baseName_):
	sp(new Sprite()),
	baseName(baseName_)
{

}

GraphicsComponent::~GraphicsComponent()
{
	sp = nullptr;
	for(auto& i : sprites)
		delete i.second;
	sprites.clear();

	surface = nullptr;
	for(auto& i : surfaces)
		delete i.second;
	surfaces.clear();
}

void GraphicsComponent::Render(Vec2 position, float angle)
{
	sp->RenderScreenPosition(position,angle);
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
		
		if(obj->footing == GameObject::LEFT_WALLED)
			obj->box.x += 0;
		else if(obj->footing == GameObject::RIGHT_WALLED)
			obj->box.x += w-sp->GetWidth();
		else
			obj->box.x += (w-sp->GetWidth())/2;
		obj->box.y += h-sp->GetHeight();
		obj->box.SetWH(GetSize());
		
		if(!sp->Loops())
			sp->SetFrame(1);
		
		if(obj->IsCharacter())
		{
			Character* c = (Character*) obj;
			c->physicsComponent.TileFix(c, StageState::GetCurrentRoom()->GetMap(), GameObject::LEFT);	
			c->physicsComponent.TileFix(c, StageState::GetCurrentRoom()->GetMap(), GameObject::RIGHT);
		}
	}
}

void GraphicsComponent::AddSprite(std::string baseName, std::string name, int frameCount, int frameTime, bool loops)
{
	surfaces.emplace(name,Resources::GetSurface(baseName+name+".png"));
	sprites.emplace(name,new Sprite(baseName+name+".png", frameCount, frameTime, true, loops));
}
