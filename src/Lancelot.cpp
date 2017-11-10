/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: Lancelot.cpp
 * Header File Name: Lancelot.h
 * Class Name: Lancelot
 * Objective: define the behavior and actions of the character Lancelot.
 */

#include "Lancelot.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include "Cutscene.h"
#include "SoundComponent.h"
#include "Logger.h"
#include <cstdlib>
#include <sys/time.h>
#include <assert.h>

/**
 * Objective: constructor of the class Lancelot.
 *
 * @param none.
 * @return instance of the class Lancelot.
*/
Lancelot::Lancelot(ItemsManager *itemManager, int x, int y):
	Player(itemManager, x, y),  // Extends the object Player.
	isBlocking(1000) {

	assert(itemManager != NULL);

	int const DIE_TIME = 250;
	dieTimer = Timer(DIE_TIME);
	name = "Lancelot";
	inputComponent = new LancelotInputComponent();
	graphicsComponent = new LancelotGraphicsComponent("Lancelot");
	soundComponent = new SoundComponent(name);
	box.SetWH(graphicsComponent->GetSize());  // Gets the sprite sizes of the character.
	attackCD.SetLimit(0);  // Default limit cool down attack.
	timeval t1;
	gettimeofday(&t1, NULL);
	srand(t1.tv_usec * t1.tv_sec);

	assert(inputComponent != nullptr);
	assert(graphicsComponent != nullptr);
	assert(soundComponent != nullptr);

	Log::instance.info("Lancelot builder started!");
}
/**
 * Objective: destructor of the class Lancelot.
 *
 * @param none.
 * @return none.
 */
Lancelot::~Lancelot() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
	int const CUT_SCENE_NUMBER = 7;
    Game::GetInstance().AddState(new Cutscene(CUT_SCENE_NUMBER, false));
}

/**
 * Objective: decrease the energy based on a skill probability.
 *
 * @param none.
 * @return none.
 */
void Lancelot::BlockingAttack(){
	int const ENERGY_LOST = 1;
	int const PROBABILITY_61 = 61;
	int const PROBABILITY_76 = 76;
	int const PROBABILITY_91 = 91;

	int n = rand()%100 + 1;  // Random number of 1 to 100.
	if (skills[0]) {  // SkillBlocking3
		if (n < PROBABILITY_61) {
			energy -= ENERGY_LOST;
		} else {
			Log::instance.info("Lancelot don't lost the energy with 39 percent of chance");
		}
	} else if (skills[1]) {  // SkillBlocking2
		if (n < PROBABILITY_76) {
			energy -= ENERGY_LOST;
		} else {
			Log::instance.info("Lancelot don't lost the energy with 24 percent of chance");
		}
	} else if (skills[2]) {  // SkillBlocking1
		if (n < PROBABILITY_91){
			energy -= ENERGY_LOST;
		} else {
			Log::instance.info("Lancelot don't lost the energy with 9 percent of chance");
		}
	} else {
		energy -= ENERGY_LOST;
	}
	clamp(energy, 0, 5);
}

/**
 * Objective: decrease the hitpoints based on some variables.
 *
 * @param int damage - the amount of damage done to the character.
 * @return none.
 */
void Lancelot::Damage(int damage) {

	if (!invincibilityTimer.IsRunning()) {
		if (isBlocking) {
			BlockingAttack();
		} else {
			soundComponent->SoundDamage();
			hitpoints -= (damage);
		}
		invincibilityTimer.Start();
	} else {
		Log::instance.info("Character invincible, takes no damage");
	}
}

/**
 * Objective: manage the attacking action of the character based on the variable (combo).
 *
 * @param none.
 * @return none.
 */
void Lancelot::Attack() {

    attacking.SetLimit(0);
    attackCD.SetLimit(0);
    soundComponent->SoundAttack();

    int const LIMIT_100 = 100;
	int const LIMIT_240 = 240;
	int const LIMIT_320 = 320;
	int const LIMIT_400 = 400;
	int const LIMIT_800 = 800;

    if (combo == "Straight") {
        attacking.SetLimit(LIMIT_240);
        attackCD.SetLimit(LIMIT_100);
        Empower(1);
    } else if (combo == "Uppercut") {
        attacking.SetLimit(LIMIT_240);
        attackCD.SetLimit(LIMIT_400);
        Empower(2);
    } else if (combo == "Chop") {
        attacking.SetLimit(LIMIT_320);
        attackCD.SetLimit(LIMIT_800);
        Empower(3);
    } else if (combo == "Spear") {
        attacking.SetLimit(LIMIT_240);
        attackCD.SetLimit(LIMIT_100);
        Empower(2);
    } else if (combo == "Sword") {
        attacking.SetLimit(LIMIT_240);
        attackCD.SetLimit(LIMIT_400);
        Empower(3);
    } else if (combo == "Axe") {
        attacking.SetLimit(LIMIT_320);
        attackCD.SetLimit(LIMIT_800);
        Empower(5);
    } else {
        Log::instance.warning("No valid combo, check string combo of Lancelot");
    }
    attacking.Start();  // Starts attack timer.
}

/**
 * Objective: activate the block action.
 *
 * @param: none.
 * @return: none.
 */
void Lancelot::StartBlock() {
    isBlocking = true;
	float const VELOCITY_RANGE = 0.2f;
    clamp(physicsComponent.velocity.x, -1*(VELOCITY_RANGE), VELOCITY_RANGE);
}

/**
 * Objective: desactivate the block action.
 *
 * @param: none.
 * @return: none.
 */
void Lancelot::StopBlock() {
    isBlocking = false;
}

/**
 * Objective: set the local variable (combo) value.
 *
 * @param: string c - the combo used by the character.
 * @return: none.
 */
void Lancelot::SetCombo(std::string setCombo) {
	assert(setCombo != "");
	combo = setCombo;
}

/**
 * Objective: manages the state of an action of the character.
 *
 * @param none.
 * @return bool blocking - return true if the character is blocking.
 */
bool Lancelot::IsBlocking() {
	assert(isBlocking == true || isBlocking == false);
    return isBlocking;
}

/**
 * Objective: get the value of the local variable (combo).
 *
 * @param none.
 * @return string combo - return which combo the character is using.
 */
std::string Lancelot::GetCombo() {
	assert(combo != "");
    return combo;
}

void Lancelot::UpdateTimers(float dt) {
	assert(dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MAX_SIZE);

    Rect checkStateTrasition;

    int const X_TRANSITION_POINT = 18504;
	int const Y_TRANSITION_POINT = 2369;
	int const W_TRANSITION_POINT = 112;
	int const H_TRANSITION_POINT = 180;

    if (StageState::stage == "cidadeLancelot") {
        checkStateTrasition.x = X_TRANSITION_POINT;
        checkStateTrasition.y = Y_TRANSITION_POINT;
        checkStateTrasition.w = W_TRANSITION_POINT;
        checkStateTrasition.h = H_TRANSITION_POINT;

        if (box.OverlapsWith(checkStateTrasition) == true) {
            Game::GetInstance().GetCurrentState()->quitRequested = true;
            Game::GetInstance().AddState(new Cutscene(2, false));
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }

    Player::UpdateTimers(dt);
}
