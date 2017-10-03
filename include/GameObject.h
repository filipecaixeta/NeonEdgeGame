#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <string>

#include "Rect.h"
#include "Vec2.h"
#include "TileMap.h"
#include "Timer.h"

class GameObject {
public:
    enum Face : short int {UPPER, BOTTOM, LEFT, RIGHT, SPECIAL};
    enum Footing : short int {GROUNDED, LEFT_WALLED, RIGHT_WALLED, AIRBORNE};

    std::string name = "GameObject";
    Rect box = Rect();
    Face facing = RIGHT;
    Footing footing = GROUNDED;
    Footing lastFooting = AIRBORNE;
    Timer dieTimer = Timer(1000);
    bool isDead = false;

    virtual ~GameObject() = 0;
    virtual bool Is(std::string type);
    virtual bool IsDead();
    virtual bool IsCharacter();
    virtual bool IsPlayer();
    virtual Vec2 GetPosition();
    virtual void SetPosition(Vec2 position);
    virtual void NotifyTileCollision(int tile, Face face);
    virtual void NotifyObjectCollision(GameObject* gameObject);
    virtual void SolidColision(GameObject* gameObject);
    virtual bool GetColisionData(SDL_Surface** surface, SDL_Rect &clipRect, Vec2 &position, bool &mirror);
    virtual void Update(TileMap* map, float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void DieAnimation();
};

#endif /* GAMEOBJECT_H_ */
