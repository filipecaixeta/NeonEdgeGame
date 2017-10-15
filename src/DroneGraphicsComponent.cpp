// Copyright (c) 2017 Neon Edge Game.

#include "DroneGraphicsComponent.h"
#include "Drone.h"

DroneGraphicsComponent::DroneGraphicsComponent(std::string baseNameParam):
        GraphicsComponent(baseNameParam) {
    AddSprite(baseName, "Idle", 6, 80);
    AddSprite(baseName, "Running", 6, 80);
    AddSprite(baseName, "Attacking", 6, 80);
    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

DroneGraphicsComponent::~DroneGraphicsComponent() {
}

void DroneGraphicsComponent::Update(GameObject* gameObject, float deltaTime) {
    Drone *drone = (Drone *) gameObject;
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);

    if (drone->Attacking()) {
        UpdateSprite(gameObject, "Attacking");
    } else if (drone->physicsComponent.velocity.x == 0) {
        UpdateSprite(gameObject, "Idle");
    } else {
        UpdateSprite(gameObject, "Running");
    }

    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);
}
