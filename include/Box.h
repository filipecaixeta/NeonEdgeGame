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
	Timer triggerCooldown;	

public:

		int hitpoints;

	PhysicsComponent physicsComponent;

	Box(int x, int y, std::string sprite);
	~Box();
	bool IsDead();
	void Trigger(TileMap* map);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 