/**
 * Copyright 2017 Neon Edge Game
 * File Name: ArthurGraphicsComponent.cpp
 * Header File Name: ArthurGraphicsComponent.h
 * Class Name: ArthurGraphicsComponent
 * Objective: it manages Arthur graphics component.
 */

#include "ArthurGraphicsComponent.h"
#include "Arthur.h"
#include "Logger.h"
#include <assert.h>

/**
 * Objective: it constructs the Notfredo Graphics Component object.
 *
 * @param String baseNameParam - responsable to the insert the default name base.
 * @return instace of Arthur Graphics Component.
 */
ArthurGraphicsComponent::ArthurGraphicsComponent(std::string baseName_):
        GraphicsComponent(baseName_) {
    assert(baseName[0] != '\0');

    AddSprite(baseName, "Idle", 8, 80);
    Log::instance.info("[Arthur Graphics Component] added 'Idle' to sprite.");

    AddSprite(baseName, "Dash", 6, 80);
    Log::instance.info("[Arthur Graphics Component] added 'Dash' to sprite.");

    AddSprite(baseName, "Punch", 8, 80);
    Log::instance.info("[Arthur Graphics Component] added 'Punch' to sprite.");

    AddSprite(baseName, "Slash", 8, 80);
    Log::instance.info("[Arthur Graphics Component] added 'Slash' to sprite.");

    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

ArthurGraphicsComponent::~ArthurGraphicsComponent() {
}

/**
 * Objective: it updates the Notfredo Graphics Component object.
 *
 * @param GameObject *gameObject - game object to update sprite status.
 * @param float deltaTime - amount of time to update sprite time.
 * @return none.
 */
void ArthurGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    assert(gameObject != nullptr);

    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    Log::instance.info("[Arthur Graphics Component] Character direction changed to left.");

    Arthur *arthur = (Arthur *) gameObject;
    assert(arthur != nullptr);
    Log::instance.info("[Arthur Graphics Component] Arthur successfully instantiated.");

    if (arthur->GetState() == IDLE) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Idle");
    } else {
        // It does nothing.
    }

    if (arthur->GetState() == DASHINGRIGHT || arthur->GetState() == DASHINGLEFT) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Dash");
    } else {
        // It does nothing.
    }

    if (arthur->GetState() == SLASHING) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Slash");
    } else {
        // It does nothing.
    }

    if (arthur->GetState() == PUNCHING) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Punch");
    } else {
        // It does nothing.
    }

    sprite->Mirror(characterLeftDirection); // Direction update of character sprite.
    Log::instance.info("[Arthur Graphics Component] Character sprite setted to left.");

    sprite->Update(deltaTime);
    Log::instance.info("[Arthur Graphics Component] Arthur sprite updates.");
}
