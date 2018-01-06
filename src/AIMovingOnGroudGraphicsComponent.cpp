// Copyright (c) 2017 Neon Edge Game.

#include "AIMovingOnGroudGraphicsComponent.h"

AIMovingOnGroudGraphicsComponent::AIMovingOnGroudGraphicsComponent(std::string baseName_):
        GraphicsComponent(baseName_) {
    AddSprite(baseName, "Idle", 1, 80);
    AddSprite(baseName, "Running", 6, 80);
    AddSprite(baseName, "Dying", 10, 100);
    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

AIMovingOnGroudGraphicsComponent::~AIMovingOnGroudGraphicsComponent() {
}

void AIMovingOnGroudGraphicsComponent::Update(GameObject *gameObject,
                                                                   float deltaTime) {
    Character *character = (Character *) gameObject;
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    if (character->physicsComponent.velocity.x == 0) {
        UpdateSprite(gameObject, "Idle");
    } else {
        UpdateSprite(gameObject, "Running");
    }

    if (gameObject->dieTimer.IsRunning()) {
        UpdateSprite(gameObject, "Dying");
    } else {
        // It does nothing.
    }

    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);
}
