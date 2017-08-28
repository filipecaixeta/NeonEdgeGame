// Copyright 2013 Thomas Park.

#include "DroneGraphicsComponent.h"
#include "Drone.h"

DroneGraphicsComponent::DroneGraphicsComponent(std::string baseName_):
        GraphicsComponent(baseName_) {
    AddSprite(baseName, "Idle", 6, 80);
    AddSprite(baseName, "Running", 6, 80);
    AddSprite(baseName, "Attacking", 6, 80);
    sp = sprites["Idle"];
    surface = surfaces["Idle"];
}

DroneGraphicsComponent::~DroneGraphicsComponent() {
}

void DroneGraphicsComponent::Update(GameObject* obj, float dt) {
    Drone *d = (Drone *) obj;
    mirror = (obj->facing == GameObject::LEFT);

    if (d->Attacking()) {
        UpdateSprite(obj, "Attacking");
    } else if (d->physicsComponent.velocity.x == 0) {
        UpdateSprite(obj, "Idle");
    } else {
        UpdateSprite(obj, "Running");
    }

    sp->Mirror(mirror);
    sp->Update(dt);
}
