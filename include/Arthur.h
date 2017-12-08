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
#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648


enum ArthurState {IDLE, SLASHING, DASHINGLEFT, DASHINGRIGHT, PUNCHING};

class Arthur : public Character {
private:
    void UpdateTimers(float deltaTime = 0);
    void UpdateAI(float deltaTime = 0);
    void ComparePlayerBox(Timer idle, Timer slash, Timer dash, Timer punch, Rect radius,
                          ArthurState arthurState, bool triggered = false, float boxX = 0.0,
                          float playerX = 0.0);
    void ArthurStateDashingLeft(Timer idle, Timer dash, float deltaTime, ArthurState arthurState);
    void ArthurStateDashingRight(Timer idle, Timer dash, float deltaTime, ArthurState arthurState);
    void ArthurStateSlashing(Timer idle, Timer slash, ArthurState arthurState, float boxX = 0.0,
                             float playerX = 0.0);
    void ArthurStatePunching(Timer idle, Timer punch, ArthurState arthurState, float boxX = 0.0,
                             float playerX = 0.0);
    Timer idle;
    Timer slash;
    Timer dash;
    Timer punch;
    Rect radius;
    ArthurState arthurState;
    bool triggered = false;

public:
    Arthur(int x = 0, int y = 0);
    ~Arthur();
    void NotifyObjectCollision(GameObject *gameObject = NULL);
    void Update(TileMap *world = NULL, float deltaTime = 0);
    void Attack();
    ArthurState GetState();
};

#endif /*ARTHUR_H*/
