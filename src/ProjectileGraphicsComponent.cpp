// Copyright (c) 2017 Neon Edge Game.

#include "ProjectileGraphicsComponent.h"
#include "Projectile.h"
#include "Rect.h"

ProjectileGraphicsComponent::ProjectileGraphicsComponent(std::string baseNameParam):
       GraphicsComponent(baseNameParam) {
    AddSprite(baseName, "Projectile", 4, 80);
    sprite = sprites["Projectile"];
    surface = surfaces["Projectile"];
}

ProjectileGraphicsComponent::~ProjectileGraphicsComponent() {
}

void ProjectileGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    characterLeftDirection = (gameObject->facing == GameObject::LEFT);

    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);
}
