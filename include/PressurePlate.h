#ifndef PRESSUREPLATE_H_
#define PRESSUREPLATE_H_

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INTEGER_SIZE_MAX (2e31)-1
#define INTEGER_SIZE_MIN -2e31

#include "Interactive.h"

class PressurePlate : public Interactive
{
private:
	Interactive* door;

public:
	PressurePlate(int x, int y, Interactive* d);
	~PressurePlate();
	void Trigger();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
};

#endif
