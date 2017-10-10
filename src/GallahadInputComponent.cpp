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

#define clamp(N, L, U) N = std::max(L, std::min(N, U))

/**
 * Objective: it constructs Gallahad graphics component object.
 *
 * @param none.
 * @return instance of Gallahad graphics component.
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
    if (player && (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE)) {
        InputComponent::Update(player, deltaTime);
        InputManager& input = InputManager::GetInstance();

        if (input.KeyPress(ACTIVE_KEY, true)) {
            Toggle();
            // Camera::CheckInstance().Follow();  // It takes pointer to droner.
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

            if (player->IsCrouching()) {
                clamp(player->physicsComponent.velocity.x,
                      -VELOCITY_RANGED_LOW, VELOCITY_RANGED_LOW);
            } else {
                clamp(player->physicsComponent.velocity.x,
                      -VELOCITY_RANGED_HIGH, VELOCITY_RANGED_HIGH);
            }

            if (input.IsKeyDown(CROUCH_KEY, true)) {
                Crouch(true);
            } else {
                Crouch(false);
            }

            if (input.IsKeyDown(ATTACK_KEY, true)) {
                Gallahad *gallahad = (Gallahad *) player;
                gallahad->StartShooting();
                Attack();
            } else {
                Gallahad *gallahad = (Gallahad *) player;
                gallahad->StopShooting();
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
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates Gallahad sprite status by your action.
 *
 * @param GameObject *obj - object of Gallahad.
 * @param float dt - value to update elapsed time of the sprite.
 * @return none.
 */
void GallahadInputComponent::Hide() {
    Gallahad *gallahad = (Gallahad *) player;
    if (gallahad->GetEnergy() > NO_ENERGY && !gallahad->IsHiding()) {
        gallahad->StartHiding();
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
        gallahad->GetDrone()->DroneActivate(true);
        Camera::CheckInstance().CreateFocus(gallahad->GetDrone());
    } else {
        gallahad->Activate(true);
        gallahad->GetDrone()->DroneActivate(false);
        Camera::CheckInstance().CreateFocus(gallahad);
    }
}
