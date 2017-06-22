#ifndef DRONE_H_
#define DRONE_H_

#include "Player.h"
#include "Timer.h"
#include "TileMap.h"
#include "DroneInputComponent.h"
#include "DroneGraphicsComponent.h"


class Drone : public Player
{
public:
	Drone(int x, int y);
	~Drone();
	void UpdateTimers(float dt);

private:
	
};

#endif /* DRONE_H_ */