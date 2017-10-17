#ifndef INCLUDE_PROJECTILE_H_
#define INCLUDE_PROJECTILE_H_

#include "GameObject.h"
#include "Vec2.h"
#include "Timer.h"
#include "TileMap.h"
#include "PhysicsComponent.h"
#include "ProjectileGraphicsComponent.h"

#define FLOAT_SIZE_MAX 3.4e+38f
#define FLOAT_SIZE_MIN -3.4e+38f
#define INTEGER_SIZE_MAX (2e31)-1
#define INTEGER_SIZE_MIN -2e31


class Projectile : public GameObject {
 private:
    Timer lifetime = Timer();
    int power = 1;
    std::string ownerN;
    bool pierce;

 public:
    Projectile(GameObject* gameObject, Vec2 speed, int lifetime, int power, bool pierce = false);
    ~Projectile();
    bool IsDead();
    int Power();
    std::string GetOwner();
    bool GetColisionData(SDL_Surface **surface_, SDL_Rect &clipRect_, Vec2 &pos_,
                         bool &mirror);
    void NotifyTileCollision(int tile, Face face);
    void NotifyObjectCollision(GameObject *gameObject);
    void UpdateTimers(float deltaTime);
    void Update(TileMap* world, float deltaTime);
    void Render();

    PhysicsComponent physicsComponent;
    ProjectileGraphicsComponent *graphicsComponent;
};

#endif  // INCLUDE_PROJECTILE_H_
