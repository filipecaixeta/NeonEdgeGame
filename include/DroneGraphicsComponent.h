// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_DroneGRAPHICSCOMPONENT_H_
#define INCLUDE_DroneGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "Character.h"
#include "GraphicsComponent.h"

class DroneGraphicsComponent: public GraphicsComponent {
 public:
    DroneGraphicsComponent(std::string baseNameParam);
    ~DroneGraphicsComponent();
    void Update(GameObject* gameObject, float deltaTime);
};

#endif  // INCLUDE_DroneGRAPHICSCOMPONENT_H_
