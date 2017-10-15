// Copyright (c) 2017 Neon Edge Game.

#include "Projectile.h"
#include "Camera.h"
#include "StageState.h"
#include "Animation.h"

#include <cmath>
#include <math.h>

Projectile::Projectile(GameObject* gameObject, Vec2 speed, int lifetime, int power, bool pierce) {
    name = "Projectile";
    ownerN = gameObject->name;
    facing = gameObject->facing;
    if (facing == LEFT) {
        speed.x *= -1;
    } else {
        // It does nothing.
    }
    physicsComponent = PhysicsComponent(true);
    physicsComponent.velocity = speed;
    graphicsComponent = new ProjectileGraphicsComponent(ownerN);
    Projectile::lifetime = Timer(lifetime);
    Projectile::lifetime.Start();
    Projectile::power = power;
    Projectile::pierce = pierce;
    Vec2 size = graphicsComponent->GetSize();
    if (facing == LEFT) {
        box.x = gameObject->box.x - size.x;
    } else {
        box.x = gameObject->box.x + gameObject->box.w;
    }
    box.y = gameObject->box.y + (gameObject->box.h / 2 - size.y / 2);
    box.w = size.x;
    box.h = size.y;
}

Projectile::~Projectile() {
}

bool Projectile::IsDead() {
    if (!lifetime.IsRunning()) {
        StageState::AddObject(new Animation(box.GetCenter().x, box.GetCenter().y,
                                            ownerN + "ProjectileEnd.png", 8, 80, true));
    } else {
        // It does nothing.
    }
    return (!lifetime.IsRunning());
}

int Projectile::Power() {
    return power;
}

std::string Projectile::GetOwner() {
    return ownerN;
}

bool Projectile::GetColisionData(SDL_Surface** surface_, SDL_Rect &clipRect_, Vec2 &pos_,
                                 bool &mirror) {
    *surface_ = graphicsComponent->GetSurface();
    clipRect_ = graphicsComponent->GetClip();
    pos_ = box.GetXY();
    mirror = graphicsComponent->GetCharacterLeftDirection();
    return true;
}

void Projectile::NotifyTileCollision(int tile, Face face) {
    if (tile >= SOLID_TILE) {
        lifetime.Stop();
    } else {
        // It does nothing.
    }
}

void Projectile::NotifyObjectCollision(GameObject *gameObject) {
    if (!gameObject->Is(ownerN)) {
        if (gameObject->Is("Projectile")) {
            Projectile *projectile = (Projectile *) gameObject;
            if (projectile->GetOwner() != ownerN) {
                if (!pierce) {
                    lifetime.Stop();
                }
            }
        } else if (!gameObject->Is("BoxSpawner")) {
            if (!pierce) {
                lifetime.Stop();
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

void Projectile::UpdateTimers(float deltaTime) {
    lifetime.Update(deltaTime);
}

void Projectile::Update(TileMap* world, float deltaTime) {
    UpdateTimers(deltaTime);
    physicsComponent.Update(this, world, deltaTime);
    graphicsComponent->Update(this, deltaTime);
}

void Projectile::Render() {
    float angle = atan(physicsComponent.velocity.y/physicsComponent.velocity.x) * 180/M_PI;
    graphicsComponent->Render(Vec2(box.x - Camera::CheckInstance().screenPosition.x,
                                   box.y - Camera::CheckInstance().screenPosition.y),
                                   angle);
}
