/**
    Copyright (c) 2017 Neon Edge
    File Name: MainMenu.cpp
    Header File Name: MainMenu.h
    Class Name: StageState
    Objective: Class responsible for the Main Menus of the game.

*/

#include "menu/MainMenu.h"
#include "menu/SettingsMenu.h"
#include "InputManager.h"
#include "Resources.h"
#include "StageState.h"
#include "Cutscene.h"
#include "Text.h"
#include <iostream>
//#include <fstream>
//#include <string>

/**
    Objective: Function responsible to invokes the Menu State.
    @param - It does not receive parameters.
    @return - none.

*/
MainMenu::MainMenu():
	MenuState()
{
}

/**
    Objective: This function is used to stop the music of menu.
    @param - It does not receive parameters.
    @return - none.

*/
MainMenu::~MainMenu() {
	music.Stop();
}

/**
    Objective: This method load the sprites and others pictures of main Menu.
    @param - It does not receive parameters.
    @return - none.

*/
void MainMenu::LoadAssets() {
	SDL_Texture *text;
   
    //Insert in the end of menuOptions vector all Sprites associated with the buttons of main menu.
	menuOptions.push_back({"NewGame", new Sprite("menus/new-game-button.png"), true, 0});
	menuOptions.push_back({"Load", new Sprite("menus/load-game-button.png"), true, 0});
	menuOptions.push_back({"Settings", new Sprite("menus/settings-button.png"), true, 0});
	menuOptions.push_back({"Exit", new Sprite("menus/exit-button.png"), true, 0});

	bg.OpenFile("menus/BG_Back.png"); // Open the main menu Background.

	bgOptions.OpenFile("menus/Menu-Neutro-Base.png");

    // Put the sounds of main menu to play.
	music.Open("menuTheme.ogg");
	music.Play(-1); 

	SetOption(1);
}

/**
    Objective: Function that makes the control of main Menu options.
    @param - It does not receive parameters.
    @return - none.

*/
void MainMenu::Update() {
	MenuState::Update();
    // Checks the event decision of player in main menu and run theis respectives stages.
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) || InputManager::GetInstance().KeyPress(SDLK_RETURN) ) {
        
        // Check if the event was "NewGame".
		if (SelectedOptionIs("NewGame")) {
			music.Stop();
			Game::GetInstance().AddState(new StageState("cidadeGalahad")); // Initializing the stage cidadeGalahad, the beginning of thegame.
		}
        // Check if the event was "Load".
		else if (SelectedOptionIs("Load")){
		}
        // Check if the event was "Settings".
		else if (SelectedOptionIs("Settings")) {
			Game::GetInstance().AddState(new SettingsMenu());
		}
        // Check if the event was "Exit".
		else if (SelectedOptionIs("Exit")) {
			exit(0);
			quitRequested = true; // Set to truth the variable that is responsible to validate the quit request of the game.
		}
	}
}

/**
    Objective: Function that that render the Menu.
    @param - It does not receive parameters.
    @return - none.

*/
void MainMenu::Render() {
	int positionsY[4] = {431,498,564,631}; // Set with precision the position that will be have rendereing the main menu.
	bg.RenderScreenPosition(CenterVertical(&bg));
	bgOptions.RenderScreenPosition(CenterVertical(&bgOptions)+Vec2(0,431));
	menuOptions[currentOption].sprite->RenderScreenPosition(CenterVertical(menuOptions[currentOption].sprite)+Vec2(0,positionsY[currentOption]));
}
