#ifndef NOTFREDO_H_
#define NOTFREDO_H_

#include "Timer.h"
#include "PhysicsComponent.h"
#include "LancelotGraphicsComponent.h"
#include "TileMap.h"

class Notfredo : public GameObject
{
private:
	int hitpoints = 5;
	Timer invincibilityTimer = Timer(500);

	Rect radius = Rect();
	Timer looking = Timer(1500);
	Timer idle = Timer(1500);
	
	PhysicsComponent physicsComponent;
	LancelotGraphicsComponent graphicsComponent;

public:
	Notfredo(int x, int y);
	~Notfredo();
	bool IsDead();
	void Damage(int damage);
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	void Render();

};

#endif /* NOTFREDO_H_ */
