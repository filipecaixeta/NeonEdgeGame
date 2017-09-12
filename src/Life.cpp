/*
    Copyright 2017 Neon Edge Game
    File Name: Life.cpp
    Header File Name: Life.h
    Class Name: Life
    Objective: Manages the Life aspects of the characters.
*/

#include "Life.h"
#include "Camera.h"

/*
    Function Objective: Constructor of the class Life.
    param: int x, int y, std::string sprite, float frameCount, float frameTime, bool loops,
                                                float lifetime, bool dies.
    return: Instance to Life.
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

/*
    Function Objective: Destructor of the class Life.
    param: No parameter.
    return: No return.
*/
Life::~Life() {

}

/*
    Function Objective: Checks an character is dead.
    param: No parameter.
    return: Returns true if is dead.
*/
bool Life::IsDead() {
    return dead;
}

/*
    Function Objective: Sets the variable dead to true if the characters Gallahad or Lancelot dies.
    param: GameObject* other: the character (Gallahad or Lancelot).
    return: No return.
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
