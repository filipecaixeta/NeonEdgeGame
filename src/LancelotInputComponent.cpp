/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: LancelotInputComponent.cpp
 * Header File Name: LancelotInputComponent.h
 * Class Name: LancelotInputComponent
 * Objective: it manages Lancelot input components.
 */

#include "LancelotInputComponent.h"
#include "InputManager.h"
#include "Lancelot.h"

#define clamp(N, L, U) N = std::max(L, std::min(N, U))

/**
 * Objective: it constructs Lancelot graphics component object.
 *
 * @param none.
 * @return none.
 */
LancelotInputComponent::LancelotInputComponent() {
}

/**
 * Objective: it updates Lancelot sprite status by your action.
 *
 * @param GameObject *player - object of Lancelot.
 * @param float deltaTime - value to update elapsed time of the sprite.
 * @return none.
 */
void LancelotInputComponent::Update(Player *player, float deltaTime) {
    InputComponent::Update(player, deltaTime);
    InputManager &input = InputManager::GetInstance();

    if (input.IsKeyDown(MOVE_LEFT_KEY, true)) {
        MoveLeft();
    } else if (input.IsKeyDown(MOVE_RIGHT_KEY, true)) {
        MoveRight();
    } else {
        StayStill();
    }

    if (player->Crouching()) {
        clamp(player->physicsComponent.velocity.x, - 0.2f, 0.2f);
    } else {
        clamp(player->physicsComponent.velocity.x, - 0.4f, 0.4f);
    }

    if (input.IsKeyDown(CROUCH_KEY, true)) {
        Crouch(true);
    } else {
        Crouch(false);
    }

    if (input.KeyPress(ATTACK_KEY, true)) {
        if (input.IsKeyDown(MOVE_LEFT_KEY, true) || input.IsKeyDown(MOVE_RIGHT_KEY, true)) {
            if (player->skills[6]) {
                Combo("Axe");
            } else {
                Combo("Chop");
            }
        } else if (input.IsKeyDown(SDLK_w)) {
            if (player->skills[5]) {
                Combo("Sword");
            } else {
                Combo("Uppercut");
            }
        } else {
            if (player->skills[4]) {
                Combo("Spear");
            } else {
                Combo("Straight");
            }
        }
        Attack();
    } else {
        // It does nothing.
    }

    if (input.IsKeyDown(SPECIAL_KEY, true)) {
        Block();
    } else {
        Stop();
    }

    if (input.KeyPress(JUMP_KEY, true)) {
        Jump();
    } else {
        // It does nothing.
    }

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        Save(true);
    } else {
        // It does nothing.
    }

    if (input.MousePress(RIGHT_MOUSE_BUTTON)) {
        Save(false);
    } else {
        // It does nothing.
    }

    ProcessItems();
}

/**
 * Objective: it blocks enemy attack to character Lancelot.
 *
 * @param none.
 * @return none.
 */
void LancelotInputComponent::Block() {
    Lancelot *lancelot = (Lancelot*) player;
    if (lancelot->GetEnergy() > 0) {
        lancelot->Block();
    } else {
        lancelot->Stop();
    }
}

/**
 * Objective: it stops character Lancelot.
 *
 * @param none.
 * @return none.
 */
void LancelotInputComponent::Stop() {
    Lancelot *lancelot = (Lancelot*) player;
    lancelot->Stop();
}

/**
 * Objective: it does combo in a fight of character Lancelot.
 *
 * @param string c - combo name.
 * @return none.
 */
void LancelotInputComponent::Combo(std::string c) {
    Lancelot *lancelot = (Lancelot*) player;
    lancelot->Combo(c);
}
