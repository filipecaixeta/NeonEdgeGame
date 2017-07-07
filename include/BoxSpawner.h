#ifndef BOXSPAWNER_H_
#define BOXSPAWNER_H_

#include "GameObject.h"
#include "Box.h"

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