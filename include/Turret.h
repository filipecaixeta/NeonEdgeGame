#ifndef TURRET_H
#define TURRET_H

#include "Character.h"

class Turret : public Character
{
public:
	Turret(int x, int y);
	~Turret();
	void Attack();
	void NotifyTileCollision(int tile, Face face);
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	bool Is(std::string type);

private:
	Rect radius;
	Timer looking;
	Timer idle;
};

#endif // TURRET_H
