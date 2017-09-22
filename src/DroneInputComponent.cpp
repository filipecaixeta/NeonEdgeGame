/**
    Copyright (c) 2017 Neon Edge
    File Name: DroneInputComponent.cpp
    Header File Name: DroneInputComponent.h
    Class Name: DroneInputComponent
    Objective: Class responsible for the movement of the drone in the game.

*/

#include "DroneInputComponent.h"
#include "InputManager.h"
#include "Drone.h"

#define clamp(N, L, U) N = std::max(L, std::min(N, U))

/**
    Objective: Constructor method.
    @param - No parameters.
    @return - none.

*/
DroneInputComponent::DroneInputComponent() {
}

/**
    Objective: Responsible for the detection of the key pressed and movement of the drone.
    @param obj - Player information.
    @param delayTime - Drone moviment time.
    @return - none.

*/
void DroneInputComponent::Update(Player *obj, float delayTime) {

    // Updates the drone moviment.
    InputComponent::Update(obj, delayTime);

    // Receives the keyboard inputs (movement).
    InputManager &input = InputManager::GetInstance();

    // Checks which key was pressed.
    if (input.IsKeyDown(MOVE_LEFT_KEY, true)) {
        MoveLeft(); // Moves drone to the left
    } else if (input.IsKeyDown(MOVE_RIGHT_KEY, true)) {
        MoveRight(); // Moves drone to the right
    } else {
        obj->physicsComponent.velocity.x = 0; // Makes the drone stand still.
    }

    // Sets maximum drone speed on x  axis.
    clamp(obj->physicsComponent.velocity.x, -0.6f, 0.6f);

    // Checks which key was pressed.
    if (input.IsKeyDown(MOVE_UP_KEY, true)) {
        MoveUp(); // Moves the drone up.
    } else if (input.IsKeyDown(MOVE_DOWN_KEY, true)) {
        MoveDown(); // Moves the drone down.
    } else {
        obj->physicsComponent.velocity.y = 0; // Makes the drone stand still.
    }

    // Sets maximum drone speed on y  axis.
    clamp(obj->physicsComponent.velocity.y, -0.6f, 0.6f);

    // Checks if the drone's attack button has been pressed.
    if (input.IsKeyDown(ATTACK_KEY, true)) {
        Attack(); // Get the drone to attack.
    }
    ProcessItems();
}
