#ifndef LIFE_H_
#define LIFE_H_
#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Life : public GameObject
{
private:
	Sprite lifeSprite;
	Timer endTimer;
	bool loops;
	bool dies;
	bool isDead = false;

public:
	Life(int x, int y, std::string sprite, float frameCount = 1, float frameTime = 0,
		   bool loops = true, float lifeTime = 0, bool dies = false);
	~Life();
	bool IsDead();
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* world, float dt);
	void Render();
};

#endif /* Life_H_ */
