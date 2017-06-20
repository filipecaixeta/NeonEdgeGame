#include "menu/MainMenu.h"
#include "menu/SettingsMenu.h"
#include "InputManager.h"
#include "Resources.h"
#include "StageState.h"
#include "Text.h"
#include <iostream>
//#include <fstream>
//#include <string>

MainMenu::MainMenu():
	MenuState()
{
}

void MainMenu::LoadAssets()
{
	SDL_Texture *text;

	menuOptions.push_back({"Lancelot",new Sprite("menus/new-game-button.png"),true,0});
	menuOptions.push_back({"Load",new Sprite("menus/load-game-button.png"),true,0});
	menuOptions.push_back({"Settings",new Sprite("menus/settings-button.png"),true,0});
	menuOptions.push_back({"Exit",new Sprite("menus/exit-button.png"),true,0});

	bg.Open("menus/BG_Back.png");

	bgOptions.Open("menus/Menu-Neutro-Base.png");

	SetOption(1);
}

void MainMenu::Update()
{
	MenuState::Update();
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) )
	{
		if (SelectedOptionIs("Lancelot"))
		{
			Game::GetInstance().AddState(new StageState("Lancelot"));
		}
		if (SelectedOptionIs("Gallahad"))
		{
			Game::GetInstance().AddState(new StageState("Gallahad"));
		}
		else if (SelectedOptionIs("Load"))
		{
		}
		else if (SelectedOptionIs("Settings"))
		{
			Game::GetInstance().AddState(new SettingsMenu());
		}
		else if (SelectedOptionIs("Exit"))
		{
			quitRequested = true;
		}
	}
}

void MainMenu::Render()
{
	int positionsY[4] = {431,498,564,631};
	bg.Render(0,0);
	bgOptions.Render(CenterVertical(&bgOptions)+Vec2(0,431));
	menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite)+Vec2(0,positionsY[currentOption]));
}
