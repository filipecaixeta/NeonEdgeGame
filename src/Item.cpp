/**
    Copyright (c) 2017 Neon Edge Game.
    File Name: Item.cpp
    Header File Name: Item.h
    Class Name: Item
    Objective:

*/

#include "Item.h"
#include "Camera.h"
#include "StageState.h"

/**
    Objective: it does nothing.
    @param none.
    @return none.

*/
Item::Item(int id_, int x, int y): sp(new Sprite("items.png", 6)), dead(false), id(id_-100) {
    sp->SetFrame(id);
    box.SetXY(Vec2(x, y));
    box.SetWH(sp->GetSize());
    name = "Item";
}

/**
    Objective:
    @param Player player - .
    @return none.

*/
void Item::Eval(Player *player) {
    if (player != nullptr && player->itemManager != nullptr) {
        player->itemManager->AddItem(id);
        player->soundComponent->Item();
    }
}

/**
    Objective: it does nothing.
    @param bool b - .
    @return none.

*/
void Item::SetActive(bool b) {
}

/**
    Objective: it verifies .
    @param none.
    @return none.

*/
bool Item::GetActive() {
    return !IsDead();
}

/**
    Objective: it does nothing.
    @param none.
    @return none.

*/
bool Item::Is(std::string type) {
    return (type == "Item");
}

/**
    Objective: it does nothing.
    @param none.
    @return none.

*/
bool Item::IsDead() {
    return dead;
}

/**
    Objective: it does nothing.
    @param none.
    @return none.

*/
void Item::NotifyObjectCollision(GameObject *other) {
    if (other->IsPlayer()) {
        dead = true;
    }
}

/**
    Objective: it does nothing.
    @param TileMap map - current map.
    @param float dt - amount of time.
    @return none.

*/
void Item::Update(TileMap *map, float dt) {
}

/**
    Objective: it does nothing.
    @param none.
    @return none.

*/
void Item::Render() {
    sp->Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
