/**
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

/**
  *  Objective: sets graphic game.
  *
  * @param none.
  * @return none.
  *
  */
void GraphicsMenu::LoadAssets() {
	int const SCREEN_WIDTH_1024 = 1024;
	int const SCREEN_WIDTH_1360 = 1360;
	int const SCREEN_WIDTH_1792 = 1792;

    menuOptions.push_back({"Resolution", new Sprite("menus/resolution-button.png"), true, 0});
    menuOptions2.push_back({"Resolution", new Sprite(), true, 0});
    SDL_Point screenSize = Game::GetInstance().GetScreenSize();  // Screen size.
    // Verifies screen size to sets.
    if (screenSize.x == SCREEN_WIDTH_1024) {
        menuOptions2[0].current = FIRST_OPTION;
        UpdateScreenSizeSprite(0, menuOptions2[0].sprite);
    } else if (screenSize.x == SCREEN_WIDTH_1360) {
        menuOptions2[0].current = SECOND_OPTION;
        UpdateScreenSizeSprite(1, menuOptions[0].sprite);
    } else if (screenSize.x == SCREEN_WIDTH_1792) {
        menuOptions2[0].current = THIRD_OPTION;
        UpdateScreenSizeSprite(2, menuOptions2[0].sprite);
    } else {
		// Do nothing
	}

    menuOptions.push_back({"FPS", new Sprite("menus/framerate-button.png"), true, 0});
    menuOptions2.push_back({"FPS", new Sprite(), true, 0});
    int framesPerSecond = Game::GetInstance().framesPerSecond;
    // Verifies fps game to sets.
    if (framesPerSecond == FRAMES_PER_SECOND_30) {
        menuOptions2[1].current = FIRST_OPTION;
        UpdateFPSSprite(0, menuOptions2[1].sprite);
    } else if (framesPerSecond == FRAMES_PER_SECOND_60) {
        menuOptions2[1].current = SECOND_OPTION;
        UpdateFPSSprite(1, menuOptions2[1].sprite);
    } else if (framesPerSecond == FRAMES_PER_SECOND_480) {
        menuOptions2[1].current = THIRD_OPTION;
        UpdateFPSSprite(2, menuOptions2[1].sprite);
    } else {
		// Do nothing
	}

    menuOptions.push_back({"WindowMode", new Sprite("menus/window-mode-button.png"), true, 0});
    menuOptions2.push_back({"WindowMode", new Sprite(), true, 0});
    bool fullScreem = Game::GetInstance().isFullScreen();  // Fullscreen.
    // Verifies windows mode to sets.
    if (!fullScreem) {
        menuOptions2[2].current = FIRST_OPTION;
        UpdateWindowModeSprite(0, menuOptions2[2].sprite);
    } else {
        menuOptions2[2].current = SECOND_OPTION;
        UpdateWindowModeSprite(1, menuOptions2[2].sprite);
    }

    bg.Open("menus/BackgroundInicial2.png");  // Loads the second menu background image.
    bgOptions.Open("menus/Screen-Menu-Neutro-Base.png");  // Loads the menu screen options image.
    selectedArrow.Open("menus/selected-arrows.png");  // Loads arrows to selected menu option.
    SetOption(1);
}

/**
 *  Objective: sets game screen configurations.
 *  
 *	@param none.
 *  @return none.
 *
 */
