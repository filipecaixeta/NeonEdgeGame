#ifndef ATTACK_H_
#define ATTACK_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Attack : public GameObject
{
private:
	Sprite* sp;
	Timer lifetime;
	int power;

public:
	Attack(std::string file, int frames, int x, int y, int power, int duration, Face facing);
	~Attack();
	bool IsDead();
	void UpdateTimers(float dt);
	void Update(float dt);
	void Render();
};

#endif /* ATTACK_H_ */
