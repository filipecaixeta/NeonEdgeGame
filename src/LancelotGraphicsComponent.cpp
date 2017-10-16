/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: LancelotGraphicsComponent.cpp
 * Header File Name: LancelotGraphicsComponent.h
 * Class Name: LancelotGraphicsComponent
 * Objective: it manages Lancelot sprite action.
 */

#include "LancelotGraphicsComponent.h"
#include "Lancelot.h"

/**
 * Objective: it constructs Lancelot graphics component object.
 *
 * @param string baseNameParam.
 * @return Lancelot graphics component instance.
 */
LancelotGraphicsComponent::LancelotGraphicsComponent(std::string baseNameParam):
        GraphicsComponent(baseNameParam) {
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
    Lancelot *lancelot = (Lancelot *) gameObject;  // Instantiation of character Lancelot.

    // Verification of character action to update sprite.
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);

    // Verification of character action to update sprite.
    if (lancelot->Attacking()) {
        UpdateCharacterSpriteToAttacking(gameObject);  // Character sprite action update
                                                      // to attacking.
    } else if (lancelot->IsBlocking()) {
        UpdateCharacterSpriteToBlocking(gameObject);  // Character sprite action update
                                                      // to blocking.
    } else if (lancelot->IsCrouching()) {
        UpdateCharacterSpriteToCrouching(gameObject);  // Character sprite action update
                                                       // to crouching.
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

    UpdateCharacterSpriteToDying(gameObject);

    sprite->Mirror(characterLeftDirection);  // It swaps direction of character spriterite.
    sprite->Update(deltaTime);  // It updates elapsed time of the sprite with value passed.
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToAttacking(GameObject *gameObject) {
    Lancelot *lancelot = (Lancelot *) gameObject;  // Instantiation of character Lancelot.
    // It verifies how the character is attacking.
    UpdateSprite(gameObject, "Attacking" + lancelot->GetCombo());
    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToBlocking(GameObject *gameObject) {
    UpdateSprite(gameObject, "Blocking");
    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToCrouching(GameObject *gameObject) {
    UpdateSprite(gameObject, "Crouching");
    // It verifies is character feet are in wall.
    if (gameObject->footing == GameObject::LEFT_WALLED ||
            gameObject->footing == GameObject::RIGHT_WALLED) {
        // If yes, it updates character feet status to airborne.
        gameObject->footing = GameObject::AIRBORNE;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates Lancelot sprite to dying.
 *
 * @param GameObject *gameObject - object of Lancelot.
 * @return none.
 */
void LancelotGraphicsComponent::UpdateCharacterSpriteToDying(GameObject *gameObject) {
    // It verifies if the character is dying.
    if (gameObject->dieTimer.IsRunning()) {
        // If character is dying, character sprite action is updated to dying.
        UpdateSprite(gameObject, "Dying");
    } else {
        // It does nothing.
    }
}
