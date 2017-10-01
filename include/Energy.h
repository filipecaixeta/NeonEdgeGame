#ifndef ENERGY_H_
#define ENERGY_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Energy : public GameObject
{
private:
	Sprite sprite;
	Timer endTimer;
	bool loops;
	bool dies;
	bool dead = false;

public:
	Energy(int x_axis_position, int y_axis_position, std::string sprite, float frameCount = 1, float frameTime = 0,
		   bool loops = true, float lifetime = 0, bool dies = false);
	~Energy();
	bool IsDead();
	void NotifyObjectCollision(GameObject* collapsed_object);
	void UpdateTimers(float deltaTime);
	void Update(TileMap* world, float deltaTime);
	void Render();
};

#endif /* ENERGY_H_ */
