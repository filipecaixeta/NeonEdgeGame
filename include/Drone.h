#ifndef DRONE_H_
#define DRONE_H_

#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "DroneInputComponent.h"
#include "DroneGraphicsComponent.h"

#define MAX_FLOAT 3.4e+38f
#define MIN_FLOAT  -3.4e+38f
#define MAX_INT 3767.0f
#define MIN_INT -3767.0f


class Drone : public Player {
public:
	Drone(ItemsManager* itemManager, int dronePositionX, int dronePositionY);
	~Drone();
	void DroneActivate(bool on);
	bool isActive();

private:
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);
	void FollowsCharacter(bool droneActive);

void Attack();
	bool droneActive = false;
};

#endif /* DRONE_H_ */
