/**
    Copyright 2017 Neon Edge Game
    File Name: Gallahad.cpp
    Header File Name: Gallahad.h
    Class Name: Gallahad
    Objective: Define the behavior and actions of the character Gallahad.
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
    Objective: Constructor of the class Gallahad.
    @param None.
    @return Instance to the class Gallahad.
*/
Gallahad::Gallahad(ItensManager* itemManager, int x, int y, GameObject* d):
    Player(itemManager, x, y),
    hiding(500),
    shooting(false) {
    name = "Gallahad";
    inputComponent = new GallahadInputComponent();
    graphicsComponent = new GallahadGraphicsComponent("Gallahad");
    soundComponent = new SoundComponent(name);
    box.SetWH(graphicsComponent->GetSize());
    drone = d;
    active = true;
    dieTimer = Timer(800);
}

/**
    Objective: Destructor of the class Gallahad.
    @param None.
    @return None.
*/
Gallahad::~Gallahad() {
    Game::GetInstance().GetCurrentState()->quitRequested = true;
    Game::GetInstance().AddState(new Cutscene(7, false));
}

/**
    Objective: Manages the attack action of the character.
    @param None.
    @return None.
*/
void Gallahad::Attack() {
    // Starts attack timer
    attackCD.Start();
    soundComponent->Attack();
    // Generates attack object
    StageState::AddObject(new Projectile(this, Vec2(0.8, 0), 1200, 1, false));
}

/**
    Objective: Set the time and start the hiding action based on a variable (skills).
    @param None.
    @return None.
*/
void Gallahad::Hide() {
    if (skills[0]) {
        hiding.SetLimit(2000);
    } else if (skills[1]) {
        hiding.SetLimit(1500);
    } else if (skills[2]) {
        hiding.SetLimit(1000);
    } else {
        hiding.SetLimit(500);
    }
    hiding.Start();
    energy -= 1;
    clamp(energy, 0, 5);
}

/**
    Objective: Activate the shooting action.
    @param None.
    @return None.
*/
void Gallahad::Shoot() {
    shooting = true;
}

/**
    Objective: Desactivate the shooting action.
    @param None.
    @return None.
*/
void Gallahad::Hold() {
    shooting = false;
}

/**
    Objective: See the state of the hiding action.
    @param None.
    @return bool hiding.IsRunning() - Return true if the character is hiding.
*/
bool Gallahad::Hiding() {
    return hiding.IsRunning();
}

/**
    Objective: See the state of the shooting action.
    @param None.
    @return bool shooting - Return true if the character is shooting.
*/
bool Gallahad::Shooting() {
    return shooting;
}

void Gallahad::Activate(bool on) {
    active = on;
}

/**
    Objective: Get the "active" value.
    @param None.
    @return bool active - Returns the value of the local variable "active".
*/
bool Gallahad::Active() {
    return active;
}

Drone* Gallahad::GetDrone() {
    Drone* d = (Drone*) drone;
    return d;
}

/**
    Objective: Updates the time of the character's hiding.
    @param float dt - the amount of time the character will hide.
    @return None.
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
