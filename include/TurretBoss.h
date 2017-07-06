#ifndef TURRETBOSS_H_
#define TURRETBOSS_H_

#include "TurretPiece.h"
#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "TurretBossGraphicsComponent.h"

enum TurretBossState{tIDLE,tSPAWNING,tSHOOTING};

class TurretBoss : public Character
{
public:
	TurretBoss(int x, int y);
	~TurretBoss();
	void AddPiece(TurretPiece* piece);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	void Render();

private:

	std::vector<TurretPiece*> pieces; 
	Timer spawn;
	Timer shoot;
	Timer idle;
	Rect radius;
	TurretBossState state;
	bool triggered;
};

#endif