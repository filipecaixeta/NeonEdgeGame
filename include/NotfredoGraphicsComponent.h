// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_NOTFREDOGRAPHICSCOMPONENT_H_
#define INCLUDE_NOTFREDOGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class NotfredoGraphicsComponent: public GraphicsComponent {
 public:
    NotfredoGraphicsComponent(std::string baseNameParam);
    ~NotfredoGraphicsComponent();
    void Update(GameObject *gameObject, float deltaTime);
};

#endif  // INCLUDE_NOTFREDOGRAPHICSCOMPONENT_H_
