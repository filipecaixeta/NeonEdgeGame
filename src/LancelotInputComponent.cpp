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
	int const HOUR_IN_MILISECONDS = 3600000;
	if(player != NULL & deltaTime < HOUR_IN_MILISECONDS){
		InputComponent::Update(player, deltaTime);
		InputManager &input = InputManager::GetInstance();
		float const VELOCITY_RANGED_LOW = 0.2f; 
		float const VELOCITY_RANGED_HIGH = 0.4f; 
	
		if (input.IsKeyDown(MOVE_LEFT_KEY, true)) {
			MoveLeft();
		} else if (input.IsKeyDown(MOVE_RIGHT_KEY, true)) {
			MoveRight();
		} else {
			StayStill();
		}

		if (player->IsCrouching()) {
			clamp(player->physicsComponent.velocity.x, -1*(VELOCITY_RANGED_LOW), VELOCITY_RANGED_LOW);
		} else {
			clamp(player->physicsComponent.velocity.x, -1*(VELOCITY_RANGED_HIGH), VELOCITY_RANGED_HIGH);
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
	} else {
		//Do nothing
	}
}

/**
 * Objective: it blocks enemy attack to character Lancelot.
 *
 * @param none.
 * @return none.
 */
void LancelotInputComponent::Block() {
	int const NO_ENERGY = 0;
	Lancelot *lancelot = (Lancelot*) player;
	if (lancelot->GetEnergy() > NO_ENERGY) {
		lancelot->StartBlock();
	} else {
        lancelot->StopBlock();
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
    lancelot->StopBlock();
}

/**
 * Objective: it does combo in a fight of character Lancelot.
 *
 * @param string c - combo name.
 * @return none.
 */
void LancelotInputComponent::Combo(std::string combo) {
	if(combo != ""){
    Lancelot *lancelot = (Lancelot*) player;
    lancelot->SetCombo(combo);
	} else {
		//Do Nothing
	}
}
