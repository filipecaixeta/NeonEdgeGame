#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#define SOLID_TILE 6

#include "GameObject.h"

class PhysicsComponent
{
public:
	Vec2 velocity = Vec2(0, 0.6);
	bool kinetic;

	PhysicsComponent(bool kinetic = false);
	void Update(GameObject* obj, float dt);
	int TileCollision(GameObject* obj, GameObject::Face face);
};

#endif // PHYSICSCOMPONENT_H
