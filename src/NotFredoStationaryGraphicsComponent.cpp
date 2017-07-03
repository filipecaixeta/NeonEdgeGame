#include "NotFredoStationaryGraphicsComponent.h"
#include "NotFredoStationary.h"

NotFredoStationaryGraphicsComponent::NotFredoStationaryGraphicsComponent(std::string baseName_):
    GraphicsComponent(baseName_)
{
    AddSprite(baseName,"Idle",10,80);
    AddSprite(baseName,"Running",8,80);
    sp = sprites["Idle"];
    surface = surfaces["Idle"];
}

NotFredoStationaryGraphicsComponent::~NotFredoStationaryGraphicsComponent()
{

}

void NotFredoStationaryGraphicsComponent::Update(Character *obj, float dt)
{

        mirror = (obj->facing == GameObject::LEFT);
        if(obj->physicsComponent.velocity.x == 0)
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
