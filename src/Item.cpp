/**
 * Copyright (c) 2017 Neon Edge Game.
 * File Name: Item.cpp
 * Header File Name: Item.h
 * Class Name: Item
 * Objective: it manages character itens in the game.
 */

#include "Item.h"
#include "Camera.h"
#include "StageState.h"
#include <assert.h>

/**
 * Objective: it constructs Item object.
 *
 * @param int id - id of item.
 * @param int x - Initial position of the Item in x axis
 * @param int y - Initial position of the Item in y axis.
 * @return instance of Item.
 */
Item::Item(int idParam, int x, int y): sprite(new Sprite("items.png", 6)), dead(false),
                                       id(idParam - 100) {
    assert(id >= INT_MIN_SIZE && id <= INT_MAX_SIZE);
    sprite->SetFrame(id);
    assert(x >= INT_MIN_SIZE && x <= INT_MAX_SIZE);
    assert(y >= INT_MIN_SIZE && y <= INT_MAX_SIZE);
    box.SetXY(Vec2(x, y));
    box.SetWH(sprite->GetSize());
    stringName = "Item";
}

/**
 * Objective: it manages itens of character.
 *
 * @param Player *player - player character object.
 * @return none.
 */
void Item::Eval(Player *player) {
    assert(player != nullptr);

    if (player->itemManager != nullptr) {
        player->itemManager->AddItem(id);
        player->soundComponent->SoundItem();
    } else {
        // It does nothing.
    }

    assert(player != nullptr);
}

/**
 * Objective: it does nothing.
 *
 * @param bool boolStatus.
 * @return none.
 */
void Item::SetActive(bool boolStatus) {
}

/**
 * Objective: it returns opposite object life status.
 *
 * @param none.
 * @return '!IsDead()'.
 */
bool Item::GetActive() {
    return !IsDead();
}

/**
 * Objective: it verifies item.
 *
 * @param none.
 * @return bool 'stringItem == "Item"'.
 */
bool Item::Is(std::string stringItem) {
    assert(stringItem[0] != '\0');

    return (stringItem == "Item");
}

/**
 * Objective: it returns object life status.
 *
 * @param none.
 * @return bool dead.
 */
bool Item::IsDead() {
    return dead;
}

/**
 * Objective: it sets character life status to dead when happens a collision.
 *
 * @param GameObject *gameObject.
 * @return none.
 */
void Item::NotifyObjectCollision(GameObject *gameObject) {
    assert(gameObject != nullptr);

    if (gameObject->IsPlayer()) {
        dead = true;
    } else {
        // It does nothing.
    }

    assert(gameObject != nullptr);
}

/**
 * Objective: it does nothing.
 *
 * @param TileMap *map.
 * @param float deltaTime.
 * @return none.
 */
void Item::Update(TileMap *map, float deltaTime) {
}

/**
 * Objective: it renders sprite item.
 *
 * @param none.
 * @return none.
 */
void Item::Render() {
    sprite->Render(box.x - Camera::CheckInstance().screenPosition.x,
                   box.y - Camera::CheckInstance().screenPosition.y);
}
