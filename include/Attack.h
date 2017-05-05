#ifndef ATTACK_H_
#define ATTACK_H_

#include "GameObject.h"

class Attack : public GameObject {
private:
	Timer lifetime;

public:
	Attack(std::string file, int frames, int x, int y, int power, int duration, Face facing);
	~Attack();
	void Update(float dt);
	void UpdateTimers(float dt);
	void UpdatePosition(float dt);
	void UpdateSprite(std::string sprite);
	void Render();
	bool NotifyTileCollision(Face face);
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	bool IsDead();
	Attack* get();
};

#endif /* ATTACK_H_ */
