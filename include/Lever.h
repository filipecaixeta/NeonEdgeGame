#ifndef LEVER_H_
#define LEVER_H_

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class Lever : public GameObject
{
private:
	Sprite sp;
	std::vector<std::vector<int>> onTiles;
	std::vector<std::vector<int>> offTiles;
	Timer triggerCooldown;
	
public:
	Lever(int x, int y, TileMap* world, std::string sprite, std::vector<std::vector<int>> onTiles);
	~Lever();
	bool IsDead();
	void Trigger(TileMap* map);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 