// Copyright (c) 2017 Neon Edge Game.

#include "TurretPieceGraphicsComponent.h"
#include "TurretPiece.h"

TurretPieceGraphicsComponent::TurretPieceGraphicsComponent(std::string baseNameParam, int type):
       GraphicsComponent(baseNameParam) {
    switch (type) {
        case 0:
            AddSprite(baseName, "Head", 13, 80);
            sprite = sprites["Head"];
            surface = surfaces["Head"];
        break;
        case 1:
            AddSprite(baseName, "Body1", 9, 80);
            sprite = sprites["Body1"];
            surface = surfaces["Body1"];
        break;
        case 2:
            AddSprite(baseName, "Body2", 2, 80);
            sprite = sprites["Body2"];
            surface = surfaces["Body2"];
        break;
        case 3:
            AddSprite(baseName, "GunFront", 1, 80);
            sprite = sprites["GunFront"];
            surface = surfaces["GunFront"];
        break;
        case 4:
            AddSprite(baseName, "GunBack", 1, 80);
            sprite = sprites["GunBack"];
            surface = surfaces["GunBack"];
        break;
    }
}

TurretPieceGraphicsComponent::~TurretPieceGraphicsComponent() {
}

void TurretPieceGraphicsComponent::Update(GameObject *gameObject, float deltaTime) {
    characterLeftDirection = (gameObject->facing == GameObject::RIGHT);

    sprite->Mirror(characterLeftDirection);
    sprite->Update(deltaTime);
}
