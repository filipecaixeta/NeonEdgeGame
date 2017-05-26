#include "menu/MainMenu.h"
#include "menu/SettingsMenu.h"
#include "InputManager.h"
#include "Resources.h"
#include "StageState.h"
#include "Text.h"
#include <iostream>

MainMenu::MainMenu()
{

}

void MainMenu::LoadAssets()
{
	SDL_Texture *text;
	std::string fontName = "Call me maybe.ttf";
	int fontSize = 72;
	SDL_Color fontColor = {0,0,0,255};

	text = Text::GetText(fontName,fontSize,fontColor,"Play");
	menuOptions.push_back(std::make_pair("Play",new Sprite(text,1,0,true)));

	text = Text::GetText(fontName,fontSize,fontColor,"Load");
	menuOptions.push_back(std::make_pair("Load",new Sprite(text,1,0,true)));

	text = Text::GetText(fontName,fontSize,fontColor,"Settings");
	menuOptions.push_back(std::make_pair("Settings",new Sprite(text,1,0,true)));

	text = Text::GetText(fontName,fontSize,fontColor,"Credits");
	menuOptions.push_back(std::make_pair("Credits",new Sprite(text,1,0,true)));

	text = Text::GetText(fontName,fontSize,fontColor,"Exit");
	menuOptions.push_back(std::make_pair("Exit",new Sprite(text,1,0,true)));

	bg.Open("mainMenuBg.png");

	SetOption(0);
}

void MainMenu::Update()
{
	MenuState::Update();
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) )
	{
		if (menuOptions[currentOption].first=="Play")
		{
			Game::GetInstance().AddState(new StageState());
		}
		else if (menuOptions[currentOption].first=="Load")
		{

		}
		else if (menuOptions[currentOption].first=="Settings")
		{
			Game::GetInstance().AddState(new SettingsMenu());
		}
		else if (menuOptions[currentOption].first=="Credits")
		{

		}
		else if (menuOptions[currentOption].first=="Exit")
		{
			quitRequested = true;
		}
	}
}

void MainMenu::Render()
{
	MenuState::Render();
}
