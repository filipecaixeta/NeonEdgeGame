#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "Player.h"
#include "GameObject.h"
#include "Sprite.h"

class Player;

class Item: public GameObject {
public:
    Item(int id, int x, int y);
    void Eval(Player *player);
    void SetActive(bool boolStatus);
    bool GetActive();

    bool Is(std::string stringItem);
    bool IsDead();

    void NotifyObjectCollision(GameObject *gameObject);

    void Update(TileMap *map, float deltaTime);
    void Render();

    Sprite *sprite;
    bool dead;
    std::string stringName;
    int id;

};
#endif // ITEM_H
