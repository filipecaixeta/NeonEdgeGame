/**
 * Copyright 2017 Neon Edge Game
 * File Name: InteractiveGraphicsComponent.cpp
 * Header File Name: InteractiveGraphicsComponent.h
 * Class Name: InteractiveGraphicsComponent
 * Objective: it manages interactive graphics component.
 */

#include "InteractiveGraphicsComponent.h"
#include <assert.h>
#include "Interactive.h"
#include "Rect.h"


/**
 * Objective: it constructs the Interactive Graphics Component object.
 *
 * @param String title - responsable to the game window title.
 * @return instace of Interactive Graphics Component.
 */
InteractiveGraphicsComponent::InteractiveGraphicsComponent(std::string baseNameParam):
       GraphicsComponent(baseNameParam) {
    AddSprite(baseName, "Off", 1, 0);
    AddSprite(baseName, "On", 1, 0);
    sprite = sprites["Off"];
    surface = surfaces["Off"];
}

InteractiveGraphicsComponent::~InteractiveGraphicsComponent() {
}

/**
 * Objective: it updates the Interactive Graphics Component object.
 *
 * @param GameObject *gameObject - game object to update sprite status.
 * @param float deltaTime - amount of time to update sprite time.
 * @return none.
 */
void InteractiveGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    assert(gameObject != nullptr);
    assert(FLOAT_MIN_SIZE <= deltaTime && deltaTime <= FLOAT_MAX_SIZE);

    Interactive *interactive = (Interactive *) gameObject;
    if (interactive->Active()) {
        UpdateSprite(gameObject, "On");
    } else {
        UpdateSprite(gameObject, "Off");
    }

    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);

    assert(gameObject != nullptr);
}
