// Copyright (c) 2017 Neon Edge Game.

#ifndef INCLUDE_ITEMSMANAGER_H_
#define INCLUDE_ITEMSMANAGER_H_

#include <vector>
#include <unordered_map>

#include "Sprite.h"

#define HOT_BAR_SIZE 3

class ItemsManager {
  public:
    struct itemType {
        Sprite *sprite;
        bool active;
        unsigned int count;
        std::string name;
        std::string description;
    };

    ItemsManager();
    std::vector<itemType> GetActiveItems();
  	itemType GetItem(std::string name);
    void AddItem(int id);
    void ConsumeItem(int hotItemsPos);
    void Render();
    void Update();
    std::string hotItems[HOT_BAR_SIZE];
    std::unordered_map<std::string,itemType> items;

  private:
    std::vector<itemType> GetItems();
    bool IsActive(std::string name);
    bool IsHot(std::string name);
    void SetActive(std::string name, bool active);

};

#endif  // INCLUDE_ITEMSMANAGER_H_
