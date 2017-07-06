#ifndef TURRETBOSS_H_
#define TURRETBOSS_H_

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "TurretBossGraphicsComponent.h"

enum TurretBossState{IDLE,SPAWNING,SHOOTING}

class TurretBoss : public Character{
public:
	TurretBoss(int x, int y);
	~TurretBoss();
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
private:
	Timer spawn;
	Timer shoot;
	Rect radius;
	TurretBossState state;
	bool triggered;
};

#endif