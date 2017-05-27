#ifndef LANCELOT_H_
#define LANCELOT_H_

#include "Timer.h"
#include "LancelotInputComponent.h"
#include "PhysicsComponent.h"
#include "LancelotGraphicsComponent.h"
#include "SaveComponent.h"

class Lancelot : public GameObject
{
private:
	int hitpoints = 10;
	Timer invincibilityTimer = Timer(500);
	Timer attacking = Timer(500);

public:
	Lancelot(int x, int y);
	~Lancelot();
	bool IsDead();
	int GetHealth();
	void Damage(int damage);
	void Attack();
	bool Attacking();
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(float dt);
	void Render();

	LancelotInputComponent inputComponent;
	PhysicsComponent physicsComponent;
	LancelotGraphicsComponent graphicsComponent;
	SaveComponent &saveComponent;
};

#endif /* LANCELOT_H_ */
