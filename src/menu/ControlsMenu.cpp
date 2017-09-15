/**
    Copyright 2017 Neon Edge Game
    File Name: ControlsMenu.cpp
    Header File Name: ControlsMenu.h
    Class Name: ControlsMenu
    Objective: manages the menu controls.

*/

#include "menu/ControlsMenu.h"
#include "Text.h"
#include "InputManager.h"
// #include <fstream>

ControlsMenu::ControlsMenu(): MenuState(), replaceKey(false) {
}

/**
    Objective: loads the menu.
    @param none.
    @return none.

*/
void ControlsMenu::LoadAssets() {
    Sprite *marker = new Sprite("menus/marker.png");  // Create menu option icon.
    menuOptions.push_back({"moveLeft", marker, true, 0});
    menuOptions.push_back({"moveLeftOption", marker, true, 0});
    menuOptions.push_back({"moveRight", marker, true, 0});
    menuOptions.push_back({"moveRightOption", marker, true, 0});

    bg.Open("menus/BG_Back.png");  // Loads the menu background image.

    bgOptions.Open("menus/Menu-Neutro-Base.png");  // Loads the menu options image.

    SetOption(1);

    /*
    SDL_Texture *text;

    text = Text::GetText(fontName, fontSize, fontColor, "Move Left");
    menuOptions.push_back({"moveLeft", new Sprite(text, 1, 0, true), false, 0});

    text = Text::GetText(fontName, fontSize, fontColor, CreateKeyString(MOVE_LEFT_KEY));
    menuOptions.push_back({"moveLeftOption", new Sprite(text, 1, 0, true), true, 0});

    text = Text::GetText(fontName, fontSize, fontColor, "Move Right");
    menuOptions.push_back({"moveRight", new Sprite(text, 1, 0, true), false, 0});

    text = Text::GetText(fontName, fontSize, fontColor, CreateKeyString(MOVE_RIGHT_KEY));
    menuOptions.push_back({"moveRightOption", new Sprite(text, 1, 0, true), true, 0});

    text = Text::GetText(fontName, fontSize, fontColor, "Crouch");
    menuOptions.push_back({"CrouchDown", new Sprite(text, 1, 0, true), false, 0});

    text = Text::GetText(fontName, fontSize, fontColor, CreateKeyString(CROUCH_KEY));
    menuOptions.push_back({"CrouchOption", new Sprite(text, 1, 0, true), true, 0});

    text = Text::GetText(fontName, fontSize, fontColor, "Jump");
    menuOptions.push_back({"jump", new Sprite(text, 1, 0, true), false, 0});

    text = Text::GetText(fontName, fontSize, fontColor, CreateKeyString(JUMP_KEY));
    menuOptions.push_back({"jumpOption", new Sprite(text, 1, 0, true), true, 0});

    text = Text::GetText(fontName, fontSize, fontColor, "Attack");
    menuOptions.push_back({"attack", new Sprite(text, 1, 0, true), false, 0});

    text = Text::GetText(fontName, fontSize, fontColor, CreateKeyString(ATTACK_KEY));
    menuOptions.push_back({"attackOption", new Sprite(text, 1, 0, true), true, 0});

    bg.Open("mainMenuBg.png");

    SetOption(1);
    */
}

/**
    Objective: turns key into buff.
    @param c - numerical representation of a key.
    @return buff - key string.

*/
std::string ControlsMenu::CreateKeyString(int c) {
    char buff[10];
    int v = InputManager::GetInstance().GetTranslationKey(c);  // Catches pressed key.
    // Verifies key and sets it.
    if (v == SDLK_LEFT) {
        snprintf(buff, sizeof(buff), "[ < ]");
    } else if (v == SDLK_RIGHT) {
        snprintf(buff, sizeof(buff), "[ > ]");
    } else if (v == SDLK_UP) {
        snprintf(buff, sizeof(buff), "[ ^ ]");
    } else if (v == SDLK_DOWN) {
        snprintf(buff, sizeof(buff), "[ v ]");
    } else if (v == SDLK_SPACE) {
        snprintf(buff, sizeof(buff), "[ space ]");
    } else {
        snprintf(buff, sizeof(buff), "[ %c ]", v);
    }
    return buff;
}

