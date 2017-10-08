#ifndef TURRET_H
#define TURRET_H

#include "Character.h"

class Turret : public Character {
public:
    Turret(int x, int y);
    ~Turret();
    void Attack();
    void NotifyTileCollision(int tile, Face face);
    void UpdateTimers(float deltaTime);
    void UpdateAI(float deltaTime);
    void Update(TileMap* world, float deltaTime);
    bool Is(std::string characterType);

private:
    Rect radius;
    Timer looking;
    Timer idle;
};

#endif // TURRET_H
