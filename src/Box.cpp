/**
    Copyright (c) 2017 Neon Edge Game
    File Name: Box.cpp
    Header File Name: Box.h
    Class Name: Box
    Objective: define the behavior of the box.
*/

#include "Box.h"
#include "Camera.h"
#include "StageState.h"
#include "Character.h"
#include "Projectile.h"

/**
    Objective: constructor of the class Box.
    @param int x - coordinate of the Box
    @param int y - coordinate of the Box.
    @return instance of the class Box.
*/
Box::Box(int x, int y):
    Interactive(x, y, "Box") {
        name = "Box";  // Sets the Box's name.
        hitpoints = 5;
        invincibilityTimer = Timer(500);
}

/**
    Objective: destructor of the class Lancelot.
    @param none.
    @return none.
*/
Box::~Box() {
}

/**
    Objective: get the box hitpoints.
    @param none.
    @return int hitpoints - returns the amount of health of the box.
*/
int Box::GetHealth() {
    return hitpoints;
}

/**
    Objective: sets the hitpoints of the box to 0.
    @param none.
    @return none.
*/
void Box::Kill() {
    hitpoints = 0;
}

/**
    Objective: checks if the box is dead.
    @param none.
    @return bool (hitpoints < 1) - return true if the hitpoints of the box is below 1.
*/
bool Box::IsDead() {
    return (hitpoints < 1);
}

/**
    Objective: triggers the invincibility of the box.
    @param: none.
    @return: none.
*/
void Box::Trigger() {
    if (!invincibilityTimer.IsRunning()) {
        hitpoints -= 1;
        invincibilityTimer.Start();
    }
}

/**
    Objective: manages the reactions of the box in a collision with another object.
    @param GameObject* other - the object that is in collision.
    @return none.
*/
void Box::NotifyObjectCollision(GameObject* other) {
    if (other->IsPlayer()) {
        Character* c = (Character*) other;
        // If the player is moving right and in the ground.
        if ((c->physicsComponent.velocity.x > 0) &&
           (other->footing == GROUNDED) &&
           (other->box.y + other->box.h > box.y) &&
           (other->facing == RIGHT)) {
                box.x += 5;  // Move the position to right in 5 meters.
                physicsComponent.TileFix(this,
                StageState::GetCurrentRoom()->GetMap(), RIGHT);
        } else if ((c->physicsComponent.velocity.x < 0) &&
                  (other->footing == GROUNDED) &&
                  (other->box.y + other->box.h > box.y) &&
                  (other->facing == LEFT)) {
                    box.x -= 5;  // Move the position to left in 5 meters.
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

/**
    Objective: updates the time of the box's invincibility.
    @param float dt - the amount of time that the Box will be invincible.
    @return none.
*/
void Box::UpdateTimers(float dt) {
    invincibilityTimer.Update(dt);
}

void Box::Update(TileMap* map, float dt) {
    UpdateTimers(dt);
    physicsComponent.Update(this, map, dt);
    Interactive::Update(map, dt);
}
