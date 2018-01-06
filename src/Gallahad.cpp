/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: Gallahad.cpp
 * Header File Name: Gallahad.h
 * Class Name: Gallahad
 * Objective: it defines the behavior and actions of the character Gallahad.
 */

#include <iostream>
#include "Gallahad.h"
#include <assert.h>
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Projectile.h"
#include "Cutscene.h"
#include "SoundComponent.h"
#include "Logger.h"

/**
 * Objective: it constructs Gallahad object.
 *
 * @param none.
 * @return instance of Gallahad.
 */
Gallahad::Gallahad(ItemsManager *itemManager, int x, int y, GameObject *setDrone):
        Player(itemManager, x, y), isHiding(HIDE_TIME), isShooting(false) {
    name = "Gallahad";

    inputComponent = new GallahadInputComponent();
    assert(inputComponent != nullptr);
    Log::instance.info("[Gallahad] input component successfully instantiated.");

    assert(name[0] != '\0');
    graphicsComponent = new GallahadGraphicsComponent(name);
    assert(graphicsComponent != nullptr);
    Log::instance.info("[Gallahad] graphics component successfully instantiated.");

    assert(name[0] != '\0');
    soundComponent = new SoundComponent(name);
    assert(soundComponent != nullptr);
    Log::instance.info("[Gallahad] sound component successfully instantiated.");

    box.SetWH(graphicsComponent->GetSize());  // Gets the sprite sizes of the character.
    Log::instance.info("[Gallahad] size setted.");

    drone = setDrone;
    Log::instance.info("[Gallahad] drone setted.");

    active = true;

    dieTimer = Timer(DIE_TIME);
    Log::instance.info("[Gallahad] die Timer setted.");

    Log::instance.info("[Gallahad] successfully instantiated.");
}

Gallahad::~Gallahad() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(INITIAL_CUTSCENE_INDEX, false));
    Log::instance.info("[Gallahad] successfully destroyed.");
}

/**
 * Objective: it manages the attack action of the character.
 *
 * @param none.
 * @return none.
 */
void Gallahad::Attack() {
    attackCD.Start();
    Log::instance.info("[Gallahad] attack cool down started.");

    soundComponent->SoundAttack();
    Log::instance.info("[Gallahad] sound attack started.");


    StageState::AddObject(new Projectile(this, Vec2(INITIAL_PROJECT_X_AXIS, INITIAL_PROJECT_Y_AXIS),
                                         INITIAL_LIFE_TIME_PROJECT, INITIAL_POWER_PROJECT, false));
    Log::instance.info("[Gallahad] projectile created.");
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
        Log::instance.info("[Gallahad] hide time setted to time 0.");
    } else if (skills[1]) {  // SkillBlocking2
        isHiding.SetLimit(LIMIT_TIME_HIDE_1);
        Log::instance.info("[Gallahad] hide time setted to time 1.");
    } else if (skills[2]) {  // SkillBlocking1
        isHiding.SetLimit(LIMIT_TIME_HIDE_2);
        Log::instance.info("[Gallahad] hide time setted to time 2.");
    } else {
        isHiding.SetLimit(LIMIT_TIME_HIDE_OTHERS);
        Log::instance.info("[Gallahad] hide time setted to time 3.");
    }

    isHiding.Start();
    Log::instance.info("[Gallahad] hide action started.");

    energy -= ENERGY_USED;
    Log::instance.info("[Gallahad] energy subtracted.");

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
    Log::instance.info("[Gallahad] shoot action started.");
}

/**
 * Objective: it desactivates the shooting action.
 *
 * @param none.
 * @return none.
 */
void Gallahad::StopShooting() {
    isShooting = false;
    Log::instance.info("[Gallahad] shoot action stoped.");
}

/**
 * Objective: it sees the state of the hiding action.
 *
 * @param none.
 * @return bool hiding.IsRunning() - return true if the character is hiding.
 */
bool Gallahad::IsHiding() {
    return isHiding.IsRunning();
    Log::instance.info("[Gallahad] hide action checked.");
}

/**
 * Objective: it sees the state of the shooting action.
 *
 * @param none.
 * @return bool shooting - return true if the character is shooting.
 */
bool Gallahad::IsShooting() {
    assert(isShooting == true || isShooting == false);
    return isShooting;
    Log::instance.info("[Gallahad] shoot action checked.");
}

void Gallahad::Activate(bool on) {
    assert(on == true || on == false);
    active = on;
    Log::instance.info("[Gallahad] activated.");
}

/**
 * Objective: it gets the "active" value.
 *
 * @param none.
 * @return bool active - returns the value of the local variable "active".
 */
bool Gallahad::Active() {
    return active;
    Log::instance.info("[Gallahad] active checked.");
}

Drone * Gallahad::GetDrone() {
    assert(drone != nullptr);
    Drone *droneObject = (Drone *) drone;
    assert(droneObject != nullptr);
    Log::instance.info("[Gallahad] drone object successfully instantiated.");

    return droneObject;
    Log::instance.info("[Gallahad] drone object getted.");

}

/**
 * Objective: it updates the time of the character's hiding.
 *
 * @param float deltaTime - the amount of time the character will hide.
 * @return none.
 */
void Gallahad::UpdateTimers(float deltaTime) {
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);
    Player::UpdateTimers(deltaTime);
    Log::instance.info("[Gallahad] uptaded timer.");

    isHiding.Update(deltaTime);
    Log::instance.info("[Gallahad] uptaded hide action timer.");
}

/**
 * Objective: it updates the time of the character's hiding.
 *
 * @param TileMap *map.
 * @param float deltaTime - the amount of time.
 * @return none.
 */
void Gallahad::Update(TileMap *map, float deltaTime) {
    assert(map != nullptr);
    assert(deltaTime >= FLOAT_MIN_SIZE && deltaTime <= FLOAT_MAX_SIZE);
    UpdateTimers(deltaTime);

    inputComponent->Update(this, deltaTime);
    Log::instance.info("Input component updated.");

    physicsComponent.Update(this, map, deltaTime);
    Log::instance.info("Physics component updated.");


    if (OutOfBounds(map)) {
        SetPosition(Vec2(startingX, startingY));
        Log::instance.info("[Gallahad] bounds positions setted.");
    } else {
        Log::instance.info("[Gallahad] bounds positions are in screen.");
    }

    graphicsComponent->Update(this, deltaTime);
    Log::instance.info("Graphics component updated.");

    std::cerr << Is("Gallahad") << std::endl;
    Log::instance.info("[Gallahad] is character chacked.");
}
