/**
    Copyright (c) 2017 Neon Edge Game
    File Name: Gallahad.cpp
    Header File Name: Gallahad.h
    Class Name: Gallahad
    Objective: define the behavior and actions of the character Gallahad.
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
    Objective: constructor of the class Gallahad.
    @param none.
    @return instance of the class Gallahad.
*/
Gallahad::Gallahad(ItensManager* itemManager, int x, int y, GameObject* d):
    Player(itemManager, x, y),  // Extends the object Player.
    hiding(500),
    shooting(false) {
    name = "Gallahad";
    inputComponent = new GallahadInputComponent();
    graphicsComponent = new GallahadGraphicsComponent("Gallahad");
    soundComponent = new SoundComponent(name);
    box.SetWH(graphicsComponent->GetSize());  // Gets the sprite sizes of the character.
    drone = d;
    active = true;
    dieTimer = Timer(800);
}

/**
    Objective: destructor of the class Gallahad.
    @param none.
    @return none.
*/
Gallahad::~Gallahad() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(7, false));
}

/**
    Objective: manages the attack action of the character.
    @param none.
    @return none.
*/
void Gallahad::Attack() {
    // Starts attack timer
    coolDownAttack.Start();
    soundComponent->Attack();
    // Generates attack object
    StageState::AddObject(new Projectile(this, Vec2(0.8, 0), 1200, 1, false));
}

/**
    Objective: set the time and start the hiding action based on a variable (skills).
    @param none.
    @return none.
*/
void Gallahad::Hide() {
    if (skills[0]) {  // SkillBlocking3
        hiding.SetLimit(2000);
    } else if (skills[1]) {  // SkillBlocking2
        hiding.SetLimit(1500);
    } else if (skills[2]) {  // SkillBlocking1
        hiding.SetLimit(1000);
    } else {
        hiding.SetLimit(500);
    }
    hiding.Start();
    energy -= 1;
    clamp(energy, 0, 5);
}

/**
    Objective: activate the shooting action.
    @param none.
    @return none.
*/
void Gallahad::Shoot() {
    shooting = true;
}

/**
    Objective: desactivate the shooting action.
    @param none.
    @return none.
*/
void Gallahad::Hold() {
    shooting = false;
}

/**
    Objective: see the state of the hiding action.
    @param none.
    @return bool hiding.IsRunning() - return true if the character is hiding.
*/
bool Gallahad::Hiding() {
    return hiding.IsRunning();
}

/**
    Objective: see the state of the shooting action.
    @param none.
    @return bool shooting - return true if the character is shooting.
*/
bool Gallahad::Shooting() {
    return shooting;
}

void Gallahad::Activate(bool on) {
    active = on;
}

/**
    Objective: get the "active" value.
    @param none.
    @return bool active - returns the value of the local variable "active".
*/
bool Gallahad::Active() {
    return active;
}

Drone* Gallahad::GetDrone() {
    Drone* d = (Drone*) drone;
    return d;
}

/**
    Objective: updates the time of the character's hiding.
    @param float dt - the amount of time the character will hide.
    @return none.
*/
void Gallahad::UpdateTimers(float dt) {
    /*Rect checkStateTrasition;
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
    }*/
    Player::UpdateTimers(dt);
    hiding.Update(dt);
}

void Gallahad::Update(TileMap* map, float dt) {
    UpdateTimers(dt);
    inputComponent->Update(this, dt);
    physicsComponent.Update(this, map, dt);
    if (OutOfBounds(map)) {
        SetPosition(Vec2(startingX, startingY));
    }
    graphicsComponent->Update(this, dt);
    std::cerr << Is("Gallahad") <<std::endl;
}
