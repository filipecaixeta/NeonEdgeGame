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

MainMenu::MainMenu():
	MenuState()
{
}

MainMenu::~MainMenu(){
	music.Stop();
}

void MainMenu::LoadAssets()
{
	SDL_Texture *text;

	menuOptions.push_back({"Galahad",new Sprite("menus/new-game-button.png"),true,0});
	menuOptions.push_back({"Lancelot",new Sprite("menus/new-game-button.png"),true,0});
	menuOptions.push_back({"Load",new Sprite("menus/load-game-button.png"),true,0});
	menuOptions.push_back({"Settings",new Sprite("menus/settings-button.png"),true,0});
	menuOptions.push_back({"Exit",new Sprite("menus/exit-button.png"),true,0});

	bg.Open("menus/BG_Back.png");

	bgOptions.Open("menus/Menu-Neutro-Base.png");

	music.Open("menuTheme.ogg");
	music.Play(-1);

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
			music.Stop();
			Game::GetInstance().AddState(new Cutscene(0, true));
		}
		if (SelectedOptionIs("Galahad"))
		{
			music.Stop();
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
	int positionsY[5] = {370,431,498,564,631};
	bg.Render(CenterVertical(&bg));
	bgOptions.Render(CenterVertical(&bgOptions)+Vec2(0,431));
	menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite)+Vec2(0,positionsY[currentOption]));
}
