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

	menuOptions.push_back({"Graphics",new Sprite("menus/screen-options-button.png"),true,0});
	menuOptions.push_back({"Controls",new Sprite("menus/controls-options-button.png"),true,0});
	menuOptions.push_back({"Sound",new Sprite("menus/audio-options-button.png"),true,0});

	bg.Open("menus/BG_Back.png");
	bgOptions.Open("menus/Settings-Menu-Neutro-Base.png");

	SetOption(1);
}

void SettingsMenu::Update()
{
	MenuState::Update();
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) )
	{
		if (SelectedOptionIs("Graphics"))
		{
			Game::GetInstance().AddState(new GraphicsMenu());
		}
		if (SelectedOptionIs("Controls"))
		{
			Game::GetInstance().AddState(new ControlsMenu());
		}
	}
}

void SettingsMenu::Render()
{
	int positionsY[3] = {374,441,507};
	bg.Render(0,0);
	bgOptions.Render(CenterVertical(&bgOptions)+Vec2(0,249));
	menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite)+Vec2(0,positionsY[currentOption]));
}
