#ifndef MINIFREDO_H_
#define MINIFREDO_H_

#include "GameObject.h"

class Minifredo : public GameObject{
private:
	bool dead = false;

public:
	bool mf = false;
	bool perched = true;

	Minifredo();
	~Minifredo();
	void Update(float dt);
	void Render();
	bool NotifyTileCollision(Face face);
	void NotifyCollision(GameObject* other);
	bool Is(std::string type);
	bool IsDead();
	Minifredo* get();
};

#endif /* MINIFREDO_H_ */
