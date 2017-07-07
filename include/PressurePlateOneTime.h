#ifndef PRESSUREPLATEONETIME_H_
#define PRESSUREPLATEONETIME_H_

#include "Interactive.h"

class PressurePlateOneTime : public Interactive
{
private:
	Interactive* door;
	
public:
	PressurePlateOneTime(int x, int y, Interactive* d);
	~PressurePlateOneTime();
	void Trigger();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
};

#endif 