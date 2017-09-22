/**
  Copyright 2017 Neon Edge Game
  File Name: TurretPiece.cpp
  Header File Name: TurretPiece.h
  Class Name: TurretPiece
  Objective: Defines the behavior and actions of a piece of the TurretPiece.

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
    @param int type - Type of TurretPiece from 0 to 4: 0 - Head | 1 - Body1 | 2 - Body2. | 3 - Front Gun | 4 - Back Gun.
    @return instance of TurretPiece.

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

/**
    Objective: Destructor of the class TurretPiece.
    @param none.
    @return none.

*/
TurretPiece::~TurretPiece() {
}

/**
    Objective: Defines the velocity of projectile of the TurretPiece.
    @param none.
    @return none.

*/
void TurretPiece::Shoot() {
    if (type > 2) {
        float Vx = cos(rotation * M_PI / 180) * 0.6; // The value 0.6 is to let the velocity of the projectile by 60%.
        float Vy = sin(rotation * M_PI / 180) * 0.6;
        StageState::AddObject(new Projectile(this, Vec2(Vx, -Vy), 1200, 1, true));
    }
}

/** Objective: Changes the rotation of the TurretPiece to the angle necessary.
    @param float angle - angle of the shoot.
    @return none.

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

/** Objective: Returns the type of the TurretPiece.  A type of the TurretPiece is its position on Turret, and varies of 0 to 4.
    @param none.
    @return int type - type of the TurretPiece.

*/
int TurretPiece::Type() {
    return type;
}

/** Objective: Changes the state of the TurretPiece (alive or not).
    @param none.
    @return none.

*/
void TurretPiece::Kill() {
    isDead = true;
}

/** Objective: Manages the reactions of the box in a collision with another object.
    @param GameObject* other - the object that is in collision.
    @return none.

*/
void TurretPiece::NotifyObjectCollision(GameObject* other) {
    // Defines the damage received by the type 0 TurretPiece (head of the tower) when there is a collision with the player in state of attack.
    if (type == 0) {
        if (other->IsPlayer()) {
            Player* c = (Player*) other;
            if (c->Attacking()) {
                center->Damage(c->Power());
            }
        }
        // Defines the damage received by the type 0 TurretPiece (head of the tower) when there is a collision with the Projectile.
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
    @param float dt - The amount of time the TurretPiece updates its graphics.
    @return none.

*/
void TurretPiece::Update(TileMap* world, float dt) {
    Vec2 size = graphicsComponent->GetSize();
    box.SetXY(Vec2(center->box.GetCenter().x + refX - (size.x / 2), center->box.GetCenter().y + refY - (size.y / 2)));
    graphicsComponent->Update(this, dt);
}

/** Objective: Draws the TurretPiece on the map.
    @param none.
    @return none.

*/
void TurretPiece::Render() {
    graphicsComponent->Render(GetPosition() - Camera::GetInstance().pos, rotation);
}
