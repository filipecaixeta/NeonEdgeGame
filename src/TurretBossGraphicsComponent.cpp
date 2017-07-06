#include "TurretBossGraphicsComponent.h"

#include "TurretBoss.h"

TurretBossGraphicsComponent::TurretBossGraphicsComponent(std::string baseName_):
	GraphicsComponent(baseName_)
{
	AddSprite(baseName, "Idle", 8, 80);

	sp = sprites["Idle"];
	surface = surfaces["Idle"];
}

TurretBossGraphicsComponent::~TurretBossGraphicsComponent(){

}

void TurretBossGraphicsComponent::Update(GameObject* obj, float dt){
	mirror = (obj->facing == GameObject::LEFT);

	TurretBoss* a = (TurretBoss*) obj;

	sp->Mirror(mirror);
	sp->Update(dt);
}