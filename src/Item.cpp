#include "Item.h"
#include "Camera.h"
#include "StageState.h"

Item::Item(int id_, int x, int y):
    sp(new Sprite("items.png",6)),
    dead(false),
    id(id_-100) {
    sp->SetFrame(id);
    box.SetXY(Vec2(x,y));
    box.SetWH(sp->GetSize());
    name = "Item";
}

void Item::Eval(Player* player) {
    if (player!=nullptr && player->itemManager!=nullptr) {
        player->itemManager->AddItem(id);
        player->soundComponent->Item();
    }
}

void Item::SetActive(bool b) {

}

bool Item::GetActive() {
    return !IsDead();
}

bool Item::Is(std::string type) {
    return type=="Item";
}

bool Item::IsDead() {
    return dead;
}

void Item::NotifyObjectCollision(GameObject* other) {
    if (other->IsPlayer())
        dead = true;
}

void Item::Update(TileMap* map, float dt) {

}

void Item::Render() {
    sp->Render(box.x - Camera::GetInstance().pos.x, box.y - Camera::GetInstance().pos.y);
}
