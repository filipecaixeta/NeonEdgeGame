#ifndef LIFE_H_
#define LIFE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Life : public GameObject
{
private:
	Sprite sp;
	Timer endTimer;
	bool loops;
	bool dies;
	bool dead = false;

public:
	Life(int x, int y, std::string sprite, float frameCount = 1, float frameTime = 0,
		   bool loops = true, float lifetime = 0, bool dies = false);
	~Life();
	bool IsDead();
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* world, float dt);
	void Render();
};

#endif /* Life_H_ */
