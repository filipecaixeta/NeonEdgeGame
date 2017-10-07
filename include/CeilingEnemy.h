#ifndef CEILINGENEMY_H
#define CEILINGENEMY_H
#include "Character.h"
#include "Timer.h"
#include "CeilingEnemyGraphicsComponent.h"

enum EnemyState{WAITING,ATTACKING,REARMING};

class CeilingEnemy : public Character
{
public:
    CeilingEnemy(int x_axis_position,int y_axis_position);
    bool Attacking();
    void NotifyTileCollision(int tile, Face face);
    void Update(TileMap* world, float deltaTime);
    void UpdateAI(float deltaTime);

private:
    EnemyState state;

};

#endif // CEILINGENEMY_H
