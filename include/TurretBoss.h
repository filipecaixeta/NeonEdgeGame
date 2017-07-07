#ifndef TURRETBOSS_H_
#define TURRETBOSS_H_

#include "TurretPiece.h"
#include "Character.h"
#include "Timer.h"
#include "TileMap.h"

enum TurretBossState{tIDLE,tAIMING,tSHOOTING};

class TurretBoss : public Character
{
public:
	TurretBoss(int x, int y);
	~TurretBoss();
	void AddPiece(TurretPiece* piece);
	void AddTurret(TurretPiece* turret);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	void Render();

private:
	std::vector<TurretPiece*> pieces;
	std::vector<TurretPiece*> turrets;
	int turret1;
	int turret2;
	Rect radius;
	bool triggered;
	TurretBossState state;
	Timer idle;
	Timer aim;
	Timer shoot;
};

#endif