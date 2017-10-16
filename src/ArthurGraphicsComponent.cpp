// Copyright (c) 2017 Neon Edge Game.

#include "ArthurGraphicsComponent.h"
#include "Arthur.h"

ArthurGraphicsComponent::ArthurGraphicsComponent(std::string baseName_):
        GraphicsComponent(baseName_) {
    AddSprite(baseName, "Idle", 8, 80);
    AddSprite(baseName, "Dash", 6, 80);
    AddSprite(baseName, "Punch", 8, 80);
    AddSprite(baseName, "Slash", 8, 80);

    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

ArthurGraphicsComponent::~ArthurGraphicsComponent() {
}

void ArthurGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);

    Arthur *arthur = (Arthur *) gameObject;

    if (arthur->GetState() == IDLE) {
        UpdateSprite(gameObject, "Idle");
    } else {
        // It does nothing.
    }

    if (arthur->GetState() == DASHINGRIGHT || arthur->GetState() == DASHINGLEFT) {
        UpdateSprite(gameObject, "Dash");
    } else {
        // It does nothing.
    }

    if (arthur->GetState() == SLASHING) {
        UpdateSprite(gameObject, "Slash");
    } else {
        // It does nothing.
    }

    if (arthur->GetState() == PUNCHING) {
        UpdateSprite(gameObject, "Punch");
    } else {
        // It does nothing.
    }

    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);
}
