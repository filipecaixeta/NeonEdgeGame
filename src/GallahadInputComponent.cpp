/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: GallahadInputComponent.cpp
 * Header File Name: GallahadInputComponent.h
 * Class Name: GallahadInputComponent
 * Objective: it manages Gallahad input components.
 */

#include "GallahadInputComponent.h"
#include "InputManager.h"
#include "Gallahad.h"
#include "Camera.h"
#include "Drone.h"

#define clamp(N, L, U) N=std::max(L, std::min(N, U))

/**
 * Objective: it constructs Gallahad graphics component object.
 *
 * @param none.
 * @return none.
 */
GallahadInputComponent::GallahadInputComponent() {
}

/**
 * Objective: it updates Gallahad sprite status by your action.
 *
 * @param GameObject *player - object of Gallahad.
 * @param float deltaTime - value to update elapsed time of the sprite.
 * @return none.
 */
void GallahadInputComponent::Update(Player *player, float deltaTime) {
    InputComponent::Update(player, deltaTime);
    InputManager& input = InputManager::GetInstance();

    if (input.KeyPress(ACTIVE_KEY, true)) {
        Toggle();
        // Camera::GetInstance().Follow();  // It takes pointer to droner.
    } else {
        // It does nothing.
    }

    Gallahad *gallahad = (Gallahad *) player;
    if (gallahad->Active()) {
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

        if (input.IsKeyDown(ATTACK_KEY, true)) {
            Gallahad *gallahad = (Gallahad *) player;
            gallahad->Shoot();
            Attack();
        } else {
            Gallahad *gallahad = (Gallahad *) player;
            gallahad->Hold();
        }

        if (input.KeyPress(SPECIAL_KEY, true)) {
            Hide();
        } else {
            // It does nothing.
        }

        if (input.KeyPress(JUMP_KEY, true)) {
            Jump();
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }

    ProcessItems();
}

/**
 * Objective: it updates Gallahad sprite status by your action.
 *
 * @param GameObject *obj - object of Gallahad.
 * @param float dt - value to update elapsed time of the sprite.
 * @return none.
 */
void GallahadInputComponent::Hide() {
    Gallahad *gallahad = (Gallahad *)player;
    if (gallahad->GetEnergy() > 0 && !gallahad->Hiding()) {
        gallahad->Hide();
    } else {
        // It does nothing.
    }
}

/**
 * Objective: It updates Gallahad sprite status by your action.
 *
 * @param GameObject *obj - object of Gallahad.
 * @param float dt - value to update elapsed time of the sprite.
 * @return none.
 */
void GallahadInputComponent::Toggle() {
    Gallahad *gallahad = (Gallahad *) player;
    if (gallahad->Active()) {
        gallahad->Activate(false);
        gallahad->GetDrone()->Activate(true);
        Camera::GetInstance().Follow(gallahad->GetDrone());
    } else {
        gallahad->Activate(true);
        gallahad->GetDrone()->Activate(false);
        Camera::GetInstance().Follow(gallahad);
    }
}
