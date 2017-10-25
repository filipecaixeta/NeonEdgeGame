#include <vector>
#include <iostream>
#include <fstream>

#include "menu/InGameQuests.h"
#include "Text.h"
#include "InputManager.h"
#include "IOFunctions.h"
#include "QuestManager.h"

InGameQuests::InGameQuests(): questTitle(new Sprite()), questText(new Sprite()) {
}

void InGameQuests::LoadAssets() {
    QuestManager qm;
    qm.ReadQuestsFile();
    questType & questsV = qm.GetQuests();
		fontSize = FONT_SIZE;
    for (auto &q: questsV) {
        quests[q.first] = q.second;
				SDL_Texture* text = Text::GetText(fontName, fontSize, fontColor, q.first, LETTER_SPACING);
				menuOptions.push_back({q.first, new Sprite(text, 1, 0, true), true, 0});
    }

    std::string path = "menus/" + StageState::player->name;
    bg.Open(path + "MenuQuest.png");
    bg.SetBlending(true);

    blackOpacity.Open("menus/smallBlack.png", true);
    blackOpacity.SetScaleX(SCALE);
    blackOpacity.SetScaleY(SCALE);
    blackOpacity.SetTransparency(FIFTY_PER_CENT);

    SetOption(1);
}

void InGameQuests::Update() {
    MenuState::Update();
}

void InGameQuests::SetQuestText(std::string questName) {
    SDL_Texture *text = NULL;
    text = Text::GetText(fontName, fontSize, fontColor, questName, LETTER_SPACING);
    questTitle->SetTexture(text, true);
    std::string & textStr = quests[questName];
    text = Text::GetText(fontName, fontSize * EIGHTY_PER_CENT, fontColor, textStr, LETTER_SPACING);
    questText->SetTexture(text, true);
}

void InGameQuests::Render() {
    blackOpacity.Render(0, 0);
    Vec2 bgXY = CenterHorizontal(&bg) + CenterVertical(&bg);
    bg.Render(bgXY);
    Vec2 pos(17, 50);
		int offset = OFFSET_VALUE;
    for(auto option: menuOptions) {
				option.sprite->Render(bgXY + pos);
				pos.y += offset;
    }

    questTitle->Render(bgXY + Vec2(255, 50));
    questText->Render(bgXY + Vec2(255, 100));
}

void InGameQuests::SetOption(int i) {
    MenuState::SetOption(i);
    if (menuOptions.size() > 0) {
        SetQuestText(menuOptions[currentOption].key);
		}
}
