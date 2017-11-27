// Copyright (c) 2017 Neon Edge Game.

#include "CeilingEnemyGraphicsComponent.h"

CeilingEnemyGraphicsComponent::CeilingEnemyGraphicsComponent(std::string baseNameParam):
    GraphicsComponent(baseNameParam) {
    AddSprite(baseName, "Idle", 6, 80);
    sprite = sprites["Idle"];
    surface = surfaces["Idle"];
}

CeilingEnemyGraphicsComponent::~CeilingEnemyGraphicsComponent() {
}

void CeilingEnemyGraphicsComponent::Update(GameObject* gameObject, float deltaTime) {
    UpdateSprite(gameObject, "Idle");
    sprite->Update(deltaTime);
}
