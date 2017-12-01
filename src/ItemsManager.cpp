/**
 * Copyright 2017 Neon Edge Game
 * File Name: ItemsManager.cpp
 * Header File Name: ItemsManager.h
 * Class Name: ItemsManager
 * Objective: it manages items of character.
 */

#include "ItemsManager.h"
#include <assert.h>
#include "InputManager.h"
#include "StageState.h"
#include "Cutscene.h"

/**
 * Objective: it constructs the Items Manager object.
 *
 * @param none.
 * @return instace of Items Manager.
 */
ItemsManager::ItemsManager() {
}

/**
 * Objective: it gets actived items.
 *
 * @param none.
 * @return vector<ItemsManager::itemType> itemsVector.
 */
std::vector<ItemsManager::itemType> ItemsManager::GetActiveItems() {
    std::vector<ItemsManager::itemType> itemsVector;
    for (auto item: items) {
        if (item.second.active == true) {
            itemsVector.emplace_back(item.second);
        } else {
            // It does nothing.
        }
    }

    return itemsVector;
}

/**
 * Objective: it manages items.
 *
 * @param none.
 * @return vector<ItemsManager::itemType> itemsVector.
 */
std::vector<ItemsManager::itemType> ItemsManager::GetItems() {
    std::vector<ItemsManager::itemType> itemsVector;
    for (auto item: items) {
        itemsVector.emplace_back(item.second);
    }

    return itemsVector;
}

/**
 * Objective: it gets items.
 *
 * @param std::string name - name of item to be getted.
 * @return ItemsManager::itemType item.
 */
ItemsManager::itemType ItemsManager::GetItem(std::string name) {
    assert(name[0] != '\0');

    ItemsManager::itemType item = items[name];

    return item;
}

/**
 * Objective: it adds item to repository.
 *
 * @param int id - id of item.
 * @return none.
 */
void ItemsManager::AddItem(int id) {
    std::string name = "";
    std::string desc = "";
    switch (id) {
        case 1:
            name = "Energy Potion 25";
            desc = "";
            break;
        case 2:
            name = "Energy Potion 50";
            desc = "";
            break;
        case 3:
            name = "Skill Coin";
            desc = "";
            break;
        case 4:
            name = "Healing Potion 25";
            desc = "Provides health regeneration by 25%";
            break;
        case 5:
            name = "Healing Potion 50";
            desc = "Provides health regeneration by 50%";
            break;
        case 6:
            name = "Driver";
            desc = "";
            break;
        default:
            break;
    }

    if (name != "") {
        if (!items.count(name)) {
            std::string imageName = "items.png";
            int frameCount = 6;

            items.emplace(name, itemType{ new Sprite(imageName, frameCount), true, 1, name, desc });
            items[name].sprite->SetFrame(id);
        } else {
            items[name].count++;
        }

        bool exists = false;
        for (int i = 0; i < HOT_BAR_SIZE; i++) {
            if (hotItems[i] == name) {
                exists = true;
                break;
            } else {
                // It does nothing.
            }
        }
        if (exists == false) {
            for (int i = 0; i < HOT_BAR_SIZE; i++) {
                if (hotItems[i] == "") {
                    hotItems[i] = name;
                    break;
                } else {
                    // It does nothing.
                }
            }
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it adds item Drive in repository and define your behavior.
 *
 * @param int id - id of Drive item (6).
 * @return none.
 */
void ItemsManager::AddDriver(int id) {
    std::string name = "";
    std::string desc = "";
    if (id == 6) {
        name = "Driver";
        desc = "";
    }

    if (name == "Driver") {
        if (StageState::stage == "naveGalahad") {
            Game::GetInstance().GetCurrentState()->quitRequested = true;
            Game::GetInstance().AddState(new Cutscene(3, false));
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it checks if item is actived.
 *
 * @param std::string name - name of item to be checked.
 * @return bool itemIsActiveStatus.
 */
bool ItemsManager::IsActive(std::string name) {
    assert(name[0] != '\0');

    bool itemIsActiveStatus = items[name].active;

    assert(itemIsActiveStatus == true || itemIsActiveStatus == false);

    return itemIsActiveStatus;
}

/**
 * Objective: it checks if item is hot.
 *
 * @param std::string name - name of item to be checked.
 * @return
 */
bool ItemsManager::IsHot(std::string name) {
    assert(name[0] != '\0');

    bool itemIsHotStatus = false;

    for (auto &item: hotItems) {
        if (item == name) {
            itemIsHotStatus = true;
        } else {
            // It does nothing.
        }
    }

    assert(itemIsHotStatus == true || itemIsHotStatus == false);

    return itemIsHotStatus;
}

/**
 * Objective: it sets item to actived.
 *
 * @param std::string name - name of item to be setted.
 * @param bool active - item active status.
 * @return none.
 */
void ItemsManager::SetActive(std::string name, bool active) {
    assert(name[0] != '\0');
    assert(active == true || active == false);

    items[name].active = active;
}

/**
 * Objective: it sets item status to consumed.
 *
 * @param int hotItemsPos - item to be consumed.
 * @return none.
 */
void ItemsManager::ConsumeItem(int hotItemsPos) {
    if (items.count(hotItems[hotItemsPos]) > 0) {
        items[hotItems[hotItemsPos]].count--;
        if (items[hotItems[hotItemsPos]].count <= 0) {
            delete items[hotItems[hotItemsPos]].sprite;
            items.erase(hotItems[hotItemsPos]);
            hotItems[hotItemsPos] = "";
        } else {
            // It does nothing.
        }
    } else {
        // It does nothing.
    }
}

/**
 * Objective: it renders position of items in screen.
 *
 * @param none.
 * @return none.
 */
void ItemsManager::Render() {
    // 50, 641
    int positionX[3] = { 50, 50 + 92, (50 + (92 * 2)) };
    for (int i = 0; i < HOT_BAR_SIZE; i++) {
        if (items.count(hotItems[i])) {
            items[hotItems[i]].sprite->Render(Vec2(positionX[i], 641));
        } else {
            // It does nothing.
        }
    }
}

/**
 * Objective: it does nothing.
 *
 * @param none.
 * @return none.
 */
void ItemsManager::Update() {
}
