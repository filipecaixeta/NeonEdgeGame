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
#include "Logger.h"
#include <assert.h>
/**
 * Objective: constructor of the class Box.
 *
 * @param int x - coordinate of the Box
 * @param int y - coordinate of the Box.
 * @return instance of the class Box.
 */
Box::Box(int x, int y):
    Interactive(x, y, "Box") {
        name = "Box";  // Sets the Box's name.
        hitPoints = 5;
        invincibilityTimer = Timer(500);
        Log::instance.info("Box builder started!");          
}

/**
 * Objective: destructor of the class Box.
 *
 * @param none.
 * @return none.
 */
Box::~Box() {
}

/**
 * Objective: get the box hitpoints.
 *
 * @param none.
 * @return int hitpoints - returns the amount of health of the box.
 */
int Box::GetHealth() {
    assert(hitPoints >=0 && hitPoints <=5 );
    return hitPoints;
}

/**
 * Objective: sets the hitpoints of the box to 0.
 *
 * @param none.
 * @return none.
 */
void Box::Kill() {
    hitPoints = 0;
}

/**
 * Objective: checks if the box is dead.
 *
 * @param none.
 * @return bool (hitpoints < 1) - return true if the hitpoints of the box is below 1.
 */
bool Box::IsDead() {
    assert(hitPoints >=0 && hitPoints <=5);    
    return (hitPoints < 1);
}

/**
 *  Objective: triggers the invincibility of the box.
 *
 *  @param: none.
 *  @return: none.
 */
void Box::Trigger() {
    if (!invincibilityTimer.IsRunning()) {
        assert(invincibilityTimer.IsRunning() == false);
        hitPoints -= 1;
        invincibilityTimer.Start();
    } else {
        // It does nothing.
    }
}

void Box::OtherColision(GameObject* other){
    if (other->Is("Projectile")) {
        Projectile* p = (Projectile*) other;
        if (p->GetOwner() == "Gallahad") {
            Trigger();
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}
void Box::CharacterAction(Character* c) {
    if (c->Attacking()) {
        Trigger();
    } else {
        // It does nothing.
    }
}

/**
 *  Objective: manages the reactions of the box in a collision with another object.
 *
 *  @param GameObject* other - the object that is in collision.
 *  @return none.
 */
void Box::NotifyObjectCollision(GameObject* other) {
    Log::instance.info("Collision of objects. NotifyObjectCollision in Box!");                     
    if (other->IsPlayer()) {
        Character* c = (Character*) other;
        assert(other != nullptr);
        // If the player is moving right and in the ground.
        if ((c->physicsComponent.velocity.x > 0) && (other->footing == GROUNDED) &&
           (other->box.y + other->box.h > box.y) && (other->facing == RIGHT)) {
                box.x += 5;  // Move the position to right in 5 meters.
                physicsComponent.TileFix(this,
                StageState::GetCurrentRoom()->GetMap(), RIGHT);
        } else if ((c->physicsComponent.velocity.x < 0) && (other->footing == GROUNDED) &&
                  (other->box.y + other->box.h > box.y) && (other->facing == LEFT)) {
                box.x -= 5;  // Move the position to left in 5 meters.
                physicsComponent.TileFix(this,
                StageState::GetCurrentRoom()->GetMap(), LEFT);
        } else {
            // It does nothing.
        }
       CharacterAction(c);
    } else {
        // It does nothing.
    }
    OtherColision(other);
}

/**
 * Objective: updates the time of the box's invincibility.
 *
 * @param float dt - the amount of time that the Box will be invincible.
 * @return none.
 */
void Box::UpdateTimers(float dt) {
    invincibilityTimer.Update(dt);
}

void Box::Update(TileMap* map, float dt) {
    UpdateTimers(dt);
    physicsComponent.Update(this, map, dt);
    Interactive::Update(map, dt);
}
