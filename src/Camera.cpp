/**
   Copyright (c) 2013 Thomas Park
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
    maxPos(999999.0f, 999999.0f){
    focus = nullptr; // Starts pointer pointing to nullptr to improve debugging.
    pos = Vec2(); // Sets camera start position.
    speed = Vec2(1, 1); // Sets camera speed.
}

/**
    Objective: Method used to destroy camera type objects.
    @param - It does not receive parameters.
    @return - none.

*/
Camera::~Camera() {
    focus = nullptr;
}

/**
    Objective: Function responsible for setting the new camera focus.
    @param GameObject * newFocus - Values ​​referring to the new focus position.
    @return - none.

*/
void Camera::Follow(GameObject* newFocus) {
    focus = newFocus; // Sets the new focus of the camera.
}

/**
    Objective: It points variable responsible for the focus to null, causing the screen to stop following the main character.
    @param - It does not receive parameters.
    @return - none.

*/
void Camera::Unfollow() {
    focus = nullptr;
}

/**
    Objective: Sets the speed of movement of the screen according to the movement of the character.
    @param float screenDelay - Float value that defines the delay of the focus change of the camera.
    @return - none.

*/
void Camera::Update(float screenDelay) {
    // Checks and regulates camera focus.
    if (!focus) {

        // Regulates focus the up.
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            pos.y -= speed.y * screenDelay;
        }

        // Regulates focus the  down.
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            pos.y += speed.y * screenDelay;
        }

        // Regulates focus the Left.
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            pos.x -= speed.x * screenDelay;
        }

        // Regulates focus the Right.
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            pos.x += speed.x * screenDelay;
        }
    } else {

            int w = 0; // Starts the camera width value.
            int h = 0; // Starts the camera height value.
            SDL_Point s = Game::GetInstance().GetScreenSize();
            w = s.x;
            h = s.y;

            // Sets the movement of the camera according to the focus (character position).
            if (pos.x > focus->box.GetBottomLeft().x - w / 2) {
                if (pos.x - speed.x * screenDelay < focus->box.GetBottomLeft().x-w / 2) {
                    pos.x = focus->box.GetBottomLeft().x - w / 2;
                } else {
                    pos.x -= speed.x * screenDelay;
                }
            } else {
                if (pos.x + speed.x * screenDelay > focus->box.GetBottomLeft().x - w / 2) {
                    pos.x = focus->box.GetBottomLeft().x - w / 2;
                } else {
                    pos.x += speed.x * screenDelay;
                }
            }
            if (pos.y > focus->box.GetBottomLeft().y - h / 2) {
                if (pos.y - speed.y * screenDelay < focus->box.GetBottomLeft().y - h / 2) {
                    pos.y = focus->box.GetBottomLeft().y-h / 2;
                } else {
                    pos.y -= speed.y * screenDelay;
                }
            } else {
                if (pos.y + speed.y * screenDelay > focus->box.GetBottomLeft().y - h / 2) {
                    pos.y = focus->box.GetBottomLeft().y - h / 2;
                } else {
                    pos.y += speed.y * screenDelay;
                }
            }
            clamp(pos.x, 0.0f, maxPos.x - w);
            clamp(pos.y, 0.0f, maxPos.y - h);
    }
}

/**
    Objective: Inform the pointer data related to camera focus.
    @param - It does not receive parameters.
    @return focus - Information regarding the camera's current focus.

*/
GameObject* Camera::GetFocus() {
    return focus;
}

/**
    Objective: Checks if the camera has been correctly created.
    @param - It does not receive parameters.
    @return - Returns pointer referring to camera information.

*/
Camera& Camera::GetInstance() {

    // Checks if the camera has been positioned correctly.
    if (instance == nullptr) {
        instance = new Camera();
    }
    return *instance;
}

/**
    Objective: Sets camera position.
    @param Vec2 pos - Calculated value for camera positioning.
    @return - none.

*/
void Camera::SetPos(Vec2 pos){
    this->pos = pos; // Sets position the camera.
}
