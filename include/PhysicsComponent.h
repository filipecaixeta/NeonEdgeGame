#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#define SOLID_TILE 6

#include "GameObject.h"

class PhysicsComponent
{
public:
	PhysicsComponent();
	void Update(GameObject* obj, float dt);
	int TileCollision(GameObject* obj, GameObject::Face face);
};

#endif // PHYSICSCOMPONENT_H
