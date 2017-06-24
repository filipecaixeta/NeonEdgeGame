#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "Player.h"
#include "GameObject.h"
#include "Sprite.h"

class Player;

class Item: public GameObject
{
public:
	Item(int id, int x, int y);
	Item(const Item& obj);
	void Eval(Player *player);
	void SetActive(bool b);
	bool GetActive();

	bool Is(std::string type);
	bool IsDead();

	void NotifyObjectCollision(GameObject* other);

	void Update(TileMap* map, float dt);
	void Render();

	Sprite* sp;
	bool dead;
	std::string name;

};
#endif // ITEM_H
