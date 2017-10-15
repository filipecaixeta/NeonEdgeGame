// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_TURRETPIECEGRAPHICSCOMPONENT_H_
#define INCLUDE_TURRETPIECEGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

class TurretPieceGraphicsComponent: public GraphicsComponent {
 public:
    TurretPieceGraphicsComponent(std::string baseNameParam, int type);
    ~TurretPieceGraphicsComponent();
    void Update(GameObject* gameObject, float deltaTime);
};

#endif  // INCLUDE_TURRETPIECEGRAPHICSCOMPONENT_H_
