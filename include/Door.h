#ifndef DOOR_H_
#define DOOR_H_

#include "Interactive.h"

class Door : public Interactive
{
private:
	bool open;

public:
	Door(int x, int y);
	~Door();
	void Trigger();
	void Update(TileMap* world, float dt);
	void Render();
};

#endif  