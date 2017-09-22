/**
    Copyright (c) 2017 Neon Edge Game
    File Name: Life.cpp
    Header File Name: Life.h
    Class Name: Life
    Objective: manages the Life aspects of the characters.
*/

#include "Life.h"
#include "Camera.h"

/**
    Objective: constructor of the class Life.
    @param int x - coordinate of the the Life.
    @param int y - coordinate of the the Life.
    @param string sprite
    @param float frameCount
    @param float frameTime
    @param bool loops
    @param float lifetime
    @param bool dies
    @return instance of the class Life.
*/
Life::Life(int x, int y, std::string sprite, float frameCount, float frameTime, bool loops,
                                            float lifetime, bool dies) {
    name = "Life";  // Sets the Life's name.
    sp = Sprite(sprite, frameCount, frameTime);  // Construct the sprite of the object Life.
    Vec2 size = sp.GetSize();  // Gets the size of the object Life.
    box = Rect(x, y, size.x, size.y);  // The position in the screen that the object can be
                                       // collided.
    endTimer = Timer(lifetime);
    if(loops)
        endTimer.Start();
    Life::loops = loops;
    Life::dies = dies;  // Manages the action of being collided by the player.
}

/**
    Objective: destructor of the class Life.
    @param none.
    @return none.
*/
Life::~Life() {

}

/**
    Objective: checks an character is dead.
    @param none.
    @return bool dead - returns true if is dead.
*/
bool Life::IsDead() {
    return dead;
}

/**
    Objective: sets the variable dead to true if the characters Gallahad or Lancelot dies.
    @param GameObject* other - the character (Gallahad or Lancelot).
    @return none.
*/
void Life::NotifyObjectCollision(GameObject* other) {
    if (other->Is("Gallahad") || other->Is("Lancelot")) {
        // Destroy the object if the player collides with it.
        if (dies) {
            dead = true;
        }
    }
}

void Life::UpdateTimers(float dt) {
    endTimer.Update(dt);
}

void Life::Update(TileMap* world, float dt) {
    UpdateTimers(dt);
    if (!loops && !endTimer.IsRunning()) {
        dead = true;
    }
    sp.Update(dt);
}

void Life::Render() {
    sp.Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
