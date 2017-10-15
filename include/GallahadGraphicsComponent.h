// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_GALLAHADGRAPHICSCOMPONENT_H_
#define INCLUDE_GALLAHADGRAPHICSCOMPONENT_H_

#include <string>
#include "Vec2.h"
#include "Sprite.h"
#include "GraphicsComponent.h"
#include "Character.h"
#define FRAME_COUNT 8
#define HALF_FRAME_COUNT 4
#define FRAME_TIME 80
#define FRAME_TIME_DYING 100
#define GALLAHAD_VELOCITY_ZERO 0
#define GALLAHAD_HIDE_POWER_ACTIVED 0.3f
#define GALLAHAD_HIDE_POWER_DISABLED 1

class GallahadGraphicsComponent: public GraphicsComponent {
 public:
    GallahadGraphicsComponent(std::string baseNameParam);
    ~GallahadGraphicsComponent();
    void Update(GameObject *gameObject, float deltaTime);
    void UpdateCharacterSpriteToShooting(GameObject *gameObject);
    void UpdateCharacterSpriteToCrouching(GameObject *gameObject);
    void UpdateCharacterSpriteToActive(GameObject *gameObject);
    void UpdateCharacterSpriteToHiding(GameObject *gameObject, Sprite *sprite);
    void UpdateCharacterSpriteToDying(GameObject *gameObject);
};

#endif  // INCLUDE_GALLAHADGRAPHICSCOMPONENT_H_
