#ifndef PRESSUREPLATEONETIME_H_
#define PRESSUREPLATEONETIME_H_

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INTEGER_SIZE_MAX (2e31)-1
#define INTEGER_SIZE_MIN -2e31

#include "Interactive.h"

class PressurePlateOneTime : public Interactive {
private:
	~PressurePlateOneTime();
	Interactive* door;
	void Update(TileMap* map, float dt);
	void Trigger();
	void NotifyObjectCollision(GameObject* other);

public:
	PressurePlateOneTime(int x, int y, Interactive* d);
};

#endif
