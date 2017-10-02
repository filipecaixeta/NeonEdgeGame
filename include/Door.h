#ifndef DOOR_H_
#define DOOR_H_

#include "Interactive.h"

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