#ifndef BOXSPAWNER_H_
#define BOXSPAWNER_H_

#include "GameObject.h"
#include "Box.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class BoxSpawner : public GameObject
{
private:
	Box* spawn;
	int x, y;
public:
	BoxSpawner(int x, int y);
	~BoxSpawner();
	bool IsDead();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 