#include "ProjectileGraphicsComponent.h"
#include "Projectile.h"
#include "Rect.h"

ProjectileGraphicsComponent::ProjectileGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName,"Projectile",4,80);
	sp = sprites["Projectile"];
	surface = surfaces["Projectile"];
}

ProjectileGraphicsComponent::~ProjectileGraphicsComponent()
{

}

void ProjectileGraphicsComponent::Update(GameObject* obj, float dt)
{
	mirror = (obj->facing == GameObject::LEFT);
	
	sp->Mirror(mirror);
	sp->Update(dt);
}
