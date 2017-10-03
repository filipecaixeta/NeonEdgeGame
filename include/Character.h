#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"
#include "Timer.h"
#include "PhysicsComponent.h"
#include "GraphicsComponent.h"
#include "SaveComponent.h"
#include "SoundComponent.h"

class GraphicsComponent;

class Character : public GameObject {
public:
    Character(int x, int y);
    virtual ~Character();
    virtual bool IsDead();
    virtual bool IsCharacter();
    virtual int GetHealth();
    virtual void Damage(int damageReceived);
    virtual void Attack();
    virtual bool Attacking();
    virtual bool Cooling();
    virtual void Empower(int powerAmount);
    virtual int CharacterPower();
    virtual bool GetColisionData(SDL_Surface **surface, SDL_Rect &clipRect, Vec2 &position,
                                 bool &mirror);
    virtual void NotifyTileCollision(int tile, Face face);
    virtual void NotifyObjectCollision(GameObject *gameObject);
    virtual void UpdateTimers(float deltaTime);
    virtual bool OutOfBounds(TileMap *map);
    virtual void Update(TileMap *map,float deltaTime);
    virtual void Render();

    PhysicsComponent physicsComponent;
    GraphicsComponent *graphicsComponent;
    SoundComponent *soundComponent;
    SaveComponent saveComponent;

protected:
    int characterHealthPoints;
    int characterPowerPoints;
    Timer invincibilityTimer;
    Timer attacking;
    Timer coolDownAttack;
    Timer stunned;
    int startingX;
    int startingY;
};

#endif // CHARACTER_H
