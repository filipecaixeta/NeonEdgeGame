#ifndef PHYSICSCOMPONENT_H
#define PHYSICSCOMPONENT_H

#define SOLID_TILE 0

#include "GameObject.h"
#include "TileMap.h"

class PhysicsComponent
{
public:
	Vec2 velocity = Vec2(0, 0.6);
	bool kinetic;

	PhysicsComponent(bool kinetic = false);
	void Update(GameObject* obj, TileMap *world, float dt);
	int TileCollision(GameObject* obj, TileMap* world, GameObject::Face face);
	int TileCollision(const GameObject* obj, Vec2 pos, TileMap* world, GameObject::Face face);
	void TileFix(GameObject* obj, TileMap* world, GameObject::Face face);
	void SetKinetic(bool kinetic);
};

#endif // PHYSICSCOMPONENT_H
