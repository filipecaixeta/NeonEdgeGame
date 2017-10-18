#ifndef ENERGY_H_
#define ENERGY_H_

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INTEGER_SIZE_MAX (2e31)-1
#define INTEGER_SIZE_MIN -2e31

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
