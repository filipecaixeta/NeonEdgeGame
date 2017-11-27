/**
 * Copyright 2017 Neon Edge Game
 * File Name: NotfredoGraphicsComponent.cpp
 * Header File Name: NotfredoGraphicsComponent.h
 * Class Name: NotfredoGraphicsComponent
 * Objective: it manages Notfredo graphics component.
 */

#include "NotfredoGraphicsComponent.h"
#include "Notfredo.h"
#include "Logger.h"
#include <assert.h>

/**
 * Objective: it constructs the Notfredo Graphics Component object.
 *
 * @param String baseNameParam - responsable to the insert the default name base.
 * @return instace of Notfredo Graphics Component.
 */
NotfredoGraphicsComponent::NotfredoGraphicsComponent(std::string baseNameParam):
        GraphicsComponent(baseNameParam) {
    assert(baseName[0] != '\0');

    AddSprite(baseName, "Idle", 10, 80);
    Log::instance.info("[Notfredo Graphics Component] added 'Idle' to sprite.");

    AddSprite(baseName, "Running", 8, 80);
    Log::instance.info("[Notfredo Graphics Component] added 'Running' to sprite.");

    AddSprite(baseName, "Attacking", 6, 60);
    Log::instance.info("[Notfredo Graphics Component] added 'Attacking' to sprite.");

    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

NotfredoGraphicsComponent::~NotfredoGraphicsComponent() {
}

/**
 * Objective: it updates the Notfredo Graphics Component object.
 *
 * @param GameObject *gameObject - game object to update sprite status.
 * @param float deltaTime - amount of time to update sprite time.
 * @return none.
 */
void NotfredoGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    assert(gameObject != nullptr);

    Character *character = (Character*) gameObject;
    assert(character != nullptr);
    Log::instance.info("[Notfredo Graphics Component] Character successfully instantiated.");

    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    Log::instance.info("[Notfredo Graphics Component] Character direction changed to left.");

    if (character->Attacking()) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Attacking");
    } else if (character->physicsComponent.velocity.x == 0) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Idle");
    } else {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Running");
    }

    sprite->Mirror(characterLeftDirection); // Direction update of character sprite.
    Log::instance.info("[Character Graphics Component] Character sprite setted to left.");

    sprite->Update(deltaTime);
    Log::instance.info("[Notfredo Graphics Component] Notfredo sprite updates.");
}
