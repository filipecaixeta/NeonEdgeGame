// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_INTERACTIVE_H_
#define INCLUDE_INTERACTIVE_H_

#include "GameObject.h"
#include "InteractiveGraphicsComponent.h"

#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

class Interactive : public GameObject {
 private:
    bool state;
    int startingX, startingY;

 public:
    Interactive(int x, int y, std::string name);
    virtual ~Interactive();
    virtual void On();
    virtual void Off();
    virtual bool Active();
    virtual void Trigger() = 0;
    virtual bool GetColisionData(SDL_Surface **surface_, SDL_Rect &clipRect_, Vec2 &pos_,
                                 bool &mirror);
    virtual void NotifyObjectCollision(GameObject* other);
    virtual bool OutOfBounds(TileMap* map);
    virtual void Update(TileMap* map, float deltaTime);
    virtual void Render();

    InteractiveGraphicsComponent* graphicsComponent;
};

#endif  // INCLUDE_INTERACTIVE_H_
