#ifndef ARTHUR_H
#define ARTHUR_H

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "ArthurGraphicsComponent.h"

enum ArthurState{IDLE,SLASHING,DASHINGLEFT,DASHINGRIGHT,PUNCHING};

class Arthur : public Character {
public:
    Arthur(int x, int y);
    ~Arthur();
    void UpdateTimers(float deltaTime);
    void NotifyObjectCollision(GameObject *gameObject);
    void UpdateAI(float deltaTime);
    void Update(TileMap *world, float deltaTime);
    void Attack();
    ArthurState GetState();
private:
    Timer idle;
    Timer slash;
    Timer dash;
    Timer punch;
    Rect radius;
    ArthurState arthurState;
    bool triggered;
};

#endif /*ARTHUR_H*/
