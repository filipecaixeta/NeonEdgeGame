// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_PROJECTILEGRAPHICSCOMPONENT_H_
#define INCLUDE_PROJECTILEGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"

class ProjectileGraphicsComponent: public GraphicsComponent {
 public:
    ProjectileGraphicsComponent(std::string baseNameParam);
    ~ProjectileGraphicsComponent();
    void Update(GameObject* gameObject, float deltaTime);
};

#endif // INCLUDE_PROJECTILEGRAPHICSCOMPONENT_H_
