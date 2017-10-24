// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_LANCELOTGRAPHICSCOMPONENT_H_
#define INCLUDE_LANCELOTGRAPHICSCOMPONENT_H_

#include <string>

#include "Vec2.h"
#include "Rect.h"
#include "Sprite.h"
#include "Character.h"
#include "GraphicsComponent.h"
#define FRAME_TIME 80
#define LANCELOT_VELOCITY_ZERO 0



class LancelotGraphicsComponent: public GraphicsComponent {
 public:
    LancelotGraphicsComponent(std::string baseNameParam);
    ~LancelotGraphicsComponent();
    void Update(GameObject* gameObject = NULL, float deltaTime = 0.0);
    void UpdateCharacterSpriteToAttacking(GameObject *gameObject = NULL);
    void UpdateCharacterSpriteToBlocking(GameObject *gameObject = NULL);
    void UpdateCharacterSpriteToCrouching(GameObject *gameObject = NULL);
    void UpdateCharacterSpriteToDying(GameObject *gameObject = NULL);
};

#endif  // INCLUDE_LANCELOTGRAPHICSCOMPONENT_H_
