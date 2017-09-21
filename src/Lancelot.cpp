/**
    Copyright 2017 Neon Edge Game
    File Name: Lancelot.cpp
    Header File Name: Lancelot.h
    Class Name: Lancelot
    Objective: Define the behavior and actions of the character Lancelot.
*/

#include "Lancelot.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include "Cutscene.h"
#include "SoundComponent.h"
#include <cstdlib>
#include <sys/time.h>

/**
    Objective: Constructor of the class Lancelot.
    @param None.
    @return Instance of the class Lancelot.
*/
Lancelot::Lancelot(ItensManager* itemManager, int x, int y):
    Player(itemManager, x, y),
    blocking(1000) {
    dieTimer = Timer(250);
    name = "Lancelot";
    inputComponent = new LancelotInputComponent();
    graphicsComponent = new LancelotGraphicsComponent("Lancelot");
    soundComponent = new SoundComponent(name);
    box.SetWH(graphicsComponent->GetSize());
    attackCD.SetLimit(0);
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
}

/**
    Objective: Destructor of the class Lancelot.
    @param None.
    @return None.
*/
Lancelot::~Lancelot() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(7, false));
}

/**
    Objective: Decrease the energy or the hitpoints based on the blocking, invincibilityTimer and
        skills variables.
    @param int damage - The amount of damage done to the character.
    @return None.
*/
void Lancelot::Damage(int damage) {
    if (!invincibilityTimer.IsRunning()) {
        if (blocking) {
            int n = rand()%100 + 1;
            if (skills[0]) {
                if (n < 61) {
                    energy -= 1;
                }
            } else if (skills[1]) {
                if (n < 76) {
                    energy -= 1;
                }
            } else if (skills[2]) {
                if (n < 91){
                    energy -= 1;
                }
            } else {
                energy -= 1;
            }
            clamp(energy, 0, 5);
        } else {
            soundComponent->Damage();
            hitpoints -= (damage);
        }
        invincibilityTimer.Start();
    }
}

/**
    Objective: Manage the attacking action of the character based on the variable (combo).
    @param None.
    @return None.
*/
void Lancelot::Attack() {
    attacking.SetLimit(0);
    attackCD.SetLimit(0);
    soundComponent->Attack();
    if (combo == "Straight") {
        attacking.SetLimit(240);
        attackCD.SetLimit(100);
        Empower(1);
    } else if (combo == "Uppercut") {
        attacking.SetLimit(240);
        attackCD.SetLimit(400);
        Empower(2);
    } else if (combo == "Chop") {
        attacking.SetLimit(320);
        attackCD.SetLimit(800);
        Empower(3);
    } else if (combo == "Spear") {
        attacking.SetLimit(240);
        attackCD.SetLimit(100);
        Empower(2);
    } else if (combo == "Sword") {
        attacking.SetLimit(240);
        attackCD.SetLimit(400);
        Empower(3);
    } else if (combo == "Axe") {
        attacking.SetLimit(320);
        attackCD.SetLimit(800);
        Empower(5);
    }
    // Starts attack timer
    attacking.Start();
}

/**
    Objective: Activate the block action.
    @param: None.
    @return: None.
*/
void Lancelot::Block() {
    blocking = true;
    clamp(physicsComponent.velocity.x, -0.2f, 0.2f);
}

/**
    Objective: Desactivate the block action.
    @param: None.
    @return: None.
*/
void Lancelot::Stop() {
    blocking = false;
}

/**
    Objective: Set the local variable (combo) value.
    @param: string c - The combo used by the character.
    @return: None.
*/
void Lancelot::Combo(std::string c) {
    combo = c;
}

/**
    Objective: Manages the state of an action of the character.
    @param None.
    @return bool blocking - Return true if the character is blocking.
*/
bool Lancelot::Blocking() {
    return blocking;
}

/**
    Objective: Get the value of the local variable (combo).
    @param None.
    @return string combo - Return which combo the character is using.
*/
std::string Lancelot::WhichCombo() {
    return combo;
}

void Lancelot::UpdateTimers(float dt) {
    Rect checkStateTrasition;
    if (StageState::stage == "cidadeLancelot") {
        checkStateTrasition.x = 18504;
        checkStateTrasition.y = 2369;
        checkStateTrasition.w = 112;
        checkStateTrasition.h = 180;

        if (box.OverlapsWith(checkStateTrasition) == true) {
            Game::GetInstance().GetCurrentState()->quitRequested = true;
            Game::GetInstance().AddState(new Cutscene(2, false));
        }
    }
    /*if(StageState::stage == "naveLancelot" && !done){
        checkStateTrasition.x = 12556;
        checkStateTrasition.y = 3072;
        checkStateTrasition.w = 108;
        checkStateTrasition.h = 180;
        if(box.OverlapsWith(checkStateTrasition) == true){
            Game::GetInstance().GetCurrentState()->quitRequested = true;
            Game::GetInstance().AddState(new Cutscene(7, false));
            done = true;
        }
    }*/
    Player::UpdateTimers(dt);
}
