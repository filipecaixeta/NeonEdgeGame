#ifndef ENERGY_H_
#define ENERGY_H_

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INT_MIN_SIZE -32768
#define INT_MAX_SIZE 32767

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Energy : public GameObject
{
private:
	Sprite sprite;
	Timer endTimer;
	bool loops = false;
	bool dies = false;
	bool dead = false;
	void Update(TileMap* world, float deltaTime = 0.0);
	void Render();
	void NotifyObjectCollision(GameObject* collapsed_object = NULL);
	void UpdateTimers(float deltaTime);
	Energy(int x_axis_position, int y_axis_position, std::string sprite, float frameCount = 1, float frameTime = 0,
		bool loops = true, float lifetime = 0, bool dies = false);
 ~Energy();
 bool IsDead();

public:
	
	
	
};

#endif /* ENERGY_H_ */
