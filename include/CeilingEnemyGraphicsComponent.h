// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_CEILINGENEMYGRAPHICSCOMPONENT_H_
#define INCLUDE_CEILINGENEMYGRAPHICSCOMPONENT_H_

#include "GraphicsComponent.h"
#include "Character.h"


class CeilingEnemyGraphicsComponent: public GraphicsComponent {
 public:
    CeilingEnemyGraphicsComponent(std::string baseNameParam);
    ~CeilingEnemyGraphicsComponent();
    void Update(GameObject* gameObject, float deltaTime);
};

#endif  // INCLUDE_CEILINGENEMYGRAPHICSCOMPONENT_H_
