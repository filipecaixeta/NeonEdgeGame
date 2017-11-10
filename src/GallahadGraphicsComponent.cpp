/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: GallahadGraphicsComponent.cpp
 * Header File Name: GallahadGraphicsComponent.h
 * Class Name: GallahadGraphicsComponent
 * Objective: it manages Gallahad sprite action.
 */

#include "GallahadGraphicsComponent.h"
#include <assert.h>
#include "Gallahad.h"
#include "Rect.h"
#include "Logger.h"

/**
 * Objective: it constructs Gallahad graphics component object.
 *
 * @param string baseNameParam.
 * @return Gallahad graphics component instance.
 */
GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseNameParam):
        GraphicsComponent(baseNameParam) {
    assert(baseName[0] != '\0');
    /*
    Params:
    AddSprite(string baseName,
              string name - character action,
              int frameCount - value of frame count,
              int frameTime - value of frame time,
              bool loops = false - value of loops, by default loops it is setted to false);
    */
    AddSprite(baseName, "Idle", FRAME_COUNT, FRAME_TIME);
    Log::instance.info("[Gallahad Graphics Component] added 'Idle' to sprite.");

    AddSprite(baseName, "Running", FRAME_COUNT, FRAME_TIME);
    Log::instance.info("[Gallahad Graphics Component] added 'Running' to sprite.");

    AddSprite(baseName, "Crouching", HALF_FRAME_COUNT, FRAME_TIME, true);
    Log::instance.info("[Gallahad Graphics Component] added 'Crouching' to sprite.");

    AddSprite(baseName, "Active", HALF_FRAME_COUNT, FRAME_TIME, true);
    Log::instance.info("[Gallahad Graphics Component] added 'Active' to sprite.");

    AddSprite(baseName, "Jumping", FRAME_COUNT, FRAME_TIME, true);
    Log::instance.info("[Gallahad Graphics Component] added 'Jumping' to sprite.");

    AddSprite(baseName, "Shot", HALF_FRAME_COUNT, FRAME_TIME, true);
    Log::instance.info("[Gallahad Graphics Component] added 'Shot' to sprite.");

    AddSprite(baseName, "RunningShot", FRAME_COUNT, FRAME_TIME);
    Log::instance.info("[Gallahad Graphics Component] added 'RunningShot' to sprite.");

    AddSprite(baseName, "JumpingShot", FRAME_COUNT, FRAME_TIME, true);
    Log::instance.info("[Gallahad Graphics Component] added 'JumpingShot' to sprite.");

    AddSprite(baseName, "Dying", FRAME_COUNT, FRAME_TIME_DYING, true);
    Log::instance.info("[Gallahad Graphics Component] added 'Dying' to sprite.");

    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

GallahadGraphicsComponent::~GallahadGraphicsComponent() {
    Log::instance.info("[Gallahad Graphics Component] successfully destroyed.");
}

/**
 * Objective: it updates Gallahad sprite status by your action.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @param float deltaTime - value to update elapsed time of the sprite.
 * @return none.
 */
void GallahadGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    assert(gameObject != nullptr);
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);

    Gallahad *gallahad = (Gallahad *) gameObject;  // Instantiation of character Gallahad.
    assert(gallahad != nullptr);
    Log::instance.info("[Gallahad Graphics Component] Gallahad successfully instantiated.");

    // Verification of character direction to left.
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    Log::instance.info("[Gallahad Graphics Component] Gallahad direction changed to left.");

    // Verification of character action to update sprite.
    if (gallahad->IsShooting()) {
        assert(gameObject != nullptr);
        UpdateCharacterSpriteToShooting(gameObject);  // Character sprite action update
                                                      // to shooting.
        assert(gameObject != nullptr);
    } else if (gallahad->IsCrouching()) {
        assert(gameObject != nullptr);
        UpdateCharacterSpriteToCrouching(gameObject);  // Character sprite action update
                                                       // to crouching.
        assert(gameObject != nullptr);
    } else if (!gallahad->Active()) {
        assert(gameObject != nullptr);
        UpdateCharacterSpriteToActive(gameObject);  // Character sprite action update to active.
        assert(gameObject != nullptr);
    } else if (gameObject->footing == GameObject::AIRBORNE) {
        UpdateSprite(gameObject, "Jumping");  // Character sprite action update to jumping.
        Log::instance.info("[Gallahad Graphics Component] Gallahad jump action sprite setted.");
    } else if (gallahad->physicsComponent.velocity.x == GALLAHAD_VELOCITY_ZERO) {
        UpdateSprite(gameObject, "Idle");  // Character sprite action update to idle.
        Log::instance.info("[Gallahad Graphics Component] Gallahad idle action sprite setted.");
    } else {
        UpdateSprite(gameObject, "Running");  // Character sprite action update to running.
        Log::instance.info("[Gallahad Graphics Component] Gallahad run action sprite setted.");
    }

    assert(gameObject != nullptr);
    assert(sprite != nullptr);
    UpdateCharacterSpriteToHiding(gameObject, sprite);
    assert(gameObject != nullptr);
    assert(sprite != nullptr);

    assert(gameObject != nullptr);
    UpdateCharacterSpriteToDying(gameObject);
    assert(gameObject != nullptr);

    sprite->Mirror(characterLeftDirection);  // Direction update of character sprite.
    Log::instance.info("[Gallahad Graphics Component] Gallahad sprite setted to left.");

    sprite->Update(deltaTime);  // Elapsed time update of the sprite.
    Log::instance.info("[Gallahad Graphics Component] Gallahad sprite updates.");

    assert(gameObject != nullptr);
}

