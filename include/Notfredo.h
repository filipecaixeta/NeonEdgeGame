#ifndef NOTFREDO_H_
#define NOTFREDO_H_

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "NotfredoGraphicsComponent.h"

#define MAX_VALUE 10000;

typedef struct Node node;

enum Type{FLYING,GROUND};

class Notfredo : public Character
{
public:
    Notfredo(int x, int y,Type type);
	~Notfredo();
	void Attack();
	void NotifyTileCollision(int tile, Face face);
    void NotifyObjectCollision(GameObject* other);
	void UpdateTimers(float dt);
	void UpdateAI(float dt);
	void Update(TileMap* world, float dt);
	bool Is(std::string type);
    node* PathFind();
    
private:
    node* New(int x,int y,int z,float physical_distance);
    node* Pop(node* stack);
    void Push(int x,int y,int z,node* stack,float physical_distance);
    void QuickSort(node* tileStack,int start,int end);
    void CopyNode(node* source,node* target);
	Rect radius;
	Timer looking;
    Timer idle;
    node* Find(node *tileStack, int x, int y);
    Type type;
};

#endif /* NOTFREDO_H_ */
