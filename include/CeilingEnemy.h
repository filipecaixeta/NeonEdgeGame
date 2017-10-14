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

enum EnemyState{WAITING,ATTACKING,REARMING};

class CeilingEnemy : public Character {
public:
    CeilingEnemy(int x_axis_position, int y_axis_position);
    bool Attacking();
    void NotifyTileCollision(int tile, Face face);
    void Update(TileMap *world, float deltaTime);
    void UpdateAI(float deltaTime);

private:
    EnemyState state;
};

#endif // CEILINGENEMY_H
