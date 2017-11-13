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
    ~Projectile();
    Timer lifetime = Timer();
    int power = 1;
    std::string ownerN;
    bool pierce;

    void Render();
    void Update(TileMap* world, float deltaTime);
    void UpdateTimers(float deltaTime);
    void NotifyObjectCollision(GameObject *gameObject);
    void NotifyTileCollision(int tile, Face face);
    bool GetColisionData(SDL_Surface **surface_, SDL_Rect &clipRect_, Vec2 &pos_,
                         bool &mirror);

    PhysicsComponent physicsComponent;
    ProjectileGraphicsComponent *graphicsComponent;

 public:
    Projectile(GameObject* gameObject, Vec2 speed, int lifetime, int power, bool pierce = false);
    bool IsDead();
    int Power();
    std::string GetOwner();

};

#endif  // INCLUDE_PROJECTILE_H_
