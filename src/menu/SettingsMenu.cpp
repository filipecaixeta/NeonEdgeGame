/**
 * Copyright (c) 2017 Neon Edge
 * File Name: SettingsMenu.cpp
 * Header File Name: SettingsMenu.h
 * Class Name: SerringsMenu
 * Objective: Class responsible for the settings of the game.
 */

#include "menu/SettingsMenu.h"
#include "menu/GraphicsMenu.h"
#include "menu/ControlsMenu.h"
#include "Text.h"
#include "InputManager.h"

/**
 * Objective: This function is responsible to invokes the MenuState.
 *
 * @param - none.
 * @return - none.
 */
SettingsMenu::SettingsMenu():
	MenuState()
{
}

/**
 * Objective: This function is used to load the sprites and others pictures of settings menu..
 *
 * @param - none.
 * @return - none.
 */
void SettingsMenu::LoadAssets() {
    SDL_Texture *text = NULL;

    // Insert in the end of menuOptions vector all Sprites associated with the buttons of settings menu.
    menuOptions.push_back({"Graphics", new Sprite("menus/screen-options-button.png"), true, 0});
    menuOptions.push_back({"Controls", new Sprite("menus/controls-options-button.png"), true, 0});
    menuOptions.push_back({"Sound", new Sprite("menus/audio-options-button.png"), true, 0});

    bg.Open("menus/BackgroundInicial2.png"); // Open the settings menu Background.
    bgOptions.Open("menus/Settings-Menu-Neutro-Base.png");

    SetOption(1);
}

/**
 * Objective: This function is responsible to control the options in settings menu.
 *
 * @param - none.
 * @return - none.
 */
void SettingsMenu::Update() {

    //Checks the event setting decision of player in settings menu and invoke their respectives updates.
	MenuState::Update();
	if (InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) ) {
        // Check whether the event was "Graphics" and instance the same.
		if (SelectedOptionIs("Graphics")) {
			Game::GetInstance().AddState(new GraphicsMenu());
		}
        // Check whether the event was "Graphics" and instance the same.
		if (SelectedOptionIs("Controls")) {
			Game::GetInstance().AddState(new ControlsMenu());
		}
	}
}

/**
 * Objective: This function responsible to render the entire settings menu.
 *
 * @param - none.
 * @return - none.
 */
void SettingsMenu::Render() {

    bg.Render(CenterVertical(&bg));
    bgOptions.Render(CenterVertical(&bgOptions) + Vec2(0, 249));
    int positionsY[3] = {374, 441, 507};
    menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite) + Vec2(0, positionsY[currentOption]));
}
