#ifndef MELEE_H_
#define MELEE_H_

#include "Attack.h"

class Melee : public Attack
{
public:
	Melee(std::string file, int frames, int frameTime, GameObject* owner, int lifetime, int power);
	~Melee();
	void Update(TileMap* world, float dt);
	void Render();
};

#endif /* MELEE_H_ */
