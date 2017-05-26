#include "menu/SettingsMenu.h"
#include "menu/GraphicsMenu.h"
#include "menu/ControlsMenu.h"
#include "Text.h"
#include "InputManager.h"

SettingsMenu::SettingsMenu():
	MenuState()
{
}

void SettingsMenu::LoadAssets()
{
	SDL_Texture *text;

	text = Text::GetText(fontName,fontSize,fontColor,"Graphics");
	menuOptions.push_back({"Graphics",new Sprite(text,1,0,true),true,0});
	text = Text::GetText(fontName,fontSize,fontColor,"Sound");
	menuOptions.push_back({"Sound",new Sprite(text,1,0,true),true,0});
	text = Text::GetText(fontName,fontSize,fontColor,"Controls");
	menuOptions.push_back({"Controls",new Sprite(text,1,0,true),true,0});

	bg.Open("mainMenuBg.png");

	SetOption(1);
}

void SettingsMenu::Update()
{
	MenuState::Update();
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) )
	{
		if (menuOptions[currentOption].key=="Graphics")
		{
			Game::GetInstance().AddState(new GraphicsMenu());
		}
		if (menuOptions[currentOption].key=="Controls")
		{
			Game::GetInstance().AddState(new ControlsMenu());
		}
	}
}

void SettingsMenu::Render()
{
	MenuState::Render();
}
