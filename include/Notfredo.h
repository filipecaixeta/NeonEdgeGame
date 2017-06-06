#ifndef NOTFREDO_H_
#define NOTFREDO_H_

#include "Timer.h"
#include "NotfredoGraphicsComponent.h"
#include "TileMap.h"
#include "Character.h"

#define MAX_VALUE 10000;

typedef struct Node node;

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
    void PathFind();
private:
    node* New(int x,int y,int z);
    node* Pop(node* stack);
    void Push(int x,int y,int z,node* stack);
	Rect radius;
	Timer looking;
	Timer idle;
};

#endif /* NOTFREDO_H_ */
