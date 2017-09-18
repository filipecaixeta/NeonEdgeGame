/**
  Copyright 2017 Neon Edge Game
  File Name: TurretPiece.cpp
  Header File Name: TurretPiece.h
  Class Name: TurretPiece
  Objective: Defines the behavior and actions of a piece of the TurretBoss.
*/

#include <cmath>
#include <math.h>

#include "TurretPiece.h"
#include "StageState.h"
#include "Camera.h"
#include "Player.h"
#include "Projectile.h"

/**
    Objective: Constructor of the class TurretPiece.
    @param Character *center.
    @param int x - Size in x of the TurretPiece.
    @param int y - Size in y of the TurretPiece.
    @param int type.
    @return instance of TurretPiece
*/
TurretPiece::TurretPiece(Character* center, int x, int y, int type):
    Character(0, 0) {
        name = "TurretBoss";
        this->center = center;
        this->type = type;
        facing = center->facing;
        refX = x;
        refY = y;
        physicsComponent.SetKinetic(true);
        graphicsComponent = new TurretPieceGraphicsComponent("TurretBoss", type);
        Vec2 size = graphicsComponent->GetSize();
        box.SetXY(Vec2(center->box.GetCenter().x + refX - (size.x / 2), center->box.GetCenter().y + refY - (size.y / 2)));
        box.SetWH(size);
        rotation = 0;
}

TurretPiece::~TurretPiece() {
}

/**
    Objective: Defines the behavior of shoot of the TurretPiece.
    @param none.
    @return void.
*/
void TurretPiece::Shoot() {
    if (type > 2) {
        float Vx = cos(rotation * M_PI / 180) * 0.6;
        float Vy = sin(rotation * M_PI / 180) * 0.6;
        StageState::AddObject(new Projectile(this, Vec2(Vx, -Vy), 1200, 1, true));
    }
}

/** Objective: Changes the rotation of the TurretPiece to the angle necessary.
    @param float angle - angle of the shoot.
    @return void.
*/
void TurretPiece::Rotate(float angle) {
    rotation = angle;
}

/** Objective: Returns the value of the rotation of the TurretPiece.
    @param none.
    @return float rotation.
*/
float TurretPiece::Rotation() {
    return rotation;
}

/** Objective: Returns the type of the TurretPiece.
    @param none.
    @return int type - type of the TurretPiece.
*/
int TurretPiece::Type() {
    return type;
}

/** Objective: Changes the state of the TurretPiece (alive or not).
    @param none.
    @return void.
*/
void TurretPiece::Kill() {
    isDead = true;
}

/** Objective: Manages the reactions of the box in a collision with another object.
    @param GameObject* other - the object that is in collision.
    @return void.
*/
void TurretPiece::NotifyObjectCollision(GameObject* other) {
    if (type == 0) {
        if (other->IsPlayer()) {
            Player* c = (Player*) other;
            if (c->Attacking()) {
                center->Damage(c->Power());
            }
        }
        if (other->Is("Projectile")) {
            Projectile* p = (Projectile*) other;
            if (p->GetOwner() == "Gallahad") {
                center->Damage(p->Power());
            }
        }
    }
}

/**
    Objective: Function responsible to update TurretPiece GameObject, but overloaded with the object 'world'.
    @param TileMap* world.
    @param float dt.
    @return void.
*/
void TurretPiece::Update(TileMap* world, float dt) {
    Vec2 size = graphicsComponent->GetSize();
    box.SetXY(Vec2(center->box.GetCenter().x + refX - (size.x / 2), center->box.GetCenter().y + refY - (size.y / 2)));
    graphicsComponent->Update(this, dt);
}

/** Objective: Draws the TurretPiece on the map.
    @param none.
    @return void.
*/
void TurretPiece::Render() {
    graphicsComponent->Render(GetPosition() - Camera::GetInstance().pos, rotation);
}