void GraphicsMenu::Update() {
    MenuState::Update();
	int const RIGHT_BUTTON = 1; 
	int const LEFT_BUTTON = -1; 
    // Verifies pressed key.
    int rl = INITIAL_VALUE;
    if (InputManager::GetInstance().KeyPress(SDLK_RIGHT)) {
        rl = RIGHT_MOUSE_BUTTON;
    } else if (InputManager::GetInstance().KeyPress(SDLK_LEFT)) {
        rl = LEFT_MOUSE_BUTTON;
    }

    if (rl != INITIAL_VALUE) {
        // Verifies selected screen size.
        if (menuOptions[currentOption].key == "Resolution") {
            menuOptions2[currentOption].current = (menuOptions2[currentOption].current + rl) % 3;
            if (menuOptions2[currentOption].current < FIRST_OPTION) {
                menuOptions2[currentOption].current = THIRD_OPTION;
            } else {
				// Do nothing
			}

            if (menuOptions2[currentOption].current == FIRST_OPTION) {
                Game::GetInstance().SetScreenSize(Game::GetInstance().resolution_4x3);
            } else if (menuOptions2[currentOption].current == SECOND_OPTION) {
                Game::GetInstance().SetScreenSize(Game::GetInstance().resolution_16x9);
            } else if (menuOptions2[currentOption].current == THIRD_OPTION) {
                Game::GetInstance().SetScreenSize(Game::GetInstance().resolution_21x9);
            } else {
				// Do nothing
			}

            UpdateScreenSizeSprite(menuOptions2[currentOption].current,
                                   menuOptions2[currentOption].sprite);
        } else {
			// Do nothing
		}

        // Verifies selected windows mode.
        if (menuOptions[currentOption].key == "WindowMode") {
            menuOptions2[currentOption].current = (menuOptions2[currentOption].current + rl) % 2;
            if (menuOptions2[currentOption].current < FIRST_OPTION) {
                menuOptions2[currentOption].current = SECOND_OPTION;
            } else {
				// Do nothing
			}

            if (menuOptions2[currentOption].current == FIRST_OPTION) {
                Game::GetInstance().setFullScreen(false);
            } else if (menuOptions2[currentOption].current == SECOND_OPTION) {
                Game::GetInstance().setFullScreen(true);
            } else {
				// Do nothing
			}

            UpdateWindowModeSprite(menuOptions2[currentOption].current,
                                   menuOptions2[currentOption].sprite);
        } else {
			// Do nothing
		}

        // Verifies selected fps.
        if (menuOptions[currentOption].key == "FPS") {
            menuOptions2[currentOption].current = (menuOptions2[currentOption].current + rl) % 3;
            if (menuOptions2[currentOption].current < FIRST_OPTION) {
                menuOptions2[currentOption].current = SECOND_OPTION;
            } else {
				// Do nothing
			}

            if (menuOptions2[currentOption].current == FIRST_OPTION) {
                Game::GetInstance().framesPerSecond = FRAMES_PER_SECOND_30;
            } else if (menuOptions2[currentOption].current == SECOND_OPTION) {
                Game::GetInstance().framesPerSecond = FRAMES_PER_SECOND_60;
            } else if (menuOptions2[currentOption].current == THIRD_OPTION) {
                Game::GetInstance().framesPerSecond = FRAMES_PER_SECOND_480;
            } else {
				// Do nothing
			}

            UpdateFPSSprite(menuOptions2[currentOption].current,
                            menuOptions2[currentOption].sprite);
        } else {
			// Do nothing
		}
    } else {
		// Do nothing
	}
}

/**
 *  Objective: sets game screen size.
 * 
 *  @param int options - selected game screen size option.
 *  @param Sprite sprite.
 *  @return none.
 *
 */
void GraphicsMenu::UpdateScreenSizeSprite(int option, Sprite *sprite) {
    // Sets screen size.
    if (option == FIRST_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "1024x768  4:3");
        sprite->SetTexture(text, true);
    } else if (option == SECOND_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "1360x768 16:9");
        sprite->SetTexture(text, true);
    } else if (option == THIRD_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "1792x768 21:9");
        sprite->SetTexture(text, true);
    } else {
		// Do nothing
	}
}

/**
  * Objective: updates windows mode of game.
  *  
  *	@param int option - selected game window mode option.
  * @param Sprint sprint.
  * @return none.
  */
void GraphicsMenu::UpdateWindowModeSprite(int option, Sprite *sprite) {
    // Sets windows mode.
    if (option == FIRST_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "Windowed");
        sprite->SetTexture(text, true);
    } else if (option == SECOND_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "Full Screen");
        sprite->SetTexture(text, true);
    } else {
		// Do nothing
	}
}

/**
  *  Objective: updates fps of game.
  *  
  *	 @param int option - selected game fps option.
  *  @param Sprint sprint.
  *  @return none.
  */
void GraphicsMenu::UpdateFPSSprite(int option, Sprite *sprite) {
    // Sets fps.
    if (option == FIRST_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "30fps");
        sprite->SetTexture(text, true);
    } else if (option == SECOND_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "60fps");
        sprite->SetTexture(text, true);
    } else if (option == THIRD_OPTION) {
        SDL_Texture *text = Text::GetText(fontName, fontSize / 2, fontColor, "480fps");
        sprite->SetTexture(text, true);
    } else {
		// Do nothing
	}
}

/**
 *   Objective: renders menu screen position.
 * 
 *   @param none.
 *   @return none.
 *
 */
void GraphicsMenu::Render() {
	int const POSITION_260_Y_AXIS = 260;
	int const POSITION_409_Y_AXIS = 409;
	int const POSITION_557_Y_AXIS = 557;
	int const POSITION_72_Y_AXIS = 72;
    int positionsY[3] = {POSITION_260_Y_AXIS, POSITION_409_Y_AXIS, POSITION_557_Y_AXIS};
    bg.Render(CenterVertical(&bg));
    bgOptions.Render(CenterVertical(&bgOptions) + Vec2(0, 135));
    menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite) +
                                              Vec2(0, positionsY[currentOption]));
    selectedArrow.Render(CenterVertical(&selectedArrow) + Vec2(0, positionsY[currentOption] + POSITION_72_Y_AXIS));

    menuOptions2[FIRST_OPTION].sprite->Render(CenterVertical(menuOptions2[0].sprite) +
                                   Vec2(0, positionsY[0] + POSITION_72_Y_AXIS));
    menuOptions2[SECOND_OPTION].sprite->Render(CenterVertical(menuOptions2[1].sprite) +
                                   Vec2(0, positionsY[1] + POSITION_72_Y_AXIS));
    menuOptions2[THIRD_OPTION].sprite->Render(CenterVertical(menuOptions2[2].sprite) +
                                   Vec2(0, positionsY[2] + POSITION_72_Y_AXIS));
}
