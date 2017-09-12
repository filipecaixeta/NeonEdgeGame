/*
  Copyright 2017 Neon Edge Game
  File Name: GraphicsMenu.cpp
  Header File Name: GraphicsMenu.h
  Class Name: GraphicsMenu
  Objective: manages the menu graphics.
*/

#include "menu/GraphicsMenu.h"
#include "Text.h"
#include "InputManager.h"
// #include <fstream>

GraphicsMenu::GraphicsMenu(): MenuState() {
}

/*
  Function Objective: sets graphic game.
  param: none.
  return: none.
*/
void GraphicsMenu::LoadAssets() {
    menuOptions.push_back({"Resolution", new Sprite("menus/resolution-button.png"), true, 0});
    menuOptions2.push_back({"Resolution", new Sprite(), true, 0});
    SDL_Point ss = Game::GetInstance().GetScreenSize();  // Screen size.
    // Verifies screen size to sets.
    if (ss.x == 1024) {
        menuOptions2[0].current = 0;
        UpdateScreenSizeSprite(0, menuOptions2[0].sprite);
    } else if (ss.x == 1360) {
        menuOptions2[0].current = 1;
        UpdateScreenSizeSprite(1, menuOptions[0].sprite);
    } else if (ss.x == 1792) {
        menuOptions2[0].current = 2;
        UpdateScreenSizeSprite(2, menuOptions2[0].sprite);
    }

    menuOptions.push_back({"FPS", new Sprite("menus/framerate-button.png"), true, 0});
    menuOptions2.push_back({"FPS", new Sprite(), true, 0});
    int fps = Game::GetInstance().fps;
    // Verifies fps game to sets.
    if (fps == 30) {
        menuOptions2[1].current = 0;
        UpdateFPSSprite(0, menuOptions2[1].sprite);
    } else if (fps == 60) {
        menuOptions2[1].current = 1;
        UpdateFPSSprite(1, menuOptions2[1].sprite);
    } else if (fps == 480) {
        menuOptions2[1].current = 2;
        UpdateFPSSprite(2, menuOptions2[1].sprite);
    }

    menuOptions.push_back({"WindowMode", new Sprite("menus/window-mode-button.png"), true, 0});
    menuOptions2.push_back({"WindowMode", new Sprite(), true, 0});
    bool fs = Game::GetInstance().isFullScreen();  // Fullscreen.
    // Verifies windows mode to sets.
    if (fs) {
        menuOptions2[2].current = 1;
        UpdateWindowModeSprite(1, menuOptions2[2].sprite);
    } else {
        menuOptions2[2].current = 0;
        UpdateWindowModeSprite(0, menuOptions2[2].sprite);
    }

    bg.Open("menus/BackgroundInicial2.png");  // Loads the second menu background image.
    bgOptions.Open("menus/Screen-Menu-Neutro-Base.png");  // Loads the menu screen options image.
    selectedArrow.Open("menus/selected-arrows.png");  // Loads arrows to selected menu option.
    SetOption(1);
}

/*
  Function Objective: sets game screen configurations.
  param: none.
  return: none.
*/
void GraphicsMenu::Update() {
    MenuState::Update();
    // Verifies pressed key.
    int rl = 0;
    if (InputManager::GetInstance().KeyPress(SDLK_RIGHT)) {
        rl = 1;
    } else if (InputManager::GetInstance().KeyPress(SDLK_LEFT)) {
        rl = -1;
    }

    if (rl != 0) {
        // Verifies selected screen size.
        if (menuOptions[currentOption].key == "Resolution") {
            menuOptions2[currentOption].current = (menuOptions2[currentOption].current + rl) % 3;
            if (menuOptions2[currentOption].current < 0) {
                menuOptions2[currentOption].current = 2;
            }

            if (menuOptions2[currentOption].current == 0) {
                Game::GetInstance().SetScreenSize(Game::GetInstance().res4x3);
            } else if (menuOptions2[currentOption].current == 1) {
                Game::GetInstance().SetScreenSize(Game::GetInstance().res16x9);
            } else if (menuOptions2[currentOption].current == 2) {
                Game::GetInstance().SetScreenSize(Game::GetInstance().res21x9);
            }

            UpdateScreenSizeSprite(menuOptions2[currentOption].current,
                                   menuOptions2[currentOption].sprite);
        }

        // Verifies selected windows mode.
        if (menuOptions[currentOption].key == "WindowMode") {
            menuOptions2[currentOption].current = (menuOptions2[currentOption].current + rl) % 2;
            if (menuOptions2[currentOption].current < 0) {
                menuOptions2[currentOption].current = 1;
            }

            if (menuOptions2[currentOption].current == 0) {
                Game::GetInstance().setFullScreen(false);
            } else if (menuOptions2[currentOption].current == 1) {
                Game::GetInstance().setFullScreen(true);
            }

            UpdateWindowModeSprite(menuOptions2[currentOption].current,
                                   menuOptions2[currentOption].sprite);
        }

        // Verifies selected fps.
        if (menuOptions[currentOption].key == "FPS") {
            menuOptions2[currentOption].current = (menuOptions2[currentOption].current + rl) % 3;
            if (menuOptions2[currentOption].current < 0) {
                menuOptions2[currentOption].current = 2;
            }

            if (menuOptions2[currentOption].current == 0) {
                Game::GetInstance().fps = 30;
            } else if (menuOptions2[currentOption].current == 1) {
                Game::GetInstance().fps = 60;
            } else if (menuOptions2[currentOption].current == 2) {
                Game::GetInstance().fps = 480;
            }

            UpdateFPSSprite(menuOptions2[currentOption].current,
                            menuOptions2[currentOption].sprite);
        }
    }
}

/*
  Function Objective: sets game screen size.
  param: int options - selected game screen size option.
  param: Sprite sprite.
  return: none.
*/
void GraphicsMenu::UpdateScreenSizeSprite(int option, Sprite *sprite) {
    // Sets screen size.
    if (option == 0) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "1024x768  4:3");
        sprite->SetTexture(text, true);
    } else if (option == 1) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "1360x768 16:9");
        sprite->SetTexture(text, true);
    } else if (option == 2) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "1792x768 21:9");
        sprite->SetTexture(text, true);
    }
}

/*
  Function Objective: updates windows mode of game.
  param: int option - selected game window mode option.
  param: Sprint sprint.
  return: none.
*/
void GraphicsMenu::UpdateWindowModeSprite(int option, Sprite *sprite) {
    // Sets windows mode.
    if (option == 0) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "Windowed");
        sprite->SetTexture(text, true);
    } else if (option == 1) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "Full Screen");
        sprite->SetTexture(text, true);
    }
}

/*
  Function Objective: updates fps of game.
  param: int option - selected game fps option.
  param: Sprint sprint.
  return: none.
*/
void GraphicsMenu::UpdateFPSSprite(int option, Sprite *sprite) {
    // Sets fps.
    if (option == 0) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "30fps");
        sprite->SetTexture(text, true);
    } else if (option == 1) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "60fps");
        sprite->SetTexture(text, true);
    } else if (option == 2) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "480fps");
        sprite->SetTexture(text, true);
    }
}

/*
  Function Objective: renders menu screen position.
  param: none.
  return: none.
*/
void GraphicsMenu::Render() {
    int positionsY[3] = {260, 409, 557};
    bg.Render(CenterVertical(&bg));
    bgOptions.Render(CenterVertical(&bgOptions) + Vec2(0, 135));
    menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite) +
                                              Vec2(0, positionsY[currentOption]));
    selectedArrow.Render(CenterVertical(&selectedArrow) + Vec2(0, positionsY[currentOption] + 72));

    menuOptions2[0].sprite->Render(CenterVertical(menuOptions2[0].sprite) +
                                   Vec2(0, positionsY[0] + 72));
    menuOptions2[1].sprite->Render(CenterVertical(menuOptions2[1].sprite) +
                                   Vec2(0, positionsY[1] + 72));
    menuOptions2[2].sprite->Render(CenterVertical(menuOptions2[2].sprite) +
                                   Vec2(0, positionsY[2] + 72));
}
