#ifndef HANDSCANNER_H_
#define HANDSCANNER_H_

#include "Interactive.h"

class HandScanner : public Interactive
{
private:
	Interactive* door;
	
public:
	HandScanner(int x, int y, Interactive* d);
	~HandScanner();
	void Trigger();
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
};

#endif 