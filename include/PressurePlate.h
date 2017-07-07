#ifndef PRESSUREPLATE_H_
#define PRESSUREPLATE_H_

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