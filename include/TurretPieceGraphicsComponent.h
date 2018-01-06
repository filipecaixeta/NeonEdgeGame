// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_TURRETPIECEGRAPHICSCOMPONENT_H_
#define INCLUDE_TURRETPIECEGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"

#define FLOAT_MIN_SIZE -3.4e+38f
#define FLOAT_MAX_SIZE 3.4e+38f
#define INT_SIZE_MAX 2147483647
#define INT_SIZE_MIN -2147483648

class TurretPieceGraphicsComponent: public GraphicsComponent {
 public:
    TurretPieceGraphicsComponent(std::string baseNameParam, int turretType);
    ~TurretPieceGraphicsComponent();
    void Update(GameObject* gameObject, float deltaTime);
};

#endif  // INCLUDE_TURRETPIECEGRAPHICSCOMPONENT_H_
