/*
  Copyright 2017 Neon Edge Game
  File Name: InGamePause.cpp
  Header File Name: InGamePause.h
  Class Name: InGamePause
  Objective: manages games pause options.
*/

#include "menu/InGamePause.h"
#include "menu/SettingsMenu.h"
#include "menu/MainMenu.h"
#include "menu/InGameItens.h"
#include "menu/InGameSkills.h"
#include "menu/InGameQuests.h"
#include "InputManager.h"
#include "StageState.h"

InGamePause::InGamePause(StageState *stageState_): MenuState(), stageState(stageState_) {
}

/*
  Function Objective: loads menu options.
  param: none.
  return: none.
*/
void InGamePause::LoadAssets() {
    SDL_Texture *text;

    menuOptions.push_back({"Skills", new Sprite("menus/skills-button.png"), true, 0});
    menuOptions.push_back({"Inventory", new Sprite("menus/inventory-button.png"), true, 0});
    menuOptions.push_back({"Quests", new Sprite("menus/quests-button.png"), true, 0});
    menuOptions.push_back({"Settings", new Sprite("menus/settings-button.png"), true, 0});
    menuOptions.push_back({"MainMenu", new Sprite("menus/main-menu-button.png"), true, 0});

    bgOptions.Open("menus/Pause-Menu-Neutro-Base.png");

    SetOption(1);
}

/*
  Function Objective: updates to selected menu option.
  param: none.
  return: none.
*/
void InGamePause::Update() {
    MenuState::Update();
    // Verifies selected menu option.
    if (InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
            InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
        if (SelectedOptionIs("Skills")) {
            stageState->inGameMenu = new InGameSkills();
            stageState->inGameMenu->LoadAssets();
        } else if (SelectedOptionIs("Inventory")) {
            stageState->inGameMenu = new InGameItens(stageState->player->itemManager);
            stageState->inGameMenu->LoadAssets();
        } else if (SelectedOptionIs("Quests")) {
            stageState->inGameMenu = new InGameQuests();
            stageState->inGameMenu->LoadAssets();
        } else if (SelectedOptionIs("Settings")) {
            Game::GetInstance().AddState(new SettingsMenu());
        } else if (SelectedOptionIs("MainMenu")) {
            Game::GetInstance().AddState(new MainMenu());
        }
    }
}

/*
  Function Objective: render menu options position.
  param: none.
  return: none.
*/
void InGamePause::Render() {
    int positionsY[5] = {381, 447, 514, 581, 648};
    bgOptions.Render(CenterVertical(&bgOptions) + Vec2(0, 122));
    menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite) +
                                              Vec2(0, positionsY[currentOption]));
}
