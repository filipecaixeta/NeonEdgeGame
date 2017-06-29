#ifndef DOOR_H_
#define DOOR_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class Door : public GameObject
{
private:
	Sprite sp;
	bool locked;
	bool dead;
	
public:
	Door(int x, int y, TileMap* world, std::string sprite, bool locked);
	~Door();
	bool IsDead();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 