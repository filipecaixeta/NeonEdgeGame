/**
 * Copyright (c) 2017 Neon Edge
 * File Name: Camera.cpp
 * Header File Name: Camera.h
 * Class Name: Camera
 * Objective: The purpose of this class is to control the game camera features.
 */

#include <iostream>
#include <math.h>
#include <assert.h>
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include "Logger.h"


#ifndef clamp
    #define clamp(N, L, U) N = std::max((float)L, std::min(N, (float)U))
#endif

Camera* Camera::instance = nullptr; // Starts pointer pointing to nullptr to improve debugging.

/**
 * Objective: The function of this method is to move the camera according to the position of the player.
 *
 * @param - It does not receive parameters.
 * @return - none.
 */
Camera::Camera():
    maxScreenPosition(MAX_SCREEN, MAX_SCREEN){
    cameraFocus = nullptr; // Starts pointer pointing to nullptr to improve debugging.
    screenPosition = Vec2(); // Sets camera start position.
    screenSpeed = Vec2(1, 1); // Sets camera speed.  
    Log::instance.info("Camera builder started!");  
}

/**
 * Objective: Method used to destroy camera type objects.
 *
 * @param - It does not receive parameters.
 * @return - none.
 */
Camera::~Camera() {
    cameraFocus = nullptr;
}

/**
 * Objective: Method responsible for testing float parameters received in functions.
 *
 * @param float testFloat - Value to be tested.
 * @return - False whether the value is valid or true if the value is valid.
 */
bool CheckFloat(float testFloat) {
    bool veryValue = false;
    if ((testFloat >= FLOAT_SIZE_MIN ) && (testFloat <= FLOAT_SIZE_MAX)) {
        Log::instance.info("Valid value! Method CheckFloat Camera");  
        veryValue = true;
    } else {
        Log::instance.error("Tested value higher or lower than allowed!");  
        // It does nothing.
    }
    assert(veryValue == false || veryValue == true);
    return veryValue;
}

/**
 * Objective: Function responsible for setting the new camera focus.
 *
 * @param GameObject * newFocus - Values ​​referring to the new focus position.
 * @return - none.
 */
void Camera::CreateFocus(GameObject* newFocus) {
    if (newFocus) {
        cameraFocus = newFocus; // Sets the new focus of the camera.
        Log::instance.info("New Focus Created!");  
    } else {
        Log::instance.warning("New camera focus has not been set correctly, check Camera CreteFocus!");        
        // It does nothing.
    }
}

/**
 * Objective: It points variable responsible for the cameraFocus to null, causing the screen to stop following the main character.
 *
 * @param - It does not receive parameters.
 * @return - none.
 */
void Camera::StopFocus() {
    cameraFocus = nullptr;
}

/**
 * Objective: Sets the speed of movement of the screen according to the movement of the character.
 *
 * @param float screenDelay - Float value that defines the delay of the focus change of the camera.
 * @return - none.
 */
void Camera::FocusUpdate(float screenDelay) {

    // Checks whether the value of the received parameter is valid.
    bool veryValue = CheckFloat(screenDelay);
	int const INITIAL_VALUE = 0;    
	
    if (veryValue) {
        // Checks and regulates camera focus.
        if (cameraFocus) {
            int screenWidth = INITIAL_VALUE; // Starts the camera width value.
            int screenHeigth = INITIAL_VALUE; // Starts the camera height value.
            SDL_Point screenSize = Game::GetInstance().GetScreenSize(); // Returns device screen size.
            screenWidth = screenSize.x; // Sets the width of the game screen.
            screenHeigth = screenSize.y; // Sets the Heigth of the game screen.

            // Sets the movement of the camera according to the focus (character position).
            if (screenPosition.x > cameraFocus->box.GetBottomLeft().x - screenWidth / FOCUS_CENTER) {
                if (screenPosition.x - screenSpeed.x * screenDelay < cameraFocus->box.GetBottomLeft().x - screenWidth / FOCUS_CENTER) {
                    screenPosition.x = cameraFocus->box.GetBottomLeft().x - screenWidth / FOCUS_CENTER;
                } else {
                    screenPosition.x -= screenSpeed.x * screenDelay;
                }
            } else {
                if (screenPosition.x + screenSpeed.x * screenDelay > cameraFocus->box.GetBottomLeft().x - screenWidth / FOCUS_CENTER) {
                    screenPosition.x = cameraFocus->box.GetBottomLeft().x - screenWidth / FOCUS_CENTER;
                } else {
                    screenPosition.x += screenSpeed.x * screenDelay;
                }
            }
            if (screenPosition.y > cameraFocus->box.GetBottomLeft().y - screenHeigth / FOCUS_CENTER) {
                if (screenPosition.y - screenSpeed.y * screenDelay < cameraFocus->box.GetBottomLeft().y - screenHeigth / FOCUS_CENTER) {
                    screenPosition.y = cameraFocus->box.GetBottomLeft().y - screenHeigth / FOCUS_CENTER;
                } else {
                    screenPosition.y -= screenSpeed.y * screenDelay;
                }
            } else {
                if (screenPosition.y + screenSpeed.y * screenDelay > cameraFocus->box.GetBottomLeft().y - screenHeigth / FOCUS_CENTER) {
                    screenPosition.y = cameraFocus->box.GetBottomLeft().y - screenHeigth / FOCUS_CENTER;
                } else {
                    screenPosition.y += screenSpeed.y * screenDelay;
                }
            }
            clamp(screenPosition.x, INITIAL_POSITION_FOCUS, maxScreenPosition.x - screenWidth);
            clamp(screenPosition.y, INITIAL_POSITION_FOCUS, maxScreenPosition.y - screenHeigth);

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
    } else {
        Log::instance.error("Incorrect camera movement, check FocusUpdate in Camera!");        
        // It does nothing.        
    }
}

/**
 * Objective: Inform the pointer data related to camera focus.
 *
 * @param - It does not receive parameters.
 * @return cameraFocus - Information regarding the camera's current focus.
 */
GameObject* Camera::GetFocus() {
    assert(cameraFocus != nullptr);
    return cameraFocus; 
}

/**
 * Objective: Checks if the camera has been correctly created.
 *
 * @param - It does not receive parameters.
 * @return - Returns pointer referring to camera information.
 */
Camera& Camera::CheckInstance() {

    // Check if the camera instance is valid.
    if (instance == nullptr) {
        instance = new Camera();
        Log::instance.info("New camera instance created!");               
    } else {
        // It does nothing.             
    }
    assert(instance != nullptr);
    return *instance;
}

/**
 * Objective: Sets camera position.
 *
 * @param Vec2 screenPosition - Calculated value for camera positioning.
 * @return - none.
 */
void Camera::SetPosition(Vec2 screenPosition) {
    
    if (CheckFloat(screenPosition.x) && (CheckFloat(screenPosition.y))) {
        this->screenPosition = screenPosition; // Sets position the camera.
        Log::instance.info("New camera position created!");                       
    } else {
        Log::instance.warning("New camera position has not been set! Check Camera SetPosition!");
        // It does nothing.        
    }
}
