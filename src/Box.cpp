/**
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

/**
    Objective: Constructor of the class Box.
    @param int x - Coordinate of the Box
    @param int y - Coordinate of the Box.
    @return Instance to the class Box.
*/
Box::Box(int x, int y):
    Interactive(x,y,"Box") {
        name = "Box";
        hitpoints = 5;
        invincibilityTimer = Timer(500);
}

/**
    Objective: Destructor of the class Lancelot.
    @param None.
    @return None.
*/
Box::~Box() {
}

/**
    Objective: Get the box hitpoints.
    @param None.
    @return int hitpoints - Returns the amount of health of the box.
*/
int Box::GetHealth() {
    return hitpoints;
}

/**
    Objective: Sets the hitpoints of the box to 0.
    @param None.
    @return None.
*/
void Box::Kill() {
    hitpoints = 0;
}

/**
    Objective: Checks if the box is dead.
    @param None.
    @return bool (hitpoints < 1) - Return true if the hitpoints of the box is below 1.
*/
bool Box::IsDead() {
    return (hitpoints < 1);
}

/**
    Objective: Triggers the invincibility of the box.
    @param: None.
    @return: None.
*/
void Box::Trigger() {
    if (!invincibilityTimer.IsRunning()) {
        hitpoints -= 1;
        invincibilityTimer.Start();
    }
}

/**
    Objective: Manages the reactions of the box in a collision with another object.
    @param GameObject* other - The object that is in collision.
    @return None.
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

/**
    Objective: Updates the time of the box's invincibility.
    @param float dt - The amount of time that the Box will be invincible.
    @return None.
*/
void Box::UpdateTimers(float dt) {
    invincibilityTimer.Update(dt);
}

void Box::Update(TileMap* map, float dt) {
    UpdateTimers(dt);
    physicsComponent.Update(this, map, dt);
    Interactive::Update(map, dt);
}
