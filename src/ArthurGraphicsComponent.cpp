#include "ArthurGraphicsComponent.h"

#include "Arthur.h"

ArthurGraphicsComponent::ArthurGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName, "Idle", 8, 80);
	AddSprite(baseName, "Dash", 6, 80);
	AddSprite(baseName, "Punch", 8, 80);
	AddSprite(baseName, "Slash", 8, 80);

	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

ArthurGraphicsComponent::~ArthurGraphicsComponent(){

}

void ArthurGraphicsComponent::Update(Character* obj, float dt){
	mirror = (obj->facing == GameObject::LEFT);

	Arthur* a = (Arthur*) obj;

	if(a->GetState() == IDLE)
		UpdateSprite(obj, "Idle");
	if(a->GetState() == DASHINGRIGHT || a->GetState() == DASHINGLEFT)
		UpdateSprite(obj, "Dash");
	if(a->GetState() == SLASHING)
		UpdateSprite(obj, "Slash");
	if(a->GetState() == PUNCHING)
		UpdateSprite(obj, "Punch");

	sp->Mirror(mirror);
	sp->Update(dt);
}