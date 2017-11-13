#include "ItensManager.h"
#include "InputManager.h"
#include "StageState.h"
#include "Cutscene.h"

ItensManager::ItensManager() {
}

std::vector<ItensManager::itemType> ItensManager::GetActiveItems() {
    std::vector<ItensManager::itemType> v;
    for (auto i: itens) {
        if (i.second.active == true) {
            v.emplace_back(i.second);
        }
    }
    return v;
}

std::vector<ItensManager::itemType> ItensManager::GetItems() {
    std::vector<ItensManager::itemType> v;
    for (auto i: itens) {
        v.emplace_back(i.second);
    }
    return v;
}

ItensManager::itemType ItensManager::GetItem(std::string name) {
    return itens[name];
}

void ItensManager::AddItem(int id) {
    std::string imageName = "items.png";
    int frameCount = 6;
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
    } if (name != "") {
        if (!itens.count(name)) {
            itens.emplace(name, itemType{
                              new Sprite(imageName, frameCount),
                              true,
                              1,
                              name,
                              desc});
            itens[name].sp->SetFrame(id);
        } else {
            itens[name].count++;
        }

        bool exists = false;
        for (int i = 0; i < HOT_BAR_SIZE; i++) {
            if (hotItens[i] == name) {
                exists = true;
                break;
            }
        }
        if (exists == false) {
            for (int i = 0; i < HOT_BAR_SIZE; i++) {
                if (hotItens[i] == "") {
                    hotItens[i] = name;
                    break;
                }
            }
        }
    }
    if (name == "Driver") {
        if (StageState::stage == "naveGalahad") {
            Game::GetInstance().GetCurrentState()->quitRequested = true;
            Game::GetInstance().AddState(new Cutscene(3, false));
        }
    }
}

bool ItensManager::IsActive(std::string name) {
    return itens[name].active;
}

bool ItensManager::IsHot(std::string name) {
    for (auto &i: hotItens) {
        if (i == name) {
            return true;
        }
    }
    return false;
}

void ItensManager::SetActive(std::string name, bool active) {
    itens[name].active = active;
}

void ItensManager::ConsumeItem(int hotItensPos) {
    if (itens.count(hotItens[hotItensPos])>0) {
        itens[hotItens[hotItensPos]].count--;
        if (itens[hotItens[hotItensPos]].count<=0) {
            delete itens[hotItens[hotItensPos]].sp;
            itens.erase(hotItens[hotItensPos]);
            hotItens[hotItensPos]="";
        }
    }
}

void ItensManager::Render() {
    //50, 641
    int positionX[3] = {50, 50+92, 50+92*2};
    for (int i = 0; i < HOT_BAR_SIZE; i++) {
        if (itens.count(hotItens[i])) {
            itens[hotItens[i]].sp->RenderScreenPosition(Vec2(positionX[i], 641));
        }
    }
}

void ItensManager::Update() {
}
