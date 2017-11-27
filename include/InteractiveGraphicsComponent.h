// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_INTERACTIVEGRAPHICSCOMPONENT_H_
#define INCLUDE_INTERACTIVEGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"

class InteractiveGraphicsComponent: public GraphicsComponent {
 public:
    InteractiveGraphicsComponent(std::string baseNameParam);
    ~InteractiveGraphicsComponent();
    void Update(GameObject *gameObject, float deltaTime);
};

#endif  // INCLUDE_INTERACTIVEGRAPHICSCOMPONENT_H_
