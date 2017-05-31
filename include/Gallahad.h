#ifndef GALLAHAD_H_
#define GALLAHAD_H_

#include "Timer.h"
#include "GallahadInputComponent.h"
#include "PhysicsComponent.h"
#include "GallahadGraphicsComponent.h"
#include "SaveComponent.h"
#include "TileMap.h"

class Gallahad : public GameObject
{
private:
	int hitpoints = 10;
	int energy = 5;
	Timer invincibilityTimer = Timer(500);
	Timer attacking = Timer(500);
	Timer hiding = Timer(1500);
	Timer regenerating = Timer(500);
	bool crouching = false;

public:
	Gallahad(int x, int y);
	~Gallahad();
	bool IsDead();
	int GetHealth();
	int GetEnergy();
	bool GetColisionData(SDL_Surface** surface_, SDL_Rect& clipRect_, Vec2& pos_, bool& mirror);
	void Damage(int damage);
	void Attack();
	void Hide();
	void Crouch();
	void Stand();
	bool Attacking();
	bool Hiding();
	bool Crouching();
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* world,float dt);
	void Render();

	GallahadInputComponent inputComponent;
	PhysicsComponent physicsComponent;
	GallahadGraphicsComponent graphicsComponent;
	SaveComponent saveComponent;
};

#endif /* GALLAHAD_H_ */
