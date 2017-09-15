/**
    Copyright 2017 Neon Edge Game
    File Name: InGameSkills.cpp
    Header File Name: InGameSkills.h
    Class Name: InGameSkills
    Objective: manages skills character.

*/

#include "menu/InGameSkills.h"
#include "StageState.h"
#include "InputManager.h"

InGameSkills::InGameSkills() {
}

InGameSkills::~InGameSkills() {
    delete menuOptions[0].sprite;
    menuOptions.clear();
}

/**
    Objective: loads skills options.
    @param none.
    @return none.

*/
void InGameSkills::LoadAssets() {
    std::string path = "menus/" + StageState::player->name;

    selected = new Sprite(path + "SkillTreeSelected.png");

    auto &skills = StageState::player->skills;

    menuOptions.push_back({"Skill0", new Sprite(path + "Skill0.png"), true, skills[0]});
    menuOptions.push_back({"Skill1", new Sprite(path + "Skill1.png"), true, skills[1]});
    menuOptions.push_back({"Skill2", new Sprite(path + "Skill2.png"), true, skills[2]});
    menuOptions.push_back({"Skill3", new Sprite(), true, skills[3]});
    menuOptions.push_back({"Skill4", new Sprite(path + "Skill4.png"), true, skills[4]});
    menuOptions.push_back({"Skill5", new Sprite(path + "Skill5.png"), true, skills[5]});
    menuOptions.push_back({"Skill6", new Sprite(path + "Skill6.png"), true, skills[6]});

    bg.Open(path + "SkillTree.png");
    bg.SetBlending(true);

    blackOpacity.Open("menus/smallBlack.png", true);
    blackOpacity.SetScaleX(2000);
    blackOpacity.SetScaleY(2000);
    blackOpacity.SetTransparency(0.5);

    SetOption(4);
}

/**
    Objective: Updates selected menu skill option.
    @param none.
    @return none.

*/
void InGameSkills::Update() {
    MenuState::Update();
    // Verifies selected skill option.
    if (InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
            InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
        if (menuOptions[currentOption].current == true) {
            return;
        }
        if (currentOption < 3) {
            if (menuOptions[currentOption + 1].current == true) {
                GetSkill(currentOption);
            }
        } else if (currentOption > 3) {
            if (menuOptions[currentOption - 1].current == true) {
                GetSkill(currentOption);
            }
        }
    }
}

/**
    Objective: gets skills.
    @param int skillNumber - skill number.
    @return none.

*/
void InGameSkills::GetSkill(int skillNumber) {
    if (StageState::player->skillPoints <= 0) {
        return;
    }
    StageState::player->skillPoints -= 1;
    StageState::player->skills[skillNumber] = true;
    menuOptions[currentOption].current = true;
}

/**
    Objective: render skills positions.
    @param none.
    @return none.

*/
void InGameSkills::Render() {
    blackOpacity.Render(0, 0);
    Vec2 bgXY = CenterHorizontal(&bg)+CenterVertical(&bg);
    bg.Render(bgXY);

    Vec2 positions[7] = {Vec2(38, 156), Vec2(219, 157), Vec2(396, 150), Vec2(397, 301),
                         Vec2(396, 452), Vec2(219, 458), Vec2(38, 457)};

    for (int i = 0; i < menuOptions.size(); i++) {
        auto &option = menuOptions[i];
        if (option.current == true) {
            option.sprite->Render(bgXY + positions[i] + Vec2(13, 18));
        }
    }
    selected->Render(bgXY + positions[currentOption]);
}
