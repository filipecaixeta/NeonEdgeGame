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

/**
 * Objective: it constructs Gallahad graphics component object.
 *
 * @param string baseNameParam.
 * @return Gallahad graphics component instance.
 */
GallahadGraphicsComponent::GallahadGraphicsComponent(std::string baseNameParam):
        GraphicsComponent(baseNameParam) {
    assert(baseNameParam[0] != '\0');
    /*
    Params:
    AddSprite(string baseName,
              string name - character action,
              int frameCount - value of frame count,
              int frameTime - value of frame time,
              bool loops = false - value of loops, by default loops it is setted to false);
    */
    AddSprite(baseName, "Idle", FRAME_COUNT, FRAME_TIME);
    AddSprite(baseName, "Running", FRAME_COUNT, FRAME_TIME);
    AddSprite(baseName, "Crouching", HALF_FRAME_COUNT, FRAME_TIME, true);
    AddSprite(baseName, "Active", HALF_FRAME_COUNT, FRAME_TIME, true);
    AddSprite(baseName, "Jumping", FRAME_COUNT, FRAME_TIME, true);
    AddSprite(baseName, "Shot", HALF_FRAME_COUNT, FRAME_TIME, true);
    AddSprite(baseName, "RunningShot", FRAME_COUNT, FRAME_TIME);
    AddSprite(baseName, "JumpingShot", FRAME_COUNT, FRAME_TIME, true);
    AddSprite(baseName, "Dying", FRAME_COUNT, FRAME_TIME_DYING, true);
    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

GallahadGraphicsComponent::~GallahadGraphicsComponent() {
}

/**
 * Objective: it updates Gallahad sprite status by your action.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @param float deltaTime - value to update elapsed time of the sprite.
 * @return none.
 */
void GallahadGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    assert(gameObject != NULL);
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);

    Gallahad *gallahad = (Gallahad *) gameObject;  // Instantiation of character Gallahad.

    // Verification of character direction to left.
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);

    // Verification of character action to update sprite.
    if (gallahad->IsShooting()) {
        assert(gameObject != NULL);
        UpdateCharacterSpriteToShooting(gameObject);  // Character sprite action update
                                                      // to shooting.
        assert(gameObject != NULL);
    } else if (gallahad->IsCrouching()) {
        assert(gameObject != NULL);
        UpdateCharacterSpriteToCrouching(gameObject);  // Character sprite action update
                                                       // to crouching.
        assert(gameObject != NULL);
    } else if (!gallahad->Active()) {
        assert(gameObject != NULL);
        UpdateCharacterSpriteToActive(gameObject);  // Character sprite action update to active.
        assert(gameObject != NULL);
    } else if (gameObject->footing == GameObject::AIRBORNE) {
        UpdateSprite(gameObject, "Jumping");  // Character sprite action update to jumping.
    } else if (gallahad->physicsComponent.velocity.x == GALLAHAD_VELOCITY_ZERO) {
        UpdateSprite(gameObject, "Idle");  // Character sprite action update to idle.
    } else {
        UpdateSprite(gameObject, "Running");  // Character sprite action update to running.
    }

    assert(gameObject != NULL);
    assert(sprite != NULL);
    UpdateCharacterSpriteToHiding(gameObject, sprite);
    assert(gameObject != NULL);
    assert(sprite != NULL);

    assert(gameObject != NULL);
    UpdateCharacterSpriteToDying(gameObject);
    assert(gameObject != NULL);

    sprite->Mirror(characterLeftDirection);  // Direction update of character sprite.
    sprite->Update(deltaTime);  // Elapsed time update of the sprite.

    assert(gameObject != NULL);
}

/**
 * Objective: it updates Gallahad sprite status to shooting.
 *
 * @param Gallahad *gallahad - object of Gallahad.
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToShooting(GameObject *gameObject) {
    assert(gameObject != NULL);

    Gallahad *gallahad = (Gallahad *) gameObject;  // Instantiation of character Gallahad.

    // It verifies how the character is shooting.
    if (gallahad->physicsComponent.velocity.x != GALLAHAD_VELOCITY_ZERO) {
        // If character speed is non-zero, character sprite action is updated to running shot.
        UpdateSprite(gameObject, "RunningShot");
    } else if (gameObject->footing == GameObject::AIRBORNE) {
        // If character feet are airborne, character sprite action is updated to jumping shot.
        UpdateSprite(gameObject, "JumpingShot");
    } else {
        // Else, character sprite action is updated to 'simple' shot.
        UpdateSprite(gameObject, "Shot");
    }

    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
        gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }

    assert(gameObject != NULL);
}

/**
 * Objective: it updates Gallahad sprite status to crouching.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToCrouching(GameObject *gameObject) {
    assert(gameObject != NULL);

    UpdateSprite(gameObject, "Crouching");
    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
        gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }

    assert(gameObject != NULL);
}

/**
 * Objective: it updates Gallahad sprite status to active.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToActive(GameObject *gameObject) {
    assert(gameObject != NULL);

    UpdateSprite(gameObject, "Active");
    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }

    assert(gameObject != NULL);
}

/**
 * Objective: it updates Gallahad sprite status to hiding.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToHiding(GameObject *gameObject,
                                                              Sprite *sprite) {
    assert(gameObject != NULL);
    assert(sprite != NULL);

    Gallahad *gallahad = (Gallahad *) gameObject;
    // It verifies if the character is using transparency power.
    if (gallahad->IsHiding()) {
        // If yes, changes transparency to 30 percent.
        sprite->SetTransparency(GALLAHAD_HIDE_POWER_ACTIVED);
    } else {
        // Else, keeps transparency at 100 percent.
        sprite->SetTransparency(GALLAHAD_HIDE_POWER_DISABLED);
    }

    assert(gameObject != NULL);
    assert(sprite != NULL);
}

/**
 * Objective: it updates Gallahad sprite to dying.
 *
 * @param GameObject *gameObject - object of Gallahad.
 * @return none.
 */
void GallahadGraphicsComponent::UpdateCharacterSpriteToDying(GameObject *gameObject) {
    assert(gameObject != NULL);

    // It verifies if the character is dying.
    if (gameObject->dieTimer.IsRunning()) {
        // If character is dying, character sprite action is updated to dying.
        UpdateSprite(gameObject, "Dying");
    } else {
        // It does nothing.
    }

    assert(gameObject != NULL);
}
