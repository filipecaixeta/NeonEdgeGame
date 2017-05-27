#include "menu/MainMenu.h"
#include "menu/SettingsMenu.h"
#include "InputManager.h"
#include "Resources.h"
#include "StageState.h"
#include "Text.h"
#include <iostream>

MainMenu::MainMenu():
	MenuState()
{
}

void MainMenu::LoadAssets()
{
	SDL_Texture *text;

	text = Text::GetText(fontName,fontSize,fontColor,"Play");
	menuOptions.push_back({"Play",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Load");
	menuOptions.push_back({"Load",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Settings");
	menuOptions.push_back({"Settings",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Credits");
	menuOptions.push_back({"Credits",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Exit");
	menuOptions.push_back({"Exit",new Sprite(text,1,0,true),true,0});

	bg.Open("mainMenuBg.png");

	SetOption(1);
}

void MainMenu::Update()
{
	MenuState::Update();
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) )
	{
		if (menuOptions[currentOption].key=="Play")
		{
			Game::GetInstance().AddState(new StageState("Lancelot"));
		}
		else if (menuOptions[currentOption].key=="Load")
		{

		}
		else if (menuOptions[currentOption].key=="Settings")
		{
			Game::GetInstance().AddState(new SettingsMenu());
		}
		else if (menuOptions[currentOption].key=="Credits")
		{

		}
		else if (menuOptions[currentOption].key=="Exit")
		{
			quitRequested = true;
		}
	}
}

void MainMenu::Render()
{
	MenuState::Render();
}
