// Copyright 2017 Neon Edge Game

#include <iostream>
#include <math.h>
#include "Camera.h"
#include "Game.h"
#include "InputManager.h"

#ifndef clamp
    #define clamp(N, L, U) N = std::max((float)L, std::min(N, (float)U))
#endif

Camera* Camera::instance = nullptr;

Camera::Camera():
    maxPos(999999.0f, 999999.0f){
    focus = nullptr;
    pos = Vec2();
    speed = Vec2(1, 1);
}

Camera::~Camera() {
    focus = nullptr;
}

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (!focus) {
        if (InputManager::GetInstance().IsKeyDown(UP_ARROW_KEY)) {
            pos.y -= speed.y * dt;
        }
        if (InputManager::GetInstance().IsKeyDown(DOWN_ARROW_KEY)) {
            pos.y += speed.y * dt;
        }
        if (InputManager::GetInstance().IsKeyDown(LEFT_ARROW_KEY)) {
            pos.x -= speed.x * dt;
        }
        if (InputManager::GetInstance().IsKeyDown(RIGHT_ARROW_KEY)) {
            pos.x += speed.x * dt;
        }
    } else {
            int w, h;
            SDL_Point s = Game::GetInstance().GetScreenSize();
            w = s.x;
            h = s.y;
            if (pos.x > focus->box.GetBottomLeft().x-w / 2) {
                if (pos.x-speed.x * dt < focus->box.GetBottomLeft().x-w / 2) {
                    pos.x = focus->box.GetBottomLeft().x - w / 2;
                } else {
                    pos.x -= speed.x * dt;
                }
            } else {
                if (pos.x + speed.x * dt > focus->box.GetBottomLeft().x - w / 2) {
                    pos.x = focus->box.GetBottomLeft().x - w / 2;
                } else {
                    pos.x += speed.x * dt;
                }
            }
            if (pos.y > focus->box.GetBottomLeft().y - h / 2) {
                if (pos.y - speed.y * dt < focus->box.GetBottomLeft().y - h / 2) {
                    pos.y = focus->box.GetBottomLeft().y-h / 2;
                } else {
                    pos.y -= speed.y * dt;
                }
            } else {
                if (pos.y + speed.y * dt > focus->box.GetBottomLeft().y - h / 2) {
                    pos.y = focus->box.GetBottomLeft().y - h / 2;
                } else {
                    pos.y += speed.y * dt;
                }
            }
            clamp(pos.x, 0.0f, maxPos.x - w);
            clamp(pos.y, 0.0f, maxPos.y - h);
	}
}


GameObject* Camera::GetFocus() {
    return focus;
}

Camera& Camera::GetInstance() {
    if (instance == nullptr) {
        instance = new Camera();
    }
    return *instance;
}

void Camera::SetPos(Vec2 pos){
    this->pos = pos;
}
