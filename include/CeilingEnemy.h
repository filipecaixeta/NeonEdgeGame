#ifndef CEILINGENEMY_H
#define CEILINGENEMY_H

#include "Character.h"
#include "Timer.h"
#include "CeilingEnemyGraphicsComponent.h"

#define INITIAL_SPIDERMAN_VELOCITY 0
#define PIXELS_X_FROM_SPIDERMAN 25
#define ATTACKING_DELAY_TIME 0.006f
#define REARMING_DELAY_TIME 0.012f
#define ATTACKING_CLAMP_L_U 0.4f
#define REARMING_CLAMP_L_U 0.2f
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767

enum EnemyState{WAITING,ATTACKING,REARMING};

class CeilingEnemy : public Character {
public:
    CeilingEnemy(int x_axis_position, int y_axis_position);
    bool Attacking();
    void NotifyTileCollision(int tile, Face face);
    void UpdateAI(float deltaTime);
    void Update(TileMap *world, float deltaTime);

private:
    EnemyState state;
    void AttackVisiblePlayer(float deltaTime);
};

#endif // CEILINGENEMY_H
