#ifndef BOX_H_
#define BOX_H_

#include "Interactive.h"
#include "Sprite.h"
#include "Timer.h"
#include "PhysicsComponent.h"

class Box : public Interactive
{
private:
	int hitPoints;
	Timer invincibilityTimer;

public:

	Box(int x, int y);
	~Box();
	int GetHealth();
	void Kill();
	bool IsDead();
	void Trigger();
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);
	void OtherColision(GameObject* other);
	void CharacterAction( Character* c);

	PhysicsComponent physicsComponent;
};

#endif
