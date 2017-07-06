#include "CeilingEnemyGraphicsComponent.h"

CeilingEnemyGraphicsComponent::CeilingEnemyGraphicsComponent(std::string baseName_):
    GraphicsComponent(baseName_)
{
    AddSprite(baseName,"Idle",6,80);
    sp = sprites["Idle"];
    surface = surfaces["Idle"];
}

CeilingEnemyGraphicsComponent::~CeilingEnemyGraphicsComponent()
{

}

void CeilingEnemyGraphicsComponent::Update(GameObject* obj, float dt)
{
    UpdateSprite(obj, "Idle");
    sp->Update(dt);
}



