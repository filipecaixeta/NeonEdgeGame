#ifndef LEVER_H_
#define LEVER_H_

#include "GameObject.h"
#include "Plattform.h"
#include "Sprite.h"
#include "Timer.h"
#include <vector>

class Lever : public GameObject
{
private:
	Sprite sp;
	/*std::vector<std::vector<int>> onTiles;
	std::vector<std::vector<int>> offTiles;*/
	Timer triggerCooldown;
	std::vector<Plattform*> plattform;
	
public:
	//Lever(int x, int y, TileMap* world, std::string sprite, std::vector<std::vector<int>> onTiles);
	Lever(int x, int y, std::string sprite, std::vector<Plattform*> plattform);
	~Lever();
	bool IsDead();
	//void Trigger(TileMap* map);
	void Trigger(TileMap* map, float dt);
	void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void Update(TileMap* map, float dt);
	void Render();
};

#endif 