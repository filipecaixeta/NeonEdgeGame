#ifndef TURRET_H
#define TURRET_H

#include "Character.h"

class Turret : public Character
{
public:
	Turret(int x, int y);
	void Update(TileMap* map,float dt);
	void UpdateAI(TileMap* map,float dt);
};

#endif // TURRET_H
