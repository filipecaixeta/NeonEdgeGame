/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: LancelotGraphicsComponent.cpp
 * Header File Name: LancelotGraphicsComponent.h
 * Class Name: LancelotGraphicsComponent
 * Objective: it manages Lancelot sprite action.
 */

#include "LancelotGraphicsComponent.h"
#include <assert.h>
#include "Lancelot.h"

/**
 * Objective: it constructs Lancelot graphics component object.
 *
 * @param string baseNameParam.
 * @return Lancelot graphics component instance.
 */
LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseNameParam):
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
    AddSprite(baseName, "Idle", 8, FRAME_TIME);
    AddSprite(baseName, "Running", 8, FRAME_TIME);
    AddSprite(baseName, "Jumping", 8, FRAME_TIME, true);
    AddSprite(baseName, "Walled", 1, 0);
    AddSprite(baseName, "Crouching", 4, FRAME_TIME, true);
    AddSprite(baseName, "Blocking", 6, FRAME_TIME, true);
    AddSprite(baseName, "AttackingStraight", 3, FRAME_TIME, true);
    AddSprite(baseName, "AttackingUppercut", 3, FRAME_TIME, true);
    AddSprite(baseName, "AttackingChop", 4, FRAME_TIME, true);
    AddSprite(baseName, "AttackingSpear", 3, FRAME_TIME, true);
    AddSprite(baseName, "AttackingSword", 3, FRAME_TIME, true);
    AddSprite(baseName, "AttackingAxe", 4, FRAME_TIME, true);
    AddSprite(baseName, "Dying", 5, 50);
    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent() {
}

/**
 * Objective: It updates Lancelot sprite status by your action.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @param float deltaTime - value to update elapsed time of the sprite.
 * @return none.
 */
void LancelotGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    assert(gameObject != NULL);
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);

    Lancelot *lancelot = (Lancelot *) gameObject;  // Instantiation of character Lancelot.

    // Verification of character action to update sprite.
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);

    // Verification of character action to update sprite.
    if (lancelot->Attacking()) {
        assert(gameObject != NULL);
        UpdateCharacterSpriteToAttacking(gameObject);  // Character sprite action update
                                                      // to attacking.
        assert(gameObject != NULL);
    } else if (lancelot->IsBlocking()) {
        assert(gameObject != NULL);
        UpdateCharacterSpriteToBlocking(gameObject);  // Character sprite action update
                                                      // to blocking.
        assert(gameObject != NULL);
    } else if (lancelot->IsCrouching()) {
        assert(gameObject != NULL);
        UpdateCharacterSpriteToCrouching(gameObject);  // Character sprite action update
                                                       // to crouching.
        assert(gameObject != NULL);
    } else if (gameObject->footing == GameObject::AIRBORNE) {
        // Else if character feet status is airborne, character sprite action is updated to jumping.
        UpdateSprite(gameObject, "Jumping");  // Character sprite action update
                                              // to jumping.
    } else if (gameObject->footing == GameObject::LEFT_WALLED ||
               gameObject->footing == GameObject::RIGHT_WALLED) {
        // Else if character feet are in wall, character sprite action is updated to walled.
        UpdateSprite(gameObject, "Walled");  // Character sprite action update
                                             // to walled.
        // It verifies if character is going to left and it is setted.
        characterLeftDirection = (gameObject->footing == GameObject::LEFT_WALLED);
    } else if (lancelot->physicsComponent.velocity.x == LANCELOT_VELOCITY_ZERO) {
        // Else if character is idle, character sprite action is updated to idle.
        UpdateSprite(gameObject, "Idle");  // Character sprite action update
                                           // to idle.
    } else {
        // Else, character sprite action is updated to running.
        UpdateSprite(gameObject, "Running");  // Character sprite action update
                                              // to running.
    }

    assert(gameObject != NULL);
    UpdateCharacterSpriteToDying(gameObject);
    assert(gameObject != NULL);

    sprite->Mirror(characterLeftDirection);  // It swaps direction of character spriterite.
    sprite->Update(deltaTime);  // It updates elapsed time of the sprite with value passed.

    assert(gameObject != NULL);
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToAttacking(GameObject *gameObject) {
    assert(gameObject != NULL);

    Lancelot *lancelot = (Lancelot *) gameObject;  // Instantiation of character Lancelot.
    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }
    // It verifies how the character is attacking.
    UpdateSprite(gameObject, "Attacking" + lancelot->GetCombo());

    assert(gameObject != NULL);
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToBlocking(GameObject *gameObject) {
    assert(gameObject != NULL);

    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }
    UpdateSprite(gameObject, "Blocking");
    assert(gameObject != NULL);
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToCrouching(GameObject *gameObject) {
    assert(gameObject != NULL);

    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }
    UpdateSprite(gameObject, "Crouching");
    assert(gameObject != NULL);
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToDying(GameObject *gameObject) {
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
