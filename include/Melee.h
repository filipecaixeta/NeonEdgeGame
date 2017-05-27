#ifndef MELEE_H_
#define MELEE_H_

#include "Attack.h"
#include "Sprite.h"
#include "Timer.h"

class Melee : public Attack
{
public:
	Melee(std::string file, int frames, int frameTime, Face facing, int duration, int power, GameObject* owner);
	~Melee();
	void Update(float dt);
	void Render();
};

#endif /* MELEE_H_ */