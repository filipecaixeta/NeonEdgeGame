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
    virtual void Damage(int damage);
    virtual void Attack();
    virtual bool Attacking();
    virtual bool Cooling();
    virtual void Empower(int pow);
    virtual int Power();
    virtual bool GetColisionData(SDL_Surface **surface_, SDL_Rect& clipRect_, Vec2& pos_,
                                 bool& mirror);
    virtual void NotifyTileCollision(int tile, Face face);
    virtual void NotifyObjectCollision(GameObject *other = NULL);
    virtual void UpdateTimers(float dt = 0);
    virtual bool OutOfBounds(TileMap *map = NULL);
    virtual void Update(TileMap *map = NULL, float dt = 0);
    virtual void Render();

    PhysicsComponent physicsComponent;
    GraphicsComponent *graphicsComponent;
    SoundComponent *soundComponent;
    SaveComponent saveComponent;

protected:
	int const INITIAL_VALUE = 0;
    int hitpoints = INITIAL_VALUE;
    int power = INITIAL_VALUE;
    Timer invincibilityTimer = INITIAL_VALUE;
    Timer attacking = INITIAL_VALUE;
    Timer attackCD = INITIAL_VALUE;
    Timer stunned = INITIAL_VALUE;
    int startingX = INITIAL_VALUE;
	int startingY = INITIAL_VALUE;
};

#endif // CHARACTER_H
