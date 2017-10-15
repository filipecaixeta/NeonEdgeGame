// Copyright (c) 2017 Neon Edge Game.

#include "InteractiveGraphicsComponent.h"
#include "Interactive.h"
#include "Rect.h"

InteractiveGraphicsComponent::InteractiveGraphicsComponent(std::string baseNameParam):
       GraphicsComponent(baseNameParam) {
    AddSprite(baseName, "Off", 1, 0);
    AddSprite(baseName, "On", 1, 0);
    sprite = sprites["Off"];
    surface = surfaces["Off"];
}

InteractiveGraphicsComponent::~InteractiveGraphicsComponent() {
}

void InteractiveGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    Interactive* interactive = (Interactive*) gameObject;

    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    if (interactive->Active()) {
        UpdateSprite(gameObject, "On");
    } else {
        UpdateSprite(gameObject, "Off");
    }

    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);
}
