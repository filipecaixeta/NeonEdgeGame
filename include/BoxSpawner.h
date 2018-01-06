#ifndef BOXSPAWNER_H_
#define BOXSPAWNER_H_

#include "GameObject.h"
#include "Box.h"

#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

class BoxSpawner : public GameObject
{
private:
	Box* spawn;

public:
	BoxSpawner(int x, int y);
	~BoxSpawner();
	void Update(TileMap* map, float dt);
	void Render();
};

#endif
