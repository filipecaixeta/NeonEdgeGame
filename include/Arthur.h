#ifndef ARTHUR_H
#define ARTHUR_H

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "ArthurGraphicsComponent.h"
#define ARTHUR_DAMAGE_POWER 9
#define INITIAL_CUTSCENE_INDEX 7
#define PIXELS_XY_AXES_REMOVED 800
#define PIXELS_WH_SIZE_ADDED 1000
#define LONG_DISTANCE_FROM_ARTHUR 400
#define SHORT_DISTANCE_FROM_ARTHUR 100
#define LONG_DISTANCE_FROM_PLAYER 400
#define SHORT_DISTANCE_FROM_PLAYER 100
#define DELAY_TIME 0.006
#define CLAMP_L_U 0.8f
#define MAX_TIME 60


enum ArthurState {IDLE, SLASHING, DASHINGLEFT, DASHINGRIGHT, PUNCHING};

class Arthur : public Character {
public:
    Arthur(int x, int y);
    ~Arthur();
    void UpdateTimers(float deltaTime);
    void NotifyObjectCollision(GameObject *gameObject);
    void UpdateAI(float deltaTime);
    void Update(TileMap *world, float deltaTime);
    void Attack();
    void ComparePlayerBox(Timer idle, Timer slash, Timer dash, Timer punch, Rect radius, ArthurState arthurState, bool triggered, float boxX, float playerX);
    void ArthurStateDashingLeft(Timer idle, Timer dash, float deltaTime, ArthurState arthurState);
    void ArthurStateDashingRight(Timer idle, Timer dash, float deltaTime, ArthurState arthurState);
    void ArthurStateSlashing(Timer idle, Timer slash, ArthurState arthurState, float boxX, float playerX);
    void ArthurStatePunching(Timer idle, Timer punch, ArthurState arthurState, float boxX, float playerX);
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
