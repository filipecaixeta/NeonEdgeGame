#ifndef BOX_H_
#define BOX_H_

#include "Interactive.h"
#include "Sprite.h"
#include "Timer.h"
#include "PhysicsComponent.h"

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648


class Box : public Interactive {
private:
	int hitPoints = 0;
	Timer invincibilityTimer = NULL;
	void Update(TileMap* map, float dt);
	void UpdateTimers(float dt);
	void CharacterAction(Character* c);
	void OtherColision(GameObject* other);
	void NotifyObjectCollision(GameObject* other);
	void Trigger();	
	bool IsDead();
	
		
public:

	Box(int x, int y);
	~Box();
	int GetHealth();
	void Kill();
	
	PhysicsComponent physicsComponent = NULL;
};

#endif
