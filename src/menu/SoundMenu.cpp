#include <menu/SoundMenu.h>
#include <InputManager.h>
#include <Resources.h>

SoundMenu::SoundMenu()
{
	std::cout << "sound" <<std::endl;
}

void SoundMenu::LoadAssets()
{
	SDL_Texture *text;
	std::string fontName = "Call me maybe.ttf";
	int fontSize = 72;
	SDL_Color fontColor = {255,255,255,255};


	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Music",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Music",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Sound Effects",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Sound Effects",new Sprite(text,1,0,true)));
	text = Resources::GetText(Game::GetInstance().GetRenderer(),"Ambient Sounds",
							  fontName,fontSize,fontColor);
	menuOptions.push_back(std::make_pair("Ambient Sounds",new Sprite(text,1,0,true)));


	bg.Open("mainMenuBg.png");

	SetOption(0);
}

void SoundMenu::Update()
{
	MenuState::Update();
}

void SoundMenu::Render()
{
	MenuState::Render();
}
