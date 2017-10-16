// Copyright (c) 2017 Neon Edge Game.

#include "NotfredoGraphicsComponent.h"
#include "Notfredo.h"

NotfredoGraphicsComponent::NotfredoGraphicsComponent(std::string baseNameParam):
        GraphicsComponent(baseNameParam) {
    AddSprite(baseName, "Idle", 10, 80);
    AddSprite(baseName, "Running", 8, 80);
    AddSprite(baseName, "Attacking", 6, 60);
    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

NotfredoGraphicsComponent::~NotfredoGraphicsComponent() {
}

void NotfredoGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    Character *character = (Character*) gameObject;
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    if (character->Attacking()) {
        UpdateSprite(gameObject, "Attacking");
    } else if (character->physicsComponent.velocity.x == 0) {
        UpdateSprite(gameObject, "Idle");
    } else {
        UpdateSprite(gameObject, "Running");
    }

    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);
}
