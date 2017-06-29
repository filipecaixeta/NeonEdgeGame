#ifndef BOX_H_
#define BOX_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "PhysicsComponent.h"

#include <vector>

class Box : public GameObject
{
private:
	Sprite sp;
	int hitpoints;
	
public:

	PhysicsComponent physicsComponent;

	Box(int x, int y, std::string sprite);
	~Box();
	bool IsDead();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 