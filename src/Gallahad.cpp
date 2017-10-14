/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: Gallahad.cpp
 * Header File Name: Gallahad.h
 * Class Name: Gallahad
 * Objective: it defines the behavior and actions of the character Gallahad.
 */

#include <iostream>
#include "Gallahad.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include "Cutscene.h"
#include "SoundComponent.h"

/**
 * Objective: it constructs Gallahad object.
 *
 * @param none.
 * @return instance of Gallahad.
 */
Gallahad::Gallahad(ItensManager *itemManager, int x, int y, GameObject *setDrone):
        Player(itemManager, x, y), isHiding(HIDE_TIME), isShooting(false) {
    name = "Gallahad";
    inputComponent = new GallahadInputComponent();
    graphicsComponent = new GallahadGraphicsComponent("Gallahad");
    soundComponent = new SoundComponent(name);
    box.SetWH(graphicsComponent->GetSize());  // Gets the sprite sizes of the character.
    drone = setDrone;
    active = true;
    dieTimer = Timer(DIE_TIME);
}

Gallahad::~Gallahad() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(INITIAL_CUTSCENE_INDEX, false));
}

/**
 * Objective: it manages the attack action of the character.
 *
 * @param none.
 * @return none.
 */
void Gallahad::Attack() {
    // Starts attack timer
    attackCD.Start();
    soundComponent->SoundAttack();
    // Generates attack object
    StageState::AddObject(new Projectile(this, Vec2(INITIAL_PROJECT_X_AXIS, INITIAL_PROJECT_Y_AXIS),
                                         INITIAL_LIFE_TIME_PROJECT, INITIAL_POWER_PROJECT, false));
}

/**
 * Objective: it sets the time and start the hiding action based on a variable (skills).
 *
 * @param none.
 * @return none.
 */
void Gallahad::StartHiding() {
    if (skills[0]) {  // SkillBlocking3
        isHiding.SetLimit(LIMIT_TIME_HIDE_0);
    } else if (skills[1]) {  // SkillBlocking2
        isHiding.SetLimit(LIMIT_TIME_HIDE_1);
    } else if (skills[2]) {  // SkillBlocking1
        isHiding.SetLimit(LIMIT_TIME_HIDE_2);
    } else {
        isHiding.SetLimit(LIMIT_TIME_HIDE_OTHERS);
    }
    isHiding.Start();
    energy -= ENERGY_USED;
    clamp(energy, CLAMP_L, CLAMP_U);
}

/**
 * Objective: it activates the shooting action.
 *
 * @param none.
 * @return none.
 */
void Gallahad::StartShooting() {
    isShooting = true;
}

/**
 * Objective: it desactivates the shooting action.
 *
 * @param none.
 * @return none.
 */
void Gallahad::StopShooting() {
    isShooting = false;
}

/**
 * Objective: it sees the state of the hiding action.
 *
 * @param none.
 * @return bool hiding.IsRunning() - return true if the character is hiding.
 */
bool Gallahad::IsHiding() {
    return isHiding.IsRunning();
}

/**
 * Objective: it sees the state of the shooting action.
 *
 * @param none.
 * @return bool shooting - return true if the character is shooting.
 */
bool Gallahad::IsShooting() {
    return isShooting;
}

void Gallahad::Activate(bool on) {
    if (on) {
        active = on;
    } else {
        active = false;
    }
}

/**
 * Objective: it gets the "active" value.
 *
 * @param none.
 * @return bool active - returns the value of the local variable "active".
 */
bool Gallahad::Active() {
    return active;
}

Drone * Gallahad::GetDrone() {
    Drone *droneObject = (Drone *) drone;
    return droneObject;
}

/**
 * Objective: it updates the time of the character's hiding.
 *
 * @param float deltaTime - the amount of time the character will hide.
 * @return none.
 */
void Gallahad::UpdateTimers(float deltaTime) {
    if (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE) {
        /*
        Rect checkStateTrasition;
        if(StageState::stage == "cidadeGalahad" && !done){
            checkStateTrasition.x = 18565;
            checkStateTrasition.y = 769;
            checkStateTrasition.w = 116;
            checkStateTrasition.h = 181;

            if(box.OverlapsWith(checkStateTrasition) == true){
                Game::GetInstance().GetCurrentState()->quitRequested = true;
                Game::GetInstance().AddState(new Cutscene(4, false));
                done = true;
            }
        }
        */
        Player::UpdateTimers(deltaTime);
        isHiding.Update(deltaTime);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it updates the time of the character's hiding.
 *
 * @param TileMap *map.
 * @param float deltaTime - the amount of time.
 * @return none.
 */
void Gallahad::Update(TileMap *map, float deltaTime) {
    if (map && (deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE)) {
        UpdateTimers(deltaTime);
        inputComponent->Update(this, deltaTime);
        physicsComponent.Update(this, map, deltaTime);
        if (OutOfBounds(map)) {
            SetPosition(Vec2(startingX, startingY));
        } else {
            // It does nothing.
        }
        graphicsComponent->Update(this, deltaTime);
        std::cerr << Is("Gallahad") << std::endl;
    } else {
        // It does nothing.
    }
}
