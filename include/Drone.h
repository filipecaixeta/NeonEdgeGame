#ifndef DRONE_H_
#define DRONE_H_

#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "DroneInputComponent.h"
#include "DroneGraphicsComponent.h"
#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f


class Drone : public Player {
public:
	Drone(ItemsManager* itemManager, int dronePositionX, int dronePositionY);
	~Drone();
	void Attack();
	void DroneActivate(bool on);
	bool isActive();
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);
	void FollowsCharacter(bool droneActive);

private:
	bool droneActive = false;
};

#endif /* DRONE_H_ */
