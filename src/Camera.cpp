/**
   Copyright (c) 2017 Neon Edge
   File Name: Camera.cpp
   Header File Name: Camera.h
   Class Name: Camera
   Objective: The purpose of this class is to control the game camera features.

*/

#include <iostream>
#include <math.h>
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

#ifndef clamp
    #define clamp(N, L, U) N = std::max((float)L, std::min(N, (float)U))
#endif

Camera* Camera::instance = nullptr; // Starts pointer pointing to nullptr to improve debugging.

/**
    Objective: The function of this method is to move the camera according to the position of the player.
    @param - It does not receive parameters.
    @return - none.

*/
Camera::Camera():
    maxScreenPosition(999999.0f, 999999.0f){
    cameraFocus = nullptr; // Starts pointer pointing to nullptr to improve debugging.
    screenPosition = Vec2(); // Sets camera start position.
    screenSpeed = Vec2(1, 1); // Sets camera speed.
}

/**
    Objective: Method used to destroy camera type objects.
    @param - It does not receive parameters.
    @return - none.

*/
Camera::~Camera() {
    cameraFocus = nullptr;
}

/**
    Objective: Function responsible for setting the new camera focus.
    @param GameObject * newFocus - Values ​​referring to the new focus position.
    @return - none.

*/
void Camera::CreateFocus(GameObject* newFocus) {
    cameraFocus = newFocus; // Sets the new focus of the camera.
}

/**
    Objective: It points variable responsible for the cameraFocus to null, causing the screen to stop following the main character.
    @param - It does not receive parameters.
    @return - none.

*/
void Camera::StopFocus() {
    cameraFocus = nullptr;
}

/**
    Objective: Sets the speed of movement of the screen according to the movement of the character.
    @param float screenDelay - Float value that defines the delay of the focus change of the camera.
    @return - none.

*/
void Camera::FocusUpdate(float screenDelay) {
    // Checks and regulates camera focus.
    if (cameraFocus) {
        int screenWidth = 0; // Starts the camera width value.
        int screenHeigth = 0; // Starts the camera height value.
        SDL_Point screenSize = Game::GetInstance().GetScreenSize(); // Returns device screen size.
        screenWidth = screenSize.x; // Sets the width of the game screen.
        screenHeigth = screenSize.y; // Sets the Heigth of the game screen.

        // Sets the movement of the camera according to the focus (character position).
        if (screenPosition.x > cameraFocus->box.GetBottomLeft().x - screenWidth / 2) {
            if (screenPosition.x - screenSpeed.x * screenDelay < cameraFocus->box.GetBottomLeft().x - screenWidth / 2) {
                screenPosition.x = cameraFocus->box.GetBottomLeft().x - screenWidth / 2;
            } else {
                screenPosition.x -= screenSpeed.x * screenDelay;
            }
        } else {
            if (screenPosition.x + screenSpeed.x * screenDelay > cameraFocus->box.GetBottomLeft().x - screenWidth / 2) {
                screenPosition.x = cameraFocus->box.GetBottomLeft().x - screenWidth / 2;
            } else {
                screenPosition.x += screenSpeed.x * screenDelay;
            }
        }
        if (screenPosition.y > cameraFocus->box.GetBottomLeft().y - screenHeigth / 2) {
            if (screenPosition.y - screenSpeed.y * screenDelay < cameraFocus->box.GetBottomLeft().y - screenHeigth / 2) {
                screenPosition.y = cameraFocus->box.GetBottomLeft().y - screenHeigth / 2;
            } else {
                screenPosition.y -= screenSpeed.y * screenDelay;
            }
        } else {
            if (screenPosition.y + screenSpeed.y * screenDelay > cameraFocus->box.GetBottomLeft().y - screenHeigth / 2) {
                screenPosition.y = cameraFocus->box.GetBottomLeft().y - screenHeigth / 2;
            } else {
                screenPosition.y += screenSpeed.y * screenDelay;
            }
        }
        clamp(screenPosition.x, 0.0f, maxScreenPosition.x - screenWidth);
        clamp(screenPosition.y, 0.0f, maxScreenPosition.y - screenHeigth);

    } else {
        
        // Regulates focus the up.
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            screenPosition.y -= screenSpeed.y * screenDelay;
        } else {
            // It does nothing.
        }

        // Regulates focus the  down.
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            screenPosition.y += screenSpeed.y * screenDelay;
        } else {
            // It does nothing.
        }

        // Regulates focus the Left.
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            screenPosition.x -= screenSpeed.x * screenDelay;
        } else {
            // It does nothing.
        }

        // Regulates focus the Right.
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            screenPosition.x += screenSpeed.x * screenDelay;
        } else {
            // It does nothing.
        }
    }
}

/**
    Objective: Inform the pointer data related to camera focus.
    @param - It does not receive parameters.
    @return cameraFocus - Information regarding the camera's current focus.

*/
GameObject* Camera::GetFocus() {
    return cameraFocus; 
}

/**
    Objective: Checks if the camera has been correctly created.
    @param - It does not receive parameters.
    @return - Returns pointer referring to camera information.

*/
Camera& Camera::CheckInstance() {

    // Check if the camera instance is valid.
    if (instance == nullptr) {
        instance = new Camera();
    } else {
        // It does nothing.
    }
    return *instance;
}

/**
    Objective: Sets camera position.
    @param Vec2 screenPosition - Calculated value for camera positioning.
    @return - none.

*/
void Camera::SetPosition(Vec2 screenPosition){
    this->screenPosition = screenPosition; // Sets position the camera.
}
