#ifndef PRESSUREPLATE_H_
#define PRESSUREPLATE_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class PressurePlate : public GameObject
{
private:
	bool toggle;
	Sprite spOn;
	Sprite spOff;
	std::vector<std::vector<int>> onTiles;
	std::vector<std::vector<int>> offTiles;
	
public:
	PressurePlate(int x, int y, TileMap* world, std::string spriteOn, std::string spriteOff, std::vector<std::vector<int>> onTiles);
	~PressurePlate();
	bool IsDead();
	void Trigger(TileMap* map);
	void NotifyObjectCollision(GameObject* other);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 