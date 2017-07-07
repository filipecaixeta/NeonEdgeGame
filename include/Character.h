#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Timer.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "SaveComponent.h"

class GraphicsComponent;

class Character : public GameObject
{
public:
	Character(int x, int y);
	virtual ~Character();
	virtual bool IsDead();
	virtual bool IsCharacter();
	virtual int GetHealth();
	virtual void Damage(int damage);
	virtual void Attack();
	virtual bool Attacking();
	virtual bool Cooling();
	virtual void Empower(int pow);
	virtual int Power();
	virtual bool GetColisionData(SDL_Surface** surface_, SDL_Rect& clipRect_, Vec2& pos_, bool& mirror);
	virtual void NotifyTileCollision(int tile, Face face);
	virtual void NotifyObjectCollision(GameObject* other);
	virtual void UpdateTimers(float dt);
	virtual bool OutOfBounds(TileMap* map);
	virtual void Update(TileMap* map,float dt);
	virtual void Render();

	PhysicsComponent physicsComponent;
	GraphicsComponent* graphicsComponent;
	SaveComponent saveComponent;

protected:
	int hitpoints;
	int power;
	Timer invincibilityTimer;
	Timer attacking;
	Timer attackCD;
	int startingX, startingY;
};

#endif // CHARACTER_H
