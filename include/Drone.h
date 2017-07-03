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
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);
	void SetActive(bool active);
	bool GetActive();
	bool Is(std::string type);
	bool IsDead();

private:
	bool active;
	bool dead;
};

#endif /* DRONE_H_ */
