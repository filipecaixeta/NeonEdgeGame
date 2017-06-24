#ifndef ITEM_H
#define ITEM_H
#include "Player.h"
#include "GameObject.h"
#include "Sprite.h"

class Item: public GameObject
{
public:
	Item(int id, int x, int y);
	void Eval(Player *player);
	void SetActive(bool b);
	bool GetActive();

	bool Is(std::string type);
	bool IsDead();

	void NotifyObjectCollision(GameObject* other);

	void Update(TileMap* map, float dt);
	void Render();

protected:
	Sprite sp;
	bool dead;
};

#endif // ITEM_H
