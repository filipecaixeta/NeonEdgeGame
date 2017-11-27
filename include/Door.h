#ifndef DOOR_H_
#define DOOR_H_

#include "Interactive.h"
#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INTEGER_SIZE_MAX (2e31)-1
#define INTEGER_SIZE_MIN -2e31
#define MOVE_DOOR_HW 200
#define MOVE_DOOR_POSITION_XY 100

class Door : public Interactive {
private:
	bool doorOpen;

public:
	Door(int doorPositionX, int doorPositionY);
	~Door();
	void Trigger();
	void Update(TileMap* worldMap, float delayTime);
	void Render();
};

#endif  