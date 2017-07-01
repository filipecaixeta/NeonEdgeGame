#ifndef NOTFREDOSTATIONARY_H
#define NOTFREDOSTATIONARY_H

#include "Character.h"
#include "Timer.h"
#include "TileMap.h"
#include "NotFredoStationaryGraphicsComponent.h"

class NotFredoStationary : public Character
{
public:
    NotFredoStationary(int x, int y);
    ~NotFredoStationary();
    void Attack();
    void NotifyTileCollision(int tile, Face face);
    void NotifyObjectCollision(GameObject* other);
    void UpdateAI(float dt);
    void Update(TileMap* world, float dt);
    bool Is(std::string type);
private:
    Rect radius;
    Timer looking;
    Timer idle;
};

#endif // NOTFREDOSTATIONARY_H
