#ifndef NOTFREDO_H_
#define NOTFREDO_H_

#include "Timer.h"
#include "PhysicsComponent.h"
#include "NotfredoGraphicsComponent.h"
#include "TileMap.h"

class Notfredo : public GameObject
{
private:
	int hitpoints = 5;
	Timer invincibilityTimer = Timer(500);
	Timer attacking = Timer(1000);

	Rect radius = Rect();
	Timer looking = Timer(1500);
	Timer idle = Timer(1500);

public:
	Notfredo(int x, int y);
	~Notfredo();
	bool IsDead();
	void Damage(int damage);
	void Attack();
	bool Attacking();
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	void Render();

	PhysicsComponent physicsComponent;
	NotfredoGraphicsComponent graphicsComponent;
};

#endif /* NOTFREDO_H_ */
