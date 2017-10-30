// Copyright 2013 Thomas Park.

#include "Character.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Interactive.h"
#include "Projectile.h"
#include "Logger.h"
#include <assert.h>

Character::Character(int x, int y) {

	graphicsComponent = nullptr;
	soundComponent = nullptr;
	hitpoints = 10;
	power = 1;
	invincibilityTimer = 500;
	attacking = 200;
	attackCD = 500;
	stunned = 0;
    box.SetXY(Vec2(x, y));
    facing = RIGHT;
    startingX = x;
    startingY = y;
    Log::instance.info("Character builder started!");      
}

Character::~Character() {
}

bool Character::IsDead() {
    if (hitpoints <= 0) {
        if (!dieTimer.IsRunning()) {
            dieTimer.Start();
            if (soundComponent) {
                soundComponent->SoundDie();
                Log::instance.info("Death sound of the initiated character!");  
            } else {
                Log::instance.error("Death sound of the character did not play, check the IsDead method of Character and SoundDie's SoundComponent method");      
                // It does nothing
            }
        } else {
            // It does nothing
        }
        if (!dieTimer.IsRunning() && dieTimer.GetElapsed() == 1) {
            isDead = true;
            Log::instance.info("Dead character!");              
        } else {
            // It does nothing
        }
    } else {
        // It does nothing
    }
    assert(isDead == true || isDead == false);
    return isDead;
}

bool Character::IsCharacter() {
    bool character = true;
    assert(character == true);    
    return character;
}

int Character::GetHealth() {
    assert(hitpoints >= 0 && hitpoints<=10);    
    return hitpoints;
}

void Character::Damage(int damage) {
    if (!invincibilityTimer.IsRunning()) {
        hitpoints -= (damage);
        invincibilityTimer.Start();
    } else {
        Log::instance.warning("No damage, check Damage in Character!");  
        // It does nothing
    }
}

void Character::Attack() {
}

bool Character::Attacking() {
    assert(attacking.IsRunning() == true || attacking.IsRunning() == false);    
    return attacking.IsRunning();
}

bool Character::Cooling() {
    assert(attackCD.IsRunning() == true || attackCD.IsRunning() == false);        
    return attackCD.IsRunning();
}

void Character::Empower(int pow) {
    power = pow;
}

int Character::Power() {
    assert(power >= 0);
    return power;
}

bool Character::GetColisionData(SDL_Surface** surface_, SDL_Rect &clipRect_, Vec2 &pos_,
                                bool &mirror) {
    *surface_ = graphicsComponent->GetSurface();
    clipRect_ = graphicsComponent->GetClip();
    pos_ = box.GetXY();
    mirror = graphicsComponent->GetCharacterLeftDirection();
    bool colision = true;    
    assert(colision == true);
    return colision;
}

void Character::NotifyTileCollision(int tile, Face face) {
    if (tile > 30) {
        Damage(1);
    } else {
        // It does nothing
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
                SolidColision(other);
            } else {
                // It does nothing
            }
        } else {
            SolidColision(other);
        }
    } else {
        // It does nothing
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
                    } else {
                        // It does nothing
                    }
                } else {
                    // It does nothing
                }
            } else {
                // It does nothing   
            }
        } else {
            // It does nothing            
        }
        if (other->Is("Projectile")) {
            Projectile *p = (Projectile *) other;
            if (p->GetOwner() == "Gallahad") { 
                Damage(p->Power());
            } else {
                // It does nothing
            }
        } else {
            // It does nothing
        }
    } else {
        // It does nothing        
    }
}

void Character::UpdateTimers(float dt) {
    dieTimer.Update(dt);
    if (dieTimer.GetElapsed() == 1) {
        isDead = true;
        Log::instance.warning("Character is dead, UpdateTimers in Character!");        
    } else {
        // It does nothing
    }
    invincibilityTimer.Update(dt);
    attacking.Update(dt);
    if (attacking.GetElapsed() == 1) {
        attacking.Reset();
        attackCD.Start();
    } else {
        // It does nothing
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
        Log::instance.warning("Outdated limits!");
    } else {
        // It does nothing
    }
    graphicsComponent->Update(this, dt);
}

void Character::Render() {
    graphicsComponent->Render(GetPosition() - Camera::CheckInstance().screenPosition);
}
