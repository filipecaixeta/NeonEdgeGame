// Copyright 2013 Thomas Park.

#include "DroneInputComponent.h"
#include "InputManager.h"
#include "Drone.h"

#define clamp(N, L, U) N = std::max(L, std::min(N, U))

DroneInputComponent::DroneInputComponent() {
}

void DroneInputComponent::Update(Player *obj_, float dt_) {
    InputComponent::Update(obj_, dt_);
    InputManager &input = InputManager::GetInstance();

    if (input.IsKeyDown(MOVE_LEFT_KEY, true)) {
        MoveLeft();
    } else if (input.IsKeyDown(MOVE_RIGHT_KEY, true)) {
        MoveRight();
    } else {
        obj->physicsComponent.velocity.x = 0;
    }

    clamp(obj->physicsComponent.velocity.x, -0.6f, 0.6f);

    if (input.IsKeyDown(MOVE_UP_KEY, true)) {
        MoveUp();
    } else if (input.IsKeyDown(MOVE_DOWN_KEY, true)) {
        MoveDown();
    } else {
        obj->physicsComponent.velocity.y = 0;
    }

    clamp(obj->physicsComponent.velocity.y, -0.6f, 0.6f);

    if (input.IsKeyDown(ATTACK_KEY, true)) {
        Attack();
    }

    ProcessItems();
}
