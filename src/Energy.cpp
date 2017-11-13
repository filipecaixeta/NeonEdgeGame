/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: Energy.cpp
 * Header File Name: Energy.h
 * Class Name: Energy
 * Objective: it manages character state life.
*/

#include "Energy.h"
#include "Camera.h"

#include <assert.h>

/**
 * Objective: it constructs energy object.

 * @param int x_axis_position - value to base.
 * @param int y_axis_position - value to height.
 * @param string sprite - .
 * @param float frameCount - value of frame count.
 * @param float frameTime - value of frame time.
 * @param bool loops - loops state.
 * @param float lifetime - value of life time.
 * @param bool dies - character life state.
 * @return none.
*/
Energy::Energy(int x_axis_position, int y_axis_position, std::string str_sprite, float frameCount, 
               float frameTime, bool loops, float lifetime, bool dies) {
    name = "Energy";
    assert(frameCount >= FLOAT_SIZE_MIN && frameCount <= FLOAT_MAX_SIZE);
    assert(frameTime >= FLOAT_SIZE_MIN && frameTime <= FLOAT_MAX_SIZE);
    sprite = Sprite(str_sprite, frameCount, frameTime);
    Vec2 size = sprite.GetSize();
    box = Rect(x_axis_position, y_axis_position, size.x, size.y);
    endTimer = Timer(lifetime);
    if (loops) {
        endTimer.Start();
    } else {
		// Do nothing
	}
    Energy::loops = loops;
    Energy::dies = dies;
}

/**
 * Objective: it destroys energy object.
 *
 * @param none.
 * @return none.
*/
Energy::~Energy() {
}

/**
 * Objective: it verifies if character is dead.
 *
 * @param none.
 * @return bool dead - character life state.
*/
bool Energy::IsDead() {
    return dead;  // It returns true if character is dead.
}

/**
 * Objective: it verifies is character dies with object collision.
 *
 * @param GameObject *other - character object.
 * @return none.
*/
void Energy::NotifyObjectCollision(GameObject *other) {
    // It verifies the name of character used.
    if (other->Is("Gallahad") || other->Is("Lancelot")) {
        assert(other != NULL);
        // It verifies if character is dead.
        if (dies) {
            dead = true;
        } else {
			// Do nothing
		}
    } else {
		// Do nothing
	}
}

/**
 * Objective: it updates end timer of character.
 *
 * @param float deltaTime - amount of time.
 * @return none.
*/
void Energy::UpdateTimers(float deltaTime) {
    assert(deltaTime >= FLOAT_SIZE_MIN && deltaTime <= FLOAT_MAX_SIZE);
    endTimer.Update(deltaTime);  // It updates end timer with value passed.
}

/**
 * Objective: it updates times of game.
 *
 * @param TileMap *world.
 * @param float deltaTime - amount of time.
 * @return none.
*/
void Energy::Update(TileMap *world, float deltaTime) {
    assert(deltaTime >= FLOAT_SIZE_MIN && deltaTime <= FLOAT_MAX_SIZE);
    // It verifies character state life.
    if (!loops && !endTimer.IsRunning()) {
        dead = true;
    } else {
		// Do nothing
    }
    UpdateTimers(deltaTime);  // It updates end timer of character with value passed.
    sprite.Update(deltaTime);  // It updates elapsed time of the sprite with value passed, deltaTime.
}

/**
 * Objective: it renders the camera position.
 *
 * @param none.
 * @return none.
*/
void Energy::Render() {
    sprite.RenderTexture(box.x - Camera::CheckInstance().screenPosition.x, 
    box.y - Camera::CheckInstance().screenPosition.y);
}