/**
    Objective: updates the chosen menu option.
    @param none.
    @return none.

*/
void ControlsMenu::Update() {
    // Selects the menu option
    if (InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
            InputManager::GetInstance().KeyPress(SDLK_RETURN)) {
        replaceKey = true;
        InputManager::GetInstance().GetLastKey();
    // Goes to selected menu option.
    } else if (replaceKey == true) {
        int lk = InputManager::GetInstance().GetLastKey();
        // Checks key validity
        if (lk != -1) {
            // std::fstream fs;
            // replaceKey = false;
            if (menuOptions[currentOption].key == "moveLeftOption") {
                InputManager::GetInstance().SetTranslationKey(MOVE_LEFT_KEY, lk);
                SDL_Texture *text = Text::GetText(fontName, fontSize, fontColor,
                                                  CreateKeyString(MOVE_LEFT_KEY));
                menuOptions[currentOption].sprite->SetTexture(text, true);
                // fs.open("moveLeftOption.txt", std::fstream::out | std::fstream::trunc);
                // fs.write((char*)lk, sizeof(lk));
            } else if (menuOptions[currentOption].key == "moveRightOption") {
                InputManager::GetInstance().SetTranslationKey(MOVE_RIGHT_KEY, lk);
                SDL_Texture *text = Text::GetText(fontName, fontSize, fontColor,
                                                  CreateKeyString(MOVE_RIGHT_KEY));
                menuOptions[currentOption].sprite->SetTexture(text, true);
                // fs.open("moveRightOption.txt", std::fstream::out | std::fstream::trunc);
                // fs.write((char*)lk, sizeof(lk));
            } else if (menuOptions[currentOption].key == "moveDownOption") {
                InputManager::GetInstance().SetTranslationKey(CROUCH_KEY, lk);
                SDL_Texture *text = Text::GetText(fontName, fontSize, fontColor,
                                                  CreateKeyString(CROUCH_KEY));
                menuOptions[currentOption].sprite->SetTexture(text, true);
                // fs.open("moveDownOption.txt", std::fstream::out | std::fstream::trunc);
                // fs.write((char*)lk, sizeof(lk));
            } else if (menuOptions[currentOption].key == "jumpOption") {
                InputManager::GetInstance().SetTranslationKey(JUMP_KEY, lk);
                SDL_Texture *text = Text::GetText(fontName, fontSize, fontColor,
                                                  CreateKeyString(JUMP_KEY));
                menuOptions[currentOption].sprite->SetTexture(text, true);
                // fs.open("jumpOption.txt", std::fstream::out | std::fstream::trunc);
                // fs.write((char*)lk, sizeof(lk));
            } else if (menuOptions[currentOption].key == "attackOption") {
                InputManager::GetInstance().SetTranslationKey(ATTACK_KEY, lk);
                SDL_Texture *text = Text::GetText(fontName, fontSize, fontColor,
                                                  CreateKeyString(ATTACK_KEY));
                menuOptions[currentOption].sprite->SetTexture(text, true);
                // fs.open("attackOption.txt", std::fstream::out | std::fstream::trunc);
                // fs.write((char*)lk, sizeof(lk));
            }
            // fs.close();
        }
    } else {
        MenuState::Update();
    }
}

/**
    Objective: renders menu position.
    @param none.
    @return none.

*/
void ControlsMenu::Render() {
    int positionsY[4] = {431, 498, 564, 631};
    bg.Render(CenterVertical(&bg));
    bgOptions.Render(CenterVertical(&bgOptions) + Vec2(0, 99));
    menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite) +
                                              Vec2(0, positionsY[currentOption]));
    MenuState::Render();
}
