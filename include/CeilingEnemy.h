#ifndef CEILINGENEMY_H
#define CEILINGENEMY_H
#include "Character.h"
#include "Timer.h"
#include "CeilingEnemyGraphicsComponent.h"

enum EnemyState{WAITING,ATTACKING,REARMING};

class CeilingEnemy : public Character
{
public:
    CeilingEnemy(int x,int y);
    void NotifyTileCollision(int tile, Face face);
    void Update(TileMap* world, float dt);
    void UpdateAI(float dt);

private:
    Timer rearm;
    Timer timer;
    EnemyState state;

};

#endif // CEILINGENEMY_H