/**
 * Objective: it updates Gallahad sprite status to shooting.
 *
 * @param Gallahad *gallahad - object of Gallahad.
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToShooting(GameObject *gameObject) {
    assert(gameObject != nullptr);

    Gallahad *gallahad = (Gallahad *) gameObject;  // Instantiation of character Gallahad.
    assert(gameObject != nullptr);
    Log::instance.info("[Gallahad Graphics Component] Gallahad successfully instantiated.");

    // It verifies how the character is shooting.
    if (gallahad->physicsComponent.velocity.x != GALLAHAD_VELOCITY_ZERO) {
        // If character speed is non-zero, character sprite action is updated to running shot.
        UpdateSprite(gameObject, "RunningShot");
        Log::instance.info("[Gallahad Graphics Component] Gallahad running shoot action sprite setted.");

    } else if (gameObject->footing == GameObject::AIRBORNE) {
        // If character feet are airborne, character sprite action is updated to jumping shot.
        UpdateSprite(gameObject, "JumpingShot");
        Log::instance.info("[Gallahad Graphics Component] Gallahad jumping shoot action sprite setted.");

    } else {
        // Else, character sprite action is updated to 'simple' shot.
        UpdateSprite(gameObject, "Shot");
        Log::instance.info("[Gallahad Graphics Component] Gallahad shoot action sprite setted.");

    }

    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
        gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }

    assert(gameObject != nullptr);
}

/**
 * Objective: it updates Gallahad sprite status to crouching.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToCrouching(GameObject *gameObject) {
    assert(gameObject != nullptr);

    UpdateSprite(gameObject, "Crouching");
    Log::instance.info("[Gallahad Graphics Component] Gallahad crouch action sprite setted.");

    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
        Log::instance.info("[Gallahad Graphics Component] Gallahad crouching in the wall.");
    } else {
        Log::instance.info("[Gallahad Graphics Component] Gallahad crouching in the floor.");
    }

    assert(gameObject != nullptr);
}

/**
 * Objective: it updates Gallahad sprite status to active.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToActive(GameObject *gameObject) {
    assert(gameObject != nullptr);

    UpdateSprite(gameObject, "Active");
    Log::instance.info("[Gallahad Graphics Component] Gallahad active sprite setted.");

    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
        Log::instance.info("[Gallahad Graphics Component] Gallahad active in the wall.");
    } else {
        Log::instance.info("[Gallahad Graphics Component] Gallahad active in the floor.");
    }

    assert(gameObject != nullptr);
}

/**
 * Objective: it updates Gallahad sprite status to hiding.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToHiding(GameObject *gameObject,
                                                              Sprite *sprite) {
    assert(gameObject != nullptr);
    assert(sprite != nullptr);

    Gallahad *gallahad = (Gallahad *) gameObject;
    assert(gallahad != nullptr);
    Log::instance.info("[Gallahad Graphics Component] Gallahad successfully instantiated.");

    // It verifies if the character is using transparency power.
    if (gallahad->IsHiding()) {
        // If yes, changes transparency to 30 percent.
        sprite->SetTransparency(GALLAHAD_HIDE_POWER_ACTIVED);
        Log::instance.info("[Gallahad Graphics Component] Gallahad transparency setted to 30 percent.");
    } else {
        // Else, keeps transparency at 100 percent.
        sprite->SetTransparency(GALLAHAD_HIDE_POWER_DISABLED);
        Log::instance.info("[Gallahad Graphics Component] Gallahad transparency setted to 100 percent.");
    }

    assert(gameObject != nullptr);
    assert(sprite != nullptr);
}

/**
 * Objective: it updates Gallahad sprite to dying.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToDying(GameObject *gameObject) {
    assert(gameObject != nullptr);

    // It verifies if the character is dying.
    if (gameObject->dieTimer.IsRunning()) {
        // If character is dying, character sprite action is updated to dying.
        Log::instance.info("[Gallahad Graphics Component] Gallahad die timer is running.");
        UpdateSprite(gameObject, "Dying");
        Log::instance.info("[Gallahad Graphics Component] Gallahad die action sprite setted.");
    } else {
        Log::instance.info("[Gallahad Graphics Component] Gallahad die timer is not running.");
    }

    assert(gameObject != nullptr);
}
