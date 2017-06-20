#include "menu/inGamePause.h"
#include "menu/SettingsMenu.h"
#include "menu/MainMenu.h"
#include "menu/InGameItens.h"
#include "InputManager.h"
#include "StageState.h"

inGamePause::inGamePause(StageState *stageState_):
	MenuState(),
	stageState(stageState_)
{

}

void inGamePause::LoadAssets()
{
	SDL_Texture *text;

	menuOptions.push_back({"Skills",new Sprite("menus/skills-button.png"),true,0});
	menuOptions.push_back({"Inventory",new Sprite("menus/inventory-button.png"),true,0});
	menuOptions.push_back({"Settings",new Sprite("menus/settings-button.png"),true,0});
	menuOptions.push_back({"MainMenu",new Sprite("menus/main-menu-button.png"),true,0});

	bgOptions.Open("menus/Pause-Menu-Neutro-Base.png");

	SetOption(1);
}

void inGamePause::Update()
{
	MenuState::Update();
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) )
	{
		if (SelectedOptionIs("Skills"))
		{
//			Game::GetInstance().AddState(new GraphicsMenu());
		}
		else if (SelectedOptionIs("Inventory"))
		{
			stageState->inGameMenu = new InGameItens(stageState->itensManager);
			stageState->inGameMenu->LoadAssets();
//			StageState.get()->inGameMenu = new InGameItens(itensManager);
//			Game::GetInstance().AddState(new InGameItens(itensManager));
		}
		else if (SelectedOptionIs("Settings"))
		{
			Game::GetInstance().AddState(new SettingsMenu());
		}
		else if (SelectedOptionIs("MainMenu"))
		{
			Game::GetInstance().AddState(new MainMenu());
		}
	}
}

void inGamePause::Render()
{
	int positionsY[4] = {383,448,514,581};
	bgOptions.Render(CenterVertical(&bgOptions)+Vec2(0,123));
	menuOptions[currentOption].sprite->Render(CenterVertical(menuOptions[currentOption].sprite)+Vec2(0,positionsY[currentOption]));
}
