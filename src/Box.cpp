/*
    Copyright 2017 Neon Edge Game
    File Name: Box.cpp
    Header File Name: Box.h
    Class Name: Box
    Objective: Define the behavior of the box.
*/

#include "Box.h"
#include "Camera.h"
#include "StageState.h"
#include "Character.h"
#include "Projectile.h"

/*
    Function Objective: Constructor of the class Box.
    param: int x, int y: coordinates of the box.
    return: Instance to Box.
*/
Box::Box(int x, int y):
    Interactive(x,y,"Box") {
        name = "Box";
        hitpoints = 5;
        invincibilityTimer = Timer(500);
}

/*
    Function Objective: Destructor of the class Lancelot.
    param: No parameter.
    return: No return.
*/
Box::~Box() {
}

/*
    Function Objective: Get the box hitpoints.
    param: No parameter.
    return: Returns the amount of hitpoints of the box.
*/
int Box::GetHealth() {
    return hitpoints;
}

/*
    Function Objective: Sets the hitpoints of the box to 0.
    param: No parameter.
    return: No return.
*/
void Box::Kill() {
    hitpoints = 0;
}

/*
    Function Objective: Checks if the box is dead.
    param: No parameter.
    return: Return true if the hitpoints of the box is below 1.
*/
bool Box::IsDead() {
    return (hitpoints < 1);
}

/*
    Function Objective: Triggers the invincibility of the box.
    param: No parameter.
    return: No return.
*/
void Box::Trigger() {
    if (!invincibilityTimer.IsRunning()) {
        hitpoints -= 1;
        invincibilityTimer.Start();
    }
}

/*
    Function Objective: Manages the reactions of the box in a collision with another object.
    param: GameObject* other: the object that is in collision.
    return: No return.
*/
void Box::NotifyObjectCollision(GameObject* other) {
    if (other->IsPlayer()) {
        Character* c = (Character*) other;
        if ((c->physicsComponent.velocity.x > 0) &&
           (other->footing == GROUNDED) &&
           (other->box.y + other->box.h > box.y) &&
           (other->facing == RIGHT)) {
                box.x += 5;
                physicsComponent.TileFix(this,
                StageState::GetCurrentRoom()->GetMap(), RIGHT);
        } else if ((c->physicsComponent.velocity.x < 0) &&
                  (other->footing == GROUNDED) &&
                  (other->box.y + other->box.h > box.y) &&
                  (other->facing == LEFT)) {
                    box.x -= 5;
                    physicsComponent.TileFix(this,
                    StageState::GetCurrentRoom()->GetMap(), LEFT);
        }
        if (c->Attacking()) {
            Trigger();
        }
    }
    if (other->Is("Projectile")) {
        Projectile* p = (Projectile*) other;
        if (p->GetOwner() == "Gallahad") {
            Trigger();
        }
    }
}

/*
    Function Objective: Updates the time of the box's invincibility.
    param: float dt: the amount of time the box will be invincible.
    return: No return.
*/
void Box::UpdateTimers(float dt) {
    invincibilityTimer.Update(dt);
}

void Box::Update(TileMap* map, float dt) {
    UpdateTimers(dt);
    physicsComponent.Update(this, map, dt);
    Interactive::Update(map, dt);
}
