#ifndef ATTACK_H_
#define ATTACK_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Attack : public GameObject {
private:
	Sprite* sp;
	Timer lifetime;
	int power;

public:
	Attack(std::string file, int frames, int x, int y, int power, int duration, Face facing);
	~Attack();
	void Update(float dt);
	void UpdateTimers(float dt);
	void Render();
	bool Is(std::string type);
	bool IsDead();
	Attack* Get();
};

#endif /* ATTACK_H_ */
