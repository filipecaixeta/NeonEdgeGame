/**
    Copyright (c) 2017 Neon Edge Game
    File Name: Lancelot.cpp
    Header File Name: Lancelot.h
    Class Name: Lancelot
    Objective: define the behavior and actions of the character Lancelot.
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
    Objective: constructor of the class Lancelot.
    @param none.
    @return instance of the class Lancelot.
*/
Lancelot::Lancelot(ItensManager* itemManager, int x, int y):
    Player(itemManager, x, y),  // Extends the object Player.
    blocking(1000) {
    dieTimer = Timer(250);
    name = "Lancelot";
    inputComponent = new LancelotInputComponent();
    graphicsComponent = new LancelotGraphicsComponent("Lancelot");
    soundComponent = new SoundComponent(name);
    box.SetWH(graphicsComponent->GetSize());  // Gets the sprite sizes of the character.
    attackCD.SetLimit(0);  // Default limit cool down attack.
    timeval t1;
    gettimeofday(&t1, NULL);
    srand(t1.tv_usec * t1.tv_sec);
}

/**
    Objective: destructor of the class Lancelot.
    @param none.
    @return none.
*/
Lancelot::~Lancelot() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(7, false));
}

/**
    Objective: decrease the energy or the hitpoints based on some variables.
    @param int damage - the amount of damage done to the character.
    @return none.
*/
void Lancelot::Damage(int damage) {
    if (!invincibilityTimer.IsRunning()) {
        if (blocking) {
            int n = rand()%100 + 1;  // Random number of 1 to 100.
            if (skills[0]) {  // SkillBlocking3
                if (n < 61) {
                    energy -= 1;
                }
            } else if (skills[1]) {  // SkillBlocking2
                if (n < 76) {
                    energy -= 1;
                }
            } else if (skills[2]) {  // SkillBlocking1
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
    Objective: manage the attacking action of the character based on the variable (combo).
    @param none.
    @return none.
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
    attacking.Start();  // Starts attack timer.
}

/**
    Objective: activate the block action.
    @param: none.
    @return: none.
*/
void Lancelot::Block() {
    blocking = true;
    clamp(physicsComponent.velocity.x, -0.2f, 0.2f);
}

/**
    Objective: desactivate the block action.
    @param: none.
    @return: none.
*/
void Lancelot::Stop() {
    blocking = false;
}

/**
    Objective: set the local variable (combo) value.
    @param: string c - the combo used by the character.
    @return: none.
*/
void Lancelot::Combo(std::string c) {
    combo = c;
}

/**
    Objective: manages the state of an action of the character.
    @param none.
    @return bool blocking - return true if the character is blocking.
*/
bool Lancelot::Blocking() {
    return blocking;
}

/**
    Objective: get the value of the local variable (combo).
    @param none.
    @return string combo - return which combo the character is using.
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
