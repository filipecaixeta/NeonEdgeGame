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
#include "Logger.h"

/**
 * Objective: it constructs the Interactive Graphics Component object.
 *
 * @param String title - responsable to the game window title.
 * @return instace of Interactive Graphics Component.
 */
InteractiveGraphicsComponent::InteractiveGraphicsComponent(std::string baseNameParam):
       GraphicsComponent(baseNameParam) {
    assert(baseName[0] != '\0');

    AddSprite(baseName, "Off", 1, 0);
    Log::instance.info("Interactive Graphics Component] added 'Off' to sprite.");

    AddSprite(baseName, "On", 1, 0);
    Log::instance.info("Interactive Graphics Component] added 'On' to sprite.");

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
    assert(interactive != nullptr);
    Log::instance.info("[Interactive Graphics Component] Interactive successfully instantiated.");

    if (interactive->Active()) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "On");
    } else {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Off");
    }

    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    Log::instance.info("[Interactive Graphics Component] Character direction changed to left.");

    sprite->Mirror(characterLeftDirection); // Direction update of character sprite.
    Log::instance.info("[Interactive Graphics Component] Character sprite setted to left.");

    sprite->Update(deltaTime);
    Log::instance.info("[Interactive Graphics Component] Interactive sprite updates.");

    assert(gameObject != nullptr);
}
