/**
 * Copyright 2017 Neon Edge Game.
 * File Name: GameObject.cpp
 * Header File Name: GameObject.h
 * Class Name: GameObject
 * Objective: it manages game object.
 */

#include "GameObject.h"
#include "Character.h"
#include "Game.h"
#include "Logger.h"
#include <assert.h>

GameObject::~GameObject() {
    Log::instance.info("Destroy GameObject");    
}

/**
 * Objective: it compares given string with name.
 *
 * @param string stringName.
 * @return bool 'stringName == name' - status of given string.
 */
bool GameObject::Is(std::string stringName) {
    Log::instance.info("Compare GameObject name with stringName");  
    assert(stringName != "");
    return (stringName == name);
}

/**
 * Objective: it verifies if game object is dead.
 *
 * @param none.
 * @return bool isDead - game object life status.
 */
bool GameObject::IsDead() {
    Log::instance.info("GameObject is Dead");
    assert(isDead || !isDead);
    return isDead;
}

/**
 * Objective: it says that game object is not a character.
 *
 * @param none.
 * @return bool false.
 */
bool GameObject::IsCharacter() {
    Log::instance.info("GameObject is Character");
    bool objectEqualCharacter = false;
    assert(objectEqualCharacter || !objectEqualCharacter);
    return objectEqualCharacter;
}

/**
 * Objective: it says that game object is not a player.
 *
 * @param none.
 * @return bool false.
 */
bool GameObject::IsPlayer() {
    Log::instance.info("GameObject is Player");
    bool objectEqualPlayer = false;
    assert(objectEqualPlayer || !objectEqualPlayer);
    return objectEqualPlayer;
}

/**
 * Objective: it gets position of game object.
 *
 * @param none.
 * @return Vec2(box.x, box.y) - position of game object.
 */
Vec2 GameObject::GetPosition() {
    Log::instance.info("Get object position");
    assert ((box.x >= FLOAT_MIN_SIZE && box.x <= FLOAT_MAX_SIZE) &&
    (box.y >= FLOAT_MIN_SIZE && box.y <= FLOAT_MAX_SIZE));
    return Vec2(box.x, box.y);
}

/**
 * Objective: it sets position of game object.
 *
 * @param Vec2 position.
 * @return none.
 */
void GameObject::SetPosition(Vec2 position) {
    Log::instance.info("GameObject is Player");
    if ((position.x >= FLOAT_MIN_SIZE && position.x <= FLOAT_MAX_SIZE) &&
            (position.y >= FLOAT_MIN_SIZE && position.y <= FLOAT_MAX_SIZE)) {
        box.x = position.x;
        box.y = position.y;
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it does nothing.
 *
 * @param int tile.
 * @param Face face.
 * @return none.
 */
void GameObject::NotifyTileCollision(int tile, Face face) {
}

/**
 * Objective: it does nothing.
 *
 * @param GameObject *gameObject.
 * @return none.
 */
void GameObject::NotifyObjectCollision(GameObject *gameObject) {
}

/**
 * Objective: it manages solid colitions.
 *
 * @param GameObject *gameObject.
 * @return none.
 */
void GameObject::SolidColision(GameObject *gameObject) {
    if (gameObject && IsCharacter()) {
        Log::instance.info("Collision with character");
        Character *character = (Character *) this;
        int y = box.y - character->physicsComponent.velocity.y * Game::GetInstance().GetDeltaTime();
        if (footing != GROUNDED && y + box.h < gameObject->box.y) {
            box.y = gameObject->box.y - box.h - 1;
            character->physicsComponent.velocity.y = 0.6;
            if (lastFooting != GROUNDED) {
                lastFooting = footing;
            } else {
                // It does nothing.
            }

            footing = GROUNDED;
        } else {
            if (character->physicsComponent.velocity.x < 0) {
                assert((box.x >= INT_MIN_SIZE && box.x <= INT_MAX_SIZE) && 
                       (box.w >= INT_MIN_SIZE && box.w <= INT_MAX_SIZE));
                if (box.x < gameObject->box.x + gameObject->box.w && box.x + box.w > 
                    gameObject->box.x + gameObject->box.w) {
                    box.x = gameObject->box.x + gameObject->box.w + 1;
                } else {
                    // It does nothing.
                }
            } else if (character->physicsComponent.velocity.x > 0) {
                assert((box.x >= INT_MIN_SIZE && box.x <= INT_MAX_SIZE) && 
                       (box.y >= INT_MIN_SIZE && box.y <= INT_MAX_SIZE));
                if (box.x + box.w > gameObject->box.x && box.x < gameObject->box.x) {
                    box.x = gameObject->box.x - box.w-1;
                } else {
                    // It does nothing.
                }
            } else {
                // It does nothing.
            }
        }

        if (y > gameObject->box.y + gameObject->box.h) {
            assert((box.y >= INT_MIN_SIZE && box.y <= INT_MAX_SIZE) && 
            (box.h >= INT_MIN_SIZE && box.h <= INT_MAX_SIZE));
            box.y = gameObject->box.y + gameObject->box.h + 1;
            character->physicsComponent.velocity.y = 0;
        } else {
            // It does nothing.
        }

        character->graphicsComponent->Update(this, 0);
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it gets colision data.
 *
 * @param SDL_Surface **surface
 * @param SDL_Rect &clipRect
 * @param Vec2 &position
 * @param bool &mirror
 * @return bool false.
 */
bool GameObject::GetColisionData(SDL_Surface **surface, SDL_Rect &clipRect, Vec2 &position,
                                 bool &mirror) {
    Log::instance.info("Collision Data");
    bool colisionData = false;
    return colisionData;
}

/**
 * Objective: it starts death time of game object.
 *
 * @param none.
 * @return none.
 */
void GameObject::DieAnimation() {
    Log::instance.info("Die Animation start");
    dieTimer.Start();
}

/**
 * Objective: it does nothing.
 *
 * @param none.
 * @return none.
 */
void GameObject::Render() {
}
