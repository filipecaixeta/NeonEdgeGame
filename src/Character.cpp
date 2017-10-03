/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: Character.cpp
 * Header File Name: Character.h
 * Class Name: Character
 * Objective:
 */

#include "Character.h"
#include "Camera.h"
#include "StageState.h"
#include "Vec2.h"
#include "Rect.h"
#include "Interactive.h"
#include "Projectile.h"

/**
 * Objective: it constructs Character object in some given axes.
 *
 * @param int x - position on the x axis.
 * @param int y - position on the y axis.
 * @return Character object.
 */
Character::Character(int x, int y): GameObject(), physicsComponent(), graphicsComponent(nullptr),
                                    soundComponent(nullptr), saveComponent(), characterHealthPoints(10),
                                    characterPowerPoints(1), invincibilityTimer(500), attacking(200),
                                    coolDownAttack(500), stunned(0) {
    box.SetXY(Vec2(x, y));
    facing = RIGHT;
    startingX = x;
    startingY = y;
}

Character::~Character() {
}

/**
 * Objective: it verifies if the character is dead.
 *
 * @param none.
 * @return bool isDead - character's life status.
 */
bool Character::IsDead() {
    if (characterHealthPoints <= 0) {
        if (!dieTimer.IsRunning()) {
            dieTimer.Start();
            if (soundComponent) {
                soundComponent->Die();
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }

        if (!dieTimer.IsRunning() && dieTimer.GetElapsed() == 1) {
            isDead = true;
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }

    return isDead;
}

/**
 * Objective: it says that the object is character.
 *
 * @param none.
 * @return true - object is a character.
 */
bool Character::IsCharacter() {
    return true;
}

/**
 * Objective: it returns the health of character.
 *
 * @param none.
 * @return healthPoints - character's life.
 */
int Character::GetHealth() {
    return characterHealthPoints;
}

/**
 * Objective: it decreases the character's life according to the damage received.
 *
 * @param int damageReceived - value of damage.
 * @return none.
 */
void Character::Damage(int damageReceived) {
    if (!invincibilityTimer.IsRunning()) {
        characterHealthPoints -= (damageReceived);
        invincibilityTimer.Start();
    } else {
        // It does nothing.
    }
}
/**
 * Objective: it manages the attack action of the character.
 *
 * @param none.
 * @return none.
 */
void Character::Attack() {
}

/**
 * Objective: it verifies if the character is attacking.
 *
 * @param none.
 * @return attacking.running - attacking running time status.
 */
bool Character::Attacking() {
    return attacking.IsRunning();
}

/**
 * Objective: it verifies if cool down attack time is running.
 *
 * @param none.
 * @return coolDownAttack.running - cool down attack time status.
 */
bool Character::Cooling() {
    return coolDownAttack.IsRunning();
}

/**
 * Objective: it sets character power.
 *
 * @param int powerAmount - character power amount to be setted.
 * @return none.
 */
void Character::Empower(int powerAmount) {
    this->characterPowerPoints = powerAmount;
}

/**
 * Objective: it verifies character power amount.
 *
 * @param none.
 * @return int characterPowerPoints - character power amount.
 */
int Character::CharacterPower() {
    return characterPowerPoints;
}

/**
 * Objective: it gets colision data.
 *
 * @param SDL_Surface **surface_
 * @param SDL_Rect &clipRect_
 * @param Vec2 &pos_
 * @param bool &mirror
 * @return bool true.
 */
bool Character::GetColisionData(SDL_Surface **surface, SDL_Rect &clipRect, Vec2 &position,
                                bool &mirror) {
    *surface = graphicsComponent->GetSurface();
    clipRect = graphicsComponent->GetClip();
    position = box.GetXY();
    mirror = graphicsComponent->GetMirror();
    return true;
}

/**
 * Objective: it verifies character colition with tile to take out health point.
 *
 * @param int tile
 * @param Face face
 * @return none.
 */
void Character::NotifyTileCollision(int tile, Face face) {
    if (tile > 30) {
        Damage(1);
    } else {
        // It does nothing.
    }

    /*
    if (tile >= SOLID_TILE && (face == LEFT || face == RIGHT)) {
        if (physicsComponent.velocity.y >= 0.6) {
            physicsComponent.velocity.y = -0.5;
        } else {
            // It does nothing.
        }
    }
    */
}

/**
 * Objective: it verifies game object to do respective actions.
 *
 * @param GameObject *gameObject - game object to be identified.
 * @return none.
 */
void Character::NotifyObjectCollision(GameObject* gameObject) {
    Interactive *interactive = (Interactive *) gameObject;
    if (((!IsPlayer() || !gameObject->IsPlayer()) && !gameObject->Is("Projectile") &&
         !gameObject->Is("PressurePlate") && !gameObject->Is("PressurePlateOneTime") &&
         !gameObject->Is("HandScanner") && !gameObject->Is("BoxSpawner")) &&
            (gameObject->Is("Door") && (!IsPlayer() || !interactive->Active()))) {
        SolidCollision(gameObject);
    } else {
        // It does nothing.
    }

    Player *player = (Player*) gameObject;
    if (!IsPlayer() && gameObject->IsPlayer() && player->Attacking()) {
        Damage(player->CharacterPower());
        if (gameObject->Is("Drone") && !stunned.IsRunning()) {
            Player *player = (Player *) StageState::GetPlayer();
            if (player->skills[6]) {
                stunned.SetLimit(2000);
                stunned.Start();
            } else if (player->skills[5]) {
                stunned.SetLimit(1000);
                stunned.Start();
            } else {
                // It does nothing.
            }
        } else {
            // It does nothing.
        }

        if (gameObject->Is("Projectile")) {
            Projectile *projectile = (Projectile *) gameObject;
            if (projectile->GetOwner() == "Gallahad") {
                Damage(projectile->CharacterPower());
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

/**
 * Objective: it updates character death time and character attack time.
 *
 * @param float deltaTime - amount of time.
 * @return none.
 */
void Character::UpdateTimers(float deltaTime) {
    dieTimer.Update(deltaTime);
    if (dieTimer.GetElapsed() == 1) {
        isDead = true;
    } else {
        // It does nothing.
    }

    invincibilityTimer.Update(deltaTime);
    attacking.Update(deltaTime);
    if (attacking.GetElapsed() == 1) {
        attacking.Reset();
        coolDownAttack.Start();
    } else {
        // It does nothing.
    }

    coolDownAttack.Update(deltaTime);
    stunned.Update(deltaTime);
}

/**
 * Objective: it verifies if map exceeds screen size limits.
 *
 * @param TileMap *map - game map.
 * @return bool - status of map in the screen.
 */
bool Character::OutOfBounds(TileMap *map) {
    return (box.x < 0 || box.x > (map->GetWidth() - 1)*map->GetTileWidth() ||
            box.y < 0 || box.y > (map->GetHeight() - 1)*map->GetTileHeight());
}

/**
 * Objective: it updates times related with character, physics and screen limits of map.
 *
 * @param TileMap *map - game map.
 * @param float deltaTime - amount of time.
 * @return none.
 */
void Character::Update(TileMap *map, float deltaTime) {
    UpdateTimers(deltaTime);
    physicsComponent.Update(this, map, deltaTime);
    if (OutOfBounds(map)) {
        SetPosition(Vec2(startingX, startingY));
    } else {
        // It does nothing.
    }

    graphicsComponent->Update(this, deltaTime);
}

/**
 * Objective: it renders character position in the map.
 *
 * @param none.
 * @return none.
 */
void Character::Render() {
    graphicsComponent->Render(GetPosition() - Camera::GetInstance().pos);
}
