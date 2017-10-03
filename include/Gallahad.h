#ifndef GALLAHAD_H_
#define GALLAHAD_H_

#include "Drone.h"
#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "GallahadInputComponent.h"
#include "GallahadGraphicsComponent.h"
#include "Drone.h"

class Gallahad : public Player
{
public:
	Gallahad(ItensManager* itemManager, int x, int y, GameObject* setDrone);
	~Gallahad();
	void Attack();
	void StartHiding();
	void StartShooting();
	void StopShooting();
	bool IsHiding();
	bool IsShooting();
	void Activate(bool on);
	bool Active();
	Drone* GetDrone();
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);

private:
	GameObject* drone;
	Timer isHiding;
	bool isShooting;
	bool active;
	bool done = false;
};

#endif /* GALLAHAD_H_ */
