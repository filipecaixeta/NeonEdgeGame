#include <menu/MainMenu.h>
#include <InputManager.h>
#include <Resources.h>
#include <StageState.h>
#include <iostream>

MainMenu::MainMenu()
{

}

void MainMenu::LoadAssets()
{
	SDL_Texture *text;
	std::string fontName = "Call me maybe.ttf";
	int fontSize = 72;
	SDL_Color fontColor = {255,255,255,255};


	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Play",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Play",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Load",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Load",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Settings",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Settings",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Credits",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Credits",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Exit",
							  fontName,fontSize,fontColor);
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
	}
}

void MainMenu::Render()
{
	MenuState::Render();
}
