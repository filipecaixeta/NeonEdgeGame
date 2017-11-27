// Copyright (c) 2017 Neon Edge Game.

#include "Projectile.h"
#include "Camera.h"
#include "StageState.h"
#include "Animation.h"

#include <cmath>
#include <math.h>
#include <assert.h>

Projectile::Projectile(GameObject* gameObject, Vec2 speed, int lifetime, int power, bool pierce) {

    name = "Projectile";
    assert(gameObject != NULL);
    ownerN = gameObject->name;
    facing = gameObject->facing;
    if (facing == LEFT) {
        assert(speed.x >= FLOAT_SIZE_MIN && speed.x <= FLOAT_SIZE_MAX);
        speed.x *= -1;
    } else {
        // It does nothing.
    }

    physicsComponent = PhysicsComponent(true);
    physicsComponent.velocity = speed;
    graphicsComponent = new ProjectileGraphicsComponent(ownerN);

    assert(lifetime >= INTEGER_SIZE_MIN && lifetime <= INTEGER_SIZE_MAX);
    Projectile::lifetime = Timer(lifetime);
    Projectile::lifetime.Start();
    Projectile::power = power;
    Projectile::pierce = pierce;
    Vec2 size = graphicsComponent->GetSize();

    if (facing == LEFT) {
        assert(gameObject != NULL);
        box.x = gameObject->box.x - size.x;
    } else {
        assert(gameObject != NULL);
        box.x = gameObject->box.x + gameObject->box.w;
    }

    box.y = gameObject->box.y + (gameObject->box.h / 2 - size.y / 2);
    box.w = size.x;
    box.h = size.y;
    assert(gameObject != NULL);
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
                                 bool &characterLeftDirection) {
    *surface_ = graphicsComponent->GetSurface();
    assert (*surface_ != NULL);
    clipRect_ = graphicsComponent->GetClip();
    pos_ = box.GetXY();
    characterLeftDirection = graphicsComponent->GetCharacterLeftDirection();
    return true;
}

void Projectile::NotifyTileCollision(int tile, Face face) {
    if (tile >= SOLID_TILE) {
        assert(tile >= INTEGER_SIZE_MIN && tile <= INTEGER_SIZE_MAX);
        lifetime.Stop();
    } else {
        // It does nothing.
    }
}

void Projectile::NotifyObjectCollision(GameObject *gameObject) {
    if (!gameObject->Is(ownerN)) {
        assert(gameObject != NULL);
        if (gameObject->Is("Projectile")) {
            assert(gameObject != NULL);
            Projectile *projectile = (Projectile *) gameObject;
            if (projectile->GetOwner() != ownerN) {
                assert(projectile != NULL);
                if (!pierce) {
                    lifetime.Stop();
                }
            }
        } else if (!gameObject->Is("BoxSpawner")) {
            assert(gameObject != NULL);
            if (!pierce) {
                lifetime.Stop();
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }
        assert(gameObject != NULL);
    } else {
        // It does nothing.
    }
}

void Projectile::UpdateTimers(float deltaTime) {
    assert(deltaTime >= FLOAT_SIZE_MIN && deltaTime <= FLOAT_SIZE_MAX);
    lifetime.Update(deltaTime);
}

void Projectile::Update(TileMap* world, float deltaTime) {
    assert(deltaTime >= FLOAT_SIZE_MIN && deltaTime <= FLOAT_SIZE_MAX);
    UpdateTimers(deltaTime);
    assert(world != NULL);
    physicsComponent.Update(this, world, deltaTime);
    graphicsComponent->Update(this, deltaTime);
    assert(world != NULL);
}

void Projectile::Render() {
    float angle = atan(physicsComponent.velocity.y / physicsComponent.velocity.x) * 180 / M_PI;
    graphicsComponent->Render(Vec2(box.x - Camera::CheckInstance().screenPosition.x,
                                   box.y - Camera::CheckInstance().screenPosition.y),
                                   angle);
}
