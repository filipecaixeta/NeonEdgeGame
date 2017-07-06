#ifndef DOOR_H_
#define DOOR_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class Door : public GameObject
{
private:
	
	bool locked;
	bool dead;

	
public:

	Sprite sp;
	bool hard;

	Door(int x, int y, std::string sprite, bool locked);
	~Door();
	bool IsDead();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 