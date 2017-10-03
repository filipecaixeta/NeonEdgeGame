// Copyright 2013 Thomas Park.

#include "Character.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Interactive.h"
#include "Projectile.h"

Character::Character(int x, int y): GameObject(), physicsComponent(), graphicsComponent(nullptr),
                                    soundComponent(nullptr), saveComponent(), hitpoints(10),
                                    power(1), invincibilityTimer(500), attacking(200),
                                    attackCD(500), stunned(0) {
    box.SetXY(Vec2(x, y));
    facing = RIGHT;
    startingX = x;
    startingY = y;
}

Character::~Character() {
}

bool Character::IsDead() {
    if (hitpoints <= 0) {
        if (!dieTimer.IsRunning()) {
            dieTimer.Start();
            if (soundComponent) {
                soundComponent->Die();
            }
        }
        if (!dieTimer.IsRunning() && dieTimer.GetElapsed() == 1) {
            isDead = true;
        }
    }
    return isDead;
}

bool Character::IsCharacter() {
    return true;
}

int Character::GetHealth() {
    return hitpoints;
}

void Character::Damage(int damage) {
    if (!invincibilityTimer.IsRunning()) {
        hitpoints -= (damage);
        invincibilityTimer.Start();
    }
}

void Character::Attack() {
}

bool Character::Attacking() {
    return attacking.IsRunning();
}

bool Character::Cooling() {
    return attackCD.IsRunning();
}

void Character::Empower(int pow) {
    power = pow;
}

int Character::Power() {
    return power;
}

bool Character::GetColisionData(SDL_Surface** surface_, SDL_Rect &clipRect_, Vec2 &pos_,
                                bool &mirror) {
    *surface_ = graphicsComponent->GetSurface();
    clipRect_ = graphicsComponent->GetClip();
    pos_ = box.GetXY();
    mirror = graphicsComponent->GetMirror();
    return true;
}

void Character::NotifyTileCollision(int tile, Face face) {
    if (tile > 30) {
        Damage(1);
    }
    /*
    if (tile >= SOLID_TILE && (face == LEFT || face == RIGHT)) {
        if (physicsComponent.velocity.y >= 0.6) {
            physicsComponent.velocity.y = -0.5;
        }
    }
    */
}

void Character::NotifyObjectCollision(GameObject* other) {
    if ((!IsPlayer() || !other->IsPlayer()) && !other->Is("Projectile") &&
            !other->Is("PressurePlate") && !other->Is("PressurePlateOneTime") &&
            !other->Is("HandScanner") && !other->Is("BoxSpawner")) {
        if (other->Is("Door")) {
            Interactive *i = (Interactive *) other;
            if (!IsPlayer() || !i->Active()) {
                SolidCollision(other);
            }
        } else {
            SolidCollision(other);
        }
    }
    if (!IsPlayer()) {
        if (other->IsPlayer()) {
            Player *p = (Player*) other;
            if (p->Attacking()) {
                Damage(p->Power());
                if (other->Is("Drone")) {
                    if (!stunned.IsRunning()) {
                        Player *play = (Player *) StageState::GetPlayer();
                        if (play->skills[6]) {
                            stunned.SetLimit(2000);
                            stunned.Start();
                        } else if (play->skills[5]) {
                            stunned.SetLimit(1000);
                            stunned.Start();
                        }
                    }
                }
            }
        }
        if (other->Is("Projectile")) {
            Projectile *p = (Projectile *) other;
            if (p->GetOwner() == "Gallahad") {
                Damage(p->Power());
            }
        }
    }
}

void Character::UpdateTimers(float dt) {
    dieTimer.Update(dt);
    if (dieTimer.GetElapsed() == 1) {
        isDead = true;
    }
    invincibilityTimer.Update(dt);
    attacking.Update(dt);
    if (attacking.GetElapsed() == 1) {
        attacking.Reset();
        attackCD.Start();
    }
    attackCD.Update(dt);
    stunned.Update(dt);
}

bool Character::OutOfBounds(TileMap *map) {
    return (box.x < 0 || box.x > (map->GetWidth() - 1)*map->GetTileWidth() ||
            box.y < 0 || box.y > (map->GetHeight() - 1)*map->GetTileHeight());
}

void Character::Update(TileMap *map, float dt) {
    UpdateTimers(dt);
    physicsComponent.Update(this, map, dt);
    if (OutOfBounds(map)) {
        SetPosition(Vec2(startingX, startingY));
    }
    graphicsComponent->Update(this, dt);
}

void Character::Render() {
    graphicsComponent->Render(GetPosition() - Camera::GetInstance().pos);
}
