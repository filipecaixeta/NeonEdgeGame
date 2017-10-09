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

GameObject::~GameObject() {
}

/**
 * Objective: it compares given string with name.
 *
 * @param string stringName.
 * @return bool 'stringName == name' - status of given string.
 */
bool GameObject::Is(std::string stringName) {
    return (stringName == name);
}

/**
 * Objective: it verifies if game object is dead.
 *
 * @param none.
 * @return bool isDead - game object life status.
 */
bool GameObject::IsDead() {
    return isDead;
}

/**
 * Objective: it says that game object is not a character.
 *
 * @param none.
 * @return bool false.
 */
bool GameObject::IsCharacter() {
    return false;
}

/**
 * Objective: it says that game object is not a player.
 *
 * @param none.
 * @return bool false.
 */
bool GameObject::IsPlayer() {
    return false;
}

/**
 * Objective: it gets position of game object.
 *
 * @param none.
 * @return Vec2(box.x, box.y) - position of game object.
 */
Vec2 GameObject::GetPosition() {
    return Vec2(box.x, box.y);
}

/**
 * Objective: it sets position of game object.
 *
 * @param Vec2 position.
 * @return none.
 */
void GameObject::SetPosition(Vec2 position) {
    if ((position.x >= INT_MIN_SIZE && position.x <= INT_MAX_SIZE) &&
            (position.y >= INT_MIN_SIZE && position.y <= INT_MAX_SIZE)) {
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
                if (box.x < gameObject->box.x + gameObject->box.w && box.x + box.w > gameObject->box.x + gameObject->box.w) {
                    box.x = gameObject->box.x + gameObject->box.w + 1;
                } else {
                    // It does nothing.
                }
            } else if (character->physicsComponent.velocity.x > 0) {
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
    return false;
}

/**
 * Objective: it starts death time of game object.
 *
 * @param none.
 * @return none.
 */
void GameObject::DieAnimation() {
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
