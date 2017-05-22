#ifndef NOTATTACK_H_
#define NOTATTACK_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class Notattack : public GameObject {
private:
	Sprite* sp;
	Timer lifetime;
	int power;

public:
	Notattack(std::string file, int frames, int x, int y, int power, int duration, Face facing);
	~Notattack();
	void Update(float dt);
	void UpdateTimers(float dt);
	void UpdatePosition(float dt);
	void UpdateSprite(std::string sprite);
	void Render();
	bool Is(std::string type);
	bool IsDead();
	Notattack* Get();
};

#endif /* NOTATTACK_H_ */
