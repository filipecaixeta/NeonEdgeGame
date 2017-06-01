#ifndef NOTFREDO_H_
#define NOTFREDO_H_

#include "Timer.h"
#include "NotfredoGraphicsComponent.h"
#include "TileMap.h"
#include "Character.h"

class Notfredo : public Character
{
public:
	Notfredo(int x, int y);
	~Notfredo();
	void Attack();
	void NotifyTileCollision(int tile, Face face);
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	bool Is(std::string type);
private:
	Rect radius;
	Timer looking;
	Timer idle;
};

#endif /* NOTFREDO_H_ */
