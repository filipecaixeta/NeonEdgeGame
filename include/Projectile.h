#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "Attack.h"
#include "PhysicsComponent.h"
#include "Vec2.h"

class Projectile : public Attack
{
private:
	bool pierce;

public:
	Projectile(std::string file, int frames, int frameTime, GameObject* owner,
			   Vec2 speed, int lifetime, int power, bool pierce = false);
	~Projectile();
	void NotifyTileCollision(int tile, Face face);
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* world, float dt);
	void Render();

	PhysicsComponent physicsComponent;
};

#endif /* PROJECTILE_H_ */
