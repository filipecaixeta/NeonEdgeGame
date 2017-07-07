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
	Gallahad(ItensManager* itemManager, int x, int y, GameObject* d);
	~Gallahad();
	void Attack();
	void Hide();
	void Shoot();
	void Hold();
	bool Hiding();
	bool Shooting();
	void Activate(bool on);
	bool Active();
	Drone* GetDrone();
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);

private:
	GameObject* drone;
	Timer hiding;
	bool shooting;
	bool active;
	bool done = false;
};

#endif /* GALLAHAD_H_ */
