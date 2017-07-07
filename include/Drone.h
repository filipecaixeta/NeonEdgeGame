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
	Drone(ItensManager* itemManager, int x, int y);
	~Drone();
	void Attack();
	void Activate(bool on);
	bool Active();
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);

private:
	bool active;
};

#endif /* DRONE_H_ */
