#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Timer.h"
#include "GraphicsComponent.h"
#include "SaveComponent.h"
#include "PhysicsComponent.h"
#include "InputComponent.h"

class InputComponent;
class GraphicsComponent;

class Character: public GameObject
{
public:
	Character(int x, int y);
	virtual ~Character();
	virtual bool IsDead();
	virtual int GetHealth();
	virtual int GetEnergy();
	virtual bool GetColisionData(SDL_Surface** surface_, SDL_Rect& clipRect_, Vec2& pos_, bool& mirror);
	virtual void Damage(int damage);
	virtual void Attack();
	virtual void Crouch();
	virtual void Stand();
	virtual bool Attacking();
	virtual bool Crouching();
	virtual void NotifyTileCollision(int tile, Face face);
	virtual void NotifyObjectCollision(GameObject* other);
	virtual void UpdateTimers(float dt);
	virtual void Update(TileMap* map,float dt);
	virtual void Render();
    virtual void CurrentTile(int* x,int* y,int* z);

	InputComponent* inputComponent;
	PhysicsComponent physicsComponent;
	GraphicsComponent* graphicsComponent;
	SaveComponent saveComponent;

protected:
	int hitpoints;
	int energy;
	Timer invincibilityTimer;
	Timer attacking;
	Timer regenerating;
	bool crouching;
};

#endif // CHARACTER_H
