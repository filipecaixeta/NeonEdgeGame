/**
    Copyright 2017 Neon Edge Game
    File Name: Life.cpp
    Header File Name: Life.h
    Class Name: Life
    Objective: Manages the Life aspects of the characters.
*/

#include "Life.h"
#include "Camera.h"

/**
    Objective: Constructor of the class Life.
    @param int x - Coordinate of the Life.
    @param int y - Coordinate of the Life.
    @param string sprite
    @param float frameCount
    @param float frameTime
    @param bool loops
    @param float lifetime
    @param bool dies
    @return: Instance to the class Life.
*/
Life::Life(int x, int y, std::string sprite, float frameCount, float frameTime, bool loops,
                                            float lifetime, bool dies) {
    name = "Life";
    sp = Sprite(sprite, frameCount, frameTime);
    Vec2 size = sp.GetSize();
    box = Rect(x, y, size.x, size.y);
    endTimer = Timer(lifetime);
    if(loops)
        endTimer.Start();
    Life::loops = loops;
    Life::dies = dies;
}

/**
    Objective: Destructor of the class Life.
    @param None.
    @return None.
*/
Life::~Life() {

}

/**
    Objective: Checks an character is dead.
    @param None.
    @return bool dead - Returns true if is dead.
*/
bool Life::IsDead() {
    return dead;
}

/**
    Objective: Sets the variable dead to true if the characters Gallahad or Lancelot dies.
    @param GameObject* other - The character (Gallahad or Lancelot).
    @return None.
*/
void Life::NotifyObjectCollision(GameObject* other) {
    if (other->Is("Gallahad") || other->Is("Lancelot")) {
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
