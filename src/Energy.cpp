/**
    Copyright (c) 2017 Neon Edge Game.
    File Name: Energy.cpp
    Header File Name: Energy.h
    Class Name: Energy
    Objective: it manages character state life.

*/

#include "Energy.h"
#include "Camera.h"

/**
    Objective: it constructs energy object.
    @param int x - value to base.
    @param int y - value to height.
    @param string sprite - .
    @param float frameCount - value of frame count.
    @param float frameTime - value of frame time.
    @param bool loops - loops state.
    @param float lifetime - value of life time.
    @param bool dies - character life state.
    @return none.

*/
Energy::Energy(int x, int y, std::string sprite, float frameCount, float frameTime, bool loops,
               float lifetime, bool dies) {
    name = "Energy";
    sp = Sprite(sprite, frameCount, frameTime);
    Vec2 size = sp.GetSize();
    box = Rect(x, y, size.x, size.y);
    endTimer = Timer(lifetime);
    if (loops) {
        endTimer.Start();
    }
    Energy::loops = loops;
    Energy::dies = dies;
}

/**
    Objective: it destroys energy object.
    @param none.
    @return none.

*/
Energy::~Energy() {
}

/**
    Objective: it verifies if character is dead.
    @param none.
    @return bool dead - character life state.

*/
bool Energy::IsDead() {
    return dead;  // It returns true if character is dead.
}

/**
    Objective: it verifies is character dies with object collision.
    @param GameObject *other - character object.
    @return none.

*/
void Energy::NotifyObjectCollision(GameObject *other) {
    // It verifies the name of character used.
    if (other->Is("Gallahad") || other->Is("Lancelot")) {
        // It verifies if character is dead.
        if (dies) {
            dead = true;
        }
    }
}

/**
    Objective: it updates end timer of character.
    @param float dt - amount of time.
    @return none.

*/
void Energy::UpdateTimers(float dt) {
    endTimer.Update(dt);  // It updates end timer with value passed.
}

/**
    Objective: it updates times of game.
    @param TileMap *world.
    @param float dt - amount of time.
    @return none.

*/
void Energy::Update(TileMap *world, float dt) {
    UpdateTimers(dt);  // It updates end timer of character with value passed.
    // It verifies character state life.
    if (!loops && !endTimer.IsRunning()) {
        dead = true;
    }
    sp.Update(dt);  // It updates elapsed time of the sprite with value passed, dt.
}

/**
    Objective: it renders the camera position.
    @param none.
    @return none.

*/
void Energy::Render() {
    sp.Render(box.x - Camera::CheckInstance().screenPosition.x, box.y - Camera::CheckInstance().screenPosition.y);
}
