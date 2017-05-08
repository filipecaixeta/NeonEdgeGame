#ifndef NOTFREDO_H_
#define NOTFREDO_H_

#include "Notattack.h"

class Notfredo : public GameObject {
private:
	Rect radius = Rect();
	Timer looking;
	Timer idle;

public:
	Notfredo(int x, int y);
	~Notfredo();
	void Update(float dt);
	void UpdateTimers(float dt);
	void UpdatePosition(float dt);
	void UpdateSprite(std::string sprite);
	void Render();
	void Damage(int damage);
	bool NotifyTileCollision(Face face);
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	bool IsDead();
	Notfredo* get();
};

#endif /* NOTFREDO_H_ */
