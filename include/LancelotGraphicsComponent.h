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
    void Update(GameObject* gameObject, float deltaTime);
    void UpdateCharacterSpriteToAttacking(GameObject *gameObject);
    void UpdateCharacterSpriteToBlocking(GameObject *gameObject);
    void UpdateCharacterSpriteToCrouching(GameObject *gameObject);
    void UpdateCharacterSpriteToDying(GameObject *gameObject);
};

#endif  // INCLUDE_LANCELOTGRAPHICSCOMPONENT_H_
