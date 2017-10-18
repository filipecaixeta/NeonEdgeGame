/**
 * Copyright (c) 2017 Neon Edge Game
 * File Name: TurretPiece.cpp
 * Header File Name: TurretPiece.h
 * Class Name: TurretPiece
 * Objective: Defines the behavior and actions of a piece of the TurretPiece.
 */

#include <cmath>
#include <math.h>

#include "TurretPiece.h"
#include "StageState.h"
#include "Camera.h"
#include "Player.h"
#include "Projectile.h"
#include <assert.h>

/**
 * Objective: Constructor of the class TurretPiece, instance the object and defines
 *            the initial attibutes.
 *
 * @param Character *center.
 * @param int x - Initial position of the TurretPiece in X
 * @param int y - Initial position of the TurretPiece in Y.
 * @param int type - Type of TurretPiece from 0 to 4: 0 - Head | 1 - Body1 | 2 - Body2.
 *                        | 3 - Front Gun | 4 - Back Gun.
 * @return instance of TurretPiece.
*/
TurretPiece::TurretPiece(Character* center, int x, int y, int type):
    Character(0, 0) {
        if (type >= INT_MIN_SIZE && type <= INT_MAX_SIZE ) {
            if ((x >= INT_MIN_SIZE && x <= INT_MAX_SIZE) && (y >= INT_MIN_SIZE && y <= INT_MAX_SIZE)) {
                name = "TurretBoss";
                this->center = center;
                this->type = type;
                facing = center->facing;
                refX = x;
                refY = y;
                physicsComponent.SetKinetic(true);
                // Instances the graphics, adding the sprites.
                graphicsComponent = new TurretPieceGraphicsComponent("TurretBoss", type);
                Vec2 size = graphicsComponent->GetSize();
                box.SetXY(Vec2(center->box.GetCenter().x + refX - (size.x / 2), center->box.GetCenter().y + refY - (size.y / 2)));
                box.SetWH(size);
                rotation = 0;
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }
}

/**
 * Objective: Destructor of the class TurretPiece.
 *
 * @param none.
 * @return none.
 */
TurretPiece::~TurretPiece() {
}

/**
 * Objective: Defines the velocity of projectile of the TurretPiece.
 *
 * @param none.
 * @return none.
 */
void TurretPiece::Shoot() {
    if (type > 2) {
        // The value 0.6 is to let the velocity of the projectile by 60%.
        float Vx = cos(rotation * M_PI / 180) * 0.6;
        float Vy = sin(rotation * M_PI / 180) * 0.6;
        StageState::AddObject(new Projectile(this, Vec2(Vx, -Vy), 1200, 1, true));
    } else {
        // It does nothing.
    }
}

/**
 * Objective: Changes the rotation of the TurretPiece to the angle necessary.
 *
 * @param float angle - angle of the shoot.
 * @return none.
*/
void TurretPiece::Rotate(float angle) {
    if (angle >= FLOAT_MIN_SIZE && angle <= FLOAT_MAX_SIZE) {
        rotation = angle;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: Returns the value of the rotation of the TurretPiece.
 *
 * @param none.
 * @return float rotation.
*/
float TurretPiece::Rotation() {
    return rotation;
}

/**
 * Objective: Returns the type of the TurretPiece.  A type of the TurretPiece
 *                is its position on Turret, and varies of 0 to 4.
 *
 * @param none.
 * @return int type - type of the TurretPiece.
*/
int TurretPiece::Type() {
    return type;
}

/**
 * Objective: Changes the state of the TurretPiece (alive or not).
 *
 * @param none.
 * @return none.
*/
void TurretPiece::Kill() {
    isDead = true;
}

void TurretPiece::TowerDamageOnPlayer(GameObject* other) {
    if (other->IsPlayer()) {
        assert(other->IsPlayer() == true);
        Player* c = (Player*) other;
        if (c->Attacking()) {
            assert(c->Attacking() == true);
            center->Damage(c->Power());
        } else {
            // It does nothing
        }
    } else {
        // It does nothing
    }
}

void TurretPiece::HeadTowerDamage(GameObject* other) {
    assert(other->Is("Projectile") == true);
    Projectile* p = (Projectile*) other;
    if (p->GetOwner() == "Gallahad") {
        assert(p->GetOwner() == "Gallahad");
        center->Damage(p->Power());
    } else {
        // It does nothing
    }
}

/**
 * Objective: Manages the reactions of the box in a collision with another object.
 *
 * @param GameObject* other - the object that is in collision.
 * @return none.
 */
void TurretPiece::NotifyObjectCollision(GameObject* other) {
    /* Defines the damage received by the type 0 TurretPiece (head of the tower) when there
     is a collision with the player in state of attack.*/
    if (type == 0) {
        TowerDamageOnPlayer(other);
        
        /* Defines the damage received by the type 0 TurretPiece (head of the tower) when there
        is a collision with the Projectile.*/
        if (other->Is("Projectile")) {
            HeadTowerDamage(other);
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: Function responsible to update TurretPiece GameObject, but overloaded with
 *              the object 'world'.
 *
 * @param TileMap* world.
 * @param float dt - The amount of time the TurretPiece updates its graphics.
 * @return none.
 */
void TurretPiece::Update(TileMap* world, float dt) {
    Vec2 size = graphicsComponent->GetSize();
    box.SetXY(Vec2(center->box.GetCenter().x + refX - (size.x / 2), center->box.GetCenter().y + refY - (size.y / 2)));
    graphicsComponent->Update(this, dt);
}

/**
 * Objective: Draws the TurretPiece on the map.
 *
 * @param none.
 * @return none.
*/
void TurretPiece::Render() {
    graphicsComponent->Render(GetPosition() - Camera::CheckInstance().screenPosition, rotation);
}
