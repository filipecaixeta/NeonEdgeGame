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
#include "Logger.h"

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
    Log::instance.info("[Lancelot Graphics Component] added 'Idle' to sprite.");

    AddSprite(baseName, "Running", 8, FRAME_TIME);
    Log::instance.info("[Lancelot Graphics Component] added 'Running' to sprite.");

    AddSprite(baseName, "Jumping", 8, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'Jumping' to sprite.");

    AddSprite(baseName, "Walled", 1, 0);

    AddSprite(baseName, "Crouching", 4, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'Crouching' to sprite.");

    AddSprite(baseName, "Blocking", 6, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'Blocking' to sprite.");

    AddSprite(baseName, "AttackingStraight", 3, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'AttackingStraight' to sprite.");

    AddSprite(baseName, "AttackingUppercut", 3, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'AttackingUppercut' to sprite.");

    AddSprite(baseName, "AttackingChop", 4, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'AttackingChop' to sprite.");

    AddSprite(baseName, "AttackingSpear", 3, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'AttackingSpear' to sprite.");

    AddSprite(baseName, "AttackingSword", 3, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'AttackingSword' to sprite.");

    AddSprite(baseName, "AttackingAxe", 4, FRAME_TIME, true);
    Log::instance.info("[Lancelot Graphics Component] added 'AttackingAxe' to sprite.");

    AddSprite(baseName, "Dying", 5, 50);
    Log::instance.info("[Lancelot Graphics Component] added 'Dying' to sprite.");

    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

LancelotGraphicsComponent::~LancelotGraphicsComponent() {
    Log::instance.info("[Lancelot Graphics Component] successfully destroyed.");
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
    assert(lancelot != nullptr);
    Log::instance.info("[Lancelot Graphics Component] Lancelot successfully instantiated.");

    // Verification of character action to update sprite.
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);
    Log::instance.info("[Lancelot Graphics Component] Lancelot direction changed to left.");

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
        Log::instance.info("[Lancelot Graphics Component] Lancelot jump action sprite setted.");
    } else if (gameObject->footing == GameObject::LEFT_WALLED ||
               gameObject->footing == GameObject::RIGHT_WALLED) {
        // Else if character feet are in wall, character sprite action is updated to walled.
        UpdateSprite(gameObject, "Walled");  // Character sprite action update
                                             // to walled.
        Log::instance.info("[Lancelot Graphics Component] Lancelot walled action sprite setted.");
        // It verifies if character is going to left and it is setted.
        characterLeftDirection = (gameObject->footing == GameObject::LEFT_WALLED);
    } else if (lancelot->physicsComponent.velocity.x == LANCELOT_VELOCITY_ZERO) {
        // Else if character is idle, character sprite action is updated to idle.
        UpdateSprite(gameObject, "Idle");  // Character sprite action update
                                           // to idle.
        Log::instance.info("[Lancelot Graphics Component] Lancelot idle action sprite setted.");
    } else {
        // Else, character sprite action is updated to running.
        UpdateSprite(gameObject, "Running");  // Character sprite action update
                                              // to running.
        Log::instance.info("[Lancelot Graphics Component] Lancelot run action sprite setted.");
    }

    assert(gameObject != NULL);
    UpdateCharacterSpriteToDying(gameObject);
    assert(gameObject != NULL);

    sprite->Mirror(characterLeftDirection);  // It swaps direction of character spriterite.
    Log::instance.info("[Lancelot Graphics Component] Lancelot sprite setted to left.");

    sprite->Update(deltaTime);  // It updates elapsed time of the sprite with value passed.
    Log::instance.info("[Lancelot Graphics Component] Lancelot sprite updates.");

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
        Log::instance.info("[Lancelot Graphics Component] Lancelot attacking in the wall.");
    } else {
        Log::instance.info("[Lancelot Graphics Component] Lancelot attacking in the floor.");
    }
    // It verifies how the character is attacking.
    UpdateSprite(gameObject, "Attacking" + lancelot->GetCombo());
    Log::instance.info("[Lancelot Graphics Component] Lancelot combo attacking action sprite setted.");

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
        Log::instance.info("[Lancelot Graphics Component] Lancelot blocking in the wall.");
    } else {
        Log::instance.info("[Lancelot Graphics Component] Lancelot blocking in the floor.");
    }
    UpdateSprite(gameObject, "Blocking");
    Log::instance.info("[Lancelot Graphics Component] Lancelot blocking action sprite setted.");

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
        Log::instance.info("[Lancelot Graphics Component] Lancelot crouching in the wall.");
    } else {
        Log::instance.info("[Lancelot Graphics Component] Lancelot crouching in the floor.");
    }

    UpdateSprite(gameObject, "Crouching");
    Log::instance.info("[Lancelot Graphics Component] Lancelot crouch action sprite setted.");

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
        Log::instance.info("[Lancelot Graphics Component] Lancelot die timer is running.");
        // If character is dying, character sprite action is updated to dying.
        UpdateSprite(gameObject, "Dying");
        Log::instance.info("[Lancelot Graphics Component] Lancelot die action sprite setted.");
    } else {
        Log::instance.info("[Lancelot Graphics Component] Lancelot die timer is not running.");
    }

    assert(gameObject != NULL);
}
