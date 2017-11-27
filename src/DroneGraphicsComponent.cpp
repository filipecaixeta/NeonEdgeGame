/**
 * Copyright 2017 Neon Edge Game
 * File Name: DroneGraphicsComponent.cpp
 * Header File Name: DroneGraphicsComponent.h
 * Class Name: DroneGraphicsComponent
 * Objective: it manages Drone graphics component.
 */

#include "DroneGraphicsComponent.h"
#include "Drone.h"
#include "Logger.h"
#include <assert.h>

/**
 * Objective: it constructs the Drone Graphics Component object.
 *
 * @param String baseNameParam - responsable to the insert the default name base.
 * @return instace of Drone Graphics Component.
 */
DroneGraphicsComponent::DroneGraphicsComponent(std::string baseNameParam):
        GraphicsComponent(baseNameParam) {
    assert(baseName[0] != '\0');

    AddSprite(baseName, "Idle", 6, 80);
    Log::instance.info("Drone Graphics Component] added 'Idle' to sprite.");

    AddSprite(baseName, "Running", 6, 80);
    Log::instance.info("[Drone Graphics Component] added 'Running' to sprite.");

    AddSprite(baseName, "Attacking", 6, 80);
    Log::instance.info("[Drone Graphics Component] added 'Attacking' to sprite.");

    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

DroneGraphicsComponent::~DroneGraphicsComponent() {
}

/**
 * Objective: it updates the Drone Graphics Component object.
 *
 * @param GameObject *gameObject - game object to update sprite status.
 * @param float deltaTime - amount of time to update sprite time.
 * @return none.
 */
void DroneGraphicsComponent::Update(GameObject* gameObject, float deltaTime) {
    assert(gameObject != nullptr);

    Drone *drone = (Drone *) gameObject;
    assert(drone != nullptr);
    Log::instance.info("[Drone Graphics Component] Drone successfully instantiated.");

    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    Log::instance.info("[Drone Graphics Component] Character direction changed to left.");

    if (drone->Attacking()) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Attacking");
    } else if (drone->physicsComponent.velocity.x == 0) {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Idle");
    } else {
        assert(gameObject != nullptr);
        UpdateSprite(gameObject, "Running");
    }

    sprite->Mirror(characterLeftDirection); // Direction update of character sprite.
    Log::instance.info("[Drone Graphics Component] Character sprite setted to left.");

    sprite->Update(deltaTime);
    Log::instance.info("[Drone Graphics Component] Drone sprite updates.");
}
