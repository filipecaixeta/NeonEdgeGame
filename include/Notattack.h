#ifndef NOTATTACK_H_
#define NOTATTACK_H_

#include "GameObject.h"

class Notattack : public GameObject {
private:
	Timer lifetime;

public:
	Notattack(std::string file, int frames, int x, int y, int power, int duration, Face facing);
	~Notattack();
	void Update(float dt);
	void UpdateTimers(float dt);
	void UpdatePosition(float dt);
	void UpdateSprite(std::string sprite);
	void Render();
	bool NotifyTileCollision(Face face);
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	bool IsDead();
	Notattack* get();
};

#endif /* NOTATTACK_H_ */
