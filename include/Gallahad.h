#ifndef GALLAHAD_H_
#define GALLAHAD_H_

#include "Timer.h"
#include "GallahadInputComponent.h"
#include "PhysicsComponent.h"
#include "GallahadGraphicsComponent.h"
#include "SaveComponent.h"

class Gallahad : public GameObject
{
private:
	int hitpoints = 10;
	Timer invincibilityTimer = Timer(800);

public:
	Gallahad(int x, int y);
	~Gallahad();
	bool IsDead();
	int GetHealth();
	void Damage(int damage);
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(float dt);
	void Render();

	GallahadInputComponent inputComponent;
	PhysicsComponent physicsComponent;
	GallahadGraphicsComponent graphicsComponent;
	SaveComponent &saveComponent;
};

#endif /* GALLAHAD_H_ */
