#include "menu/SettingsMenu.h"

SettingsMenu::SettingsMenu()
{
	SDL_Texture *text;
	std::string fontName = "Call me maybe.ttf";
	int fontSize = 72;
	SDL_Color fontColor = {255,255,255,255};

	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Graphics",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Graphics",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Sound",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Sound",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Controls",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Controls",new Sprite(text,1,0,true)));

	bg.Open("mainMenuBg.png");

	SetOption(0);
}

void SettingsMenu::LoadAssets()
{

}

void SettingsMenu::Update()
{
	MenuState::Update();
}

void SettingsMenu::Render()
{
	MenuState::Render();
}
