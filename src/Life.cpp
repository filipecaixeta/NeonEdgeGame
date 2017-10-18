/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: Life.cpp
 * Header File Name: Life.h
 * Class Name: Life
 * Objective: manages the Life aspects of the characters.
*/

#include "Life.h"
#include "Camera.h"

#include <assert.h>

/**
 *Objective: constructor of the class Life.

 * @param int x - coordinate of the the Life.
 * @param int y - coordinate of the the Life.
 * @param string sprite
 * @param float frameCount
 * @param float frameTime
 * @param bool loops
 * @param float lifeTime
 * @param bool dies
 * @return instance of the class Life.
*/
Life::Life(int x, int y, std::string sprite, float frameCount, float frameTime, bool loops,
                                            float lifeTime, bool dies) {
    name = "Life";  // Sets the Life's name.
    assert(frameCount >= FLOAT_MIN_SIZE && frameCount <= FLOAT_MIN_SIZE);
    assert(frameTime >= FLOAT_MIN_SIZE && frameTime <= FLOAT_MIN_SIZE);
    lifeSprite = Sprite(sprite, frameCount, frameTime);  // Construct the sprite of the object Life.
    Vec2 size = lifeSprite.GetSize();  // Gets the size of the object Life.
    box = Rect(x, y, size.x, size.y);  // The position in the screen that the object can be
                                       // collided.
    assert(lifeTime >= FLOAT_MIN_SIZE && lifeTime <= FLOAT_MIN_SIZE);
    endTimer = Timer(lifeTime);
    if (loops) {
        endTimer.Start();
    } else {
        // It does nothing.
    }
    Life::loops = loops;
    Life::dies = dies;  // Manages the action of being collided by the player.
}

/**
 * Objective: destructor of the class Life.
 *
 * @param none.
 * @return none.
*/
Life::~Life() {

}

/**
 * Objective: checks an character is dead.
 *
 * @param none.
 * @return bool dead - returns true if is dead.
*/
bool Life::IsDead() {
    return isDead;
}

/**
 * Objective: sets the variable dead to true if the characters Gallahad or Lancelot dies.
 * @param GameObject* other - the character (Gallahad or Lancelot).
 * @return none.
*/
void Life::NotifyObjectCollision(GameObject* other) {
    assert(other != NULL);
    if (other->Is("Gallahad") || other->Is("Lancelot")) {
        // Destroy the object if the player collides with it.
        if (dies) {
            isDead = true;
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
    assert(other != NULL);
}

void Life::UpdateTimers(float dt) {
    assert(dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MIN_SIZE);
    endTimer.Update(dt);
}

void Life::Update(TileMap* world, float dt) {
    assert(dt >= FLOAT_MIN_SIZE && dt <= FLOAT_MIN_SIZE);
    UpdateTimers(dt);
    if (!loops && !endTimer.IsRunning()) {
        isDead = true;
    } else {
        // It does nothing.
    }
    lifeSprite.Update(dt);
}

void Life::Render() {

    lifeSprite.Render(box.x - Camera::CheckInstance().screenPosition.x, box.y - Camera::CheckInstance().screenPosition.y);
}
