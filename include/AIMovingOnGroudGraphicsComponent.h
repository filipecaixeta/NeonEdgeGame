// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_AIMOVINGONGROUDGRAPHICSCOMPONENT_H_
#define INCLUDE_AIMOVINGONGROUDGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class AIMovingOnGroudGraphicsComponent: public GraphicsComponent {
 public:
    AIMovingOnGroudGraphicsComponent(std::string baseName_);
    ~AIMovingOnGroudGraphicsComponent();
    void Update(GameObject *gameObject, float deltaTime);
};

#endif  // INCLUDE_AIMOVINGONGROUDGRAPHICSCOMPONENT_H_
