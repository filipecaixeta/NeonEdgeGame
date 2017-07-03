#ifndef PLATTFORM_H_
#define PLATTFORM_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class Plattform : public GameObject
{
private:
	Sprite sp;



public:

	int cycleCount;
	bool on;
	int route[10][3];

	Plattform(int x, int y, std::string sprite, int route[10][3]);
	~Plattform();
	bool IsDead();
	void Toggle();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 