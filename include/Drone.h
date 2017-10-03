#ifndef DRONE_H_
#define DRONE_H_

#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "DroneInputComponent.h"
#include "DroneGraphicsComponent.h"


class Drone : public Player {
public:
	Drone(ItensManager* itemManager, int dronePositionX, int dronePositionY);
	~Drone();
	void Attack();
	void DroneActivate(bool on);
	bool isActive();
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);

private:
	bool droneActive;
};

#endif /* DRONE_H_ */
