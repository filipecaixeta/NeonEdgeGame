#ifndef LANCELOT_H_
#define LANCELOT_H_

#include "Timer.h"
#include "LancelotInputComponent.h"
#include "PhysicsComponent.h"
#include "LancelotGraphicsComponent.h"
#include "SaveComponent.h"
#include "TileMap.h"

class Lancelot : public GameObject
{
private:
	int hitpoints = 10;
	int energy = 5;
	Timer invincibilityTimer = Timer(500);
	Timer attacking = Timer(500);
	Timer blocking = Timer(1000);
	Timer regenerating = Timer(500);
	bool crouching = false;

public:
	Lancelot(int x, int y);
	~Lancelot();
	bool IsDead();
	int GetHealth();
	int GetEnergy();
	void Damage(int damage);
	void Attack();
	void Block();
	void Crouch();
	void Stand();
	bool Attacking();
	bool Blocking();
	bool Crouching();
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* world, float dt);
	void Render();

	LancelotInputComponent inputComponent;
	PhysicsComponent physicsComponent;
	LancelotGraphicsComponent graphicsComponent;
	SaveComponent saveComponent;
};

#endif /* LANCELOT_H_ */
