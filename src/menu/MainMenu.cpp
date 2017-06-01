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

	text = Text::GetText(fontName,fontSize,fontColor,"Lancelot");
	menuOptions.push_back({"Lancelot",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Gallahad");
	menuOptions.push_back({"Gallahad",new Sprite(text,1,0,true),true,0});

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
		if (menuOptions[currentOption].key=="Lancelot")
		{
			Game::GetInstance().AddState(new StageState("Lancelot"));
		}
		if (menuOptions[currentOption].key=="Gallahad")
		{
			Game::GetInstance().AddState(new StageState("Gallahad"));
		}
		else if (menuOptions[currentOption].key=="Load")
		{
/*			std::fstream fs;
			std::string Resolution;
			fs.open("Resolution.txt", std::fstream::in);
			fs.read("Resolution", sizeof(std::string));
			if (Resolution == "4x3")
			{
				Game::GetInstance().SetScreenSize(Game::GetInstance().res4x3);
			}
			else if (Resolution == "16x9")
			{
				Game::GetInstance().SetScreenSize(Game::GetInstance().res16x9);
			}
			else if (Resolution == "16x9")
			{
				Game::GetInstance().SetScreenSize(Game::GetInstance().res21x9);
			}
			fs.close();

			std::string WindowMode;
			fs.open("WindowMode.txt", std::fstream::in);
			fs.read("WindowMode", sizeof(std::string));
			if (WindowMode == "Windowed")
			{
				Game::GetInstance().setFullScreen(false);
			}
			else if (WindowMode == "21x9")
			{
				Game::GetInstance().setFullScreen(true);
			}
			fs.close();

			int FPS;
			fs.open("FPS.txt", std::fstream::in)
			fs.read(FPS, sizeof(int));
			Game::GetInstance().fps = FPS;
			fs.close();

			int moveLeftOption;
			fs.open("moveLeftOption.txt", std::fstream::in);
			fs.read(moveLeftOption, sizeof(int));
			InputManager::GetInstance().SetTranslationKey(MOVE_LEFT_KEY, moveLeftOption);
			fs.close();

			int moveRightOption;
			fs.open("moveRightOption.txt", std::fstream::in);
			fs.read(moveRightOption, sizeof(int));
			InputManager::GetInstance().SetTranslationKey(MOVE_RIGHT_KEY, moveRightOption);
			fs.close();

			int moveDownOption;
			fs.open("moveDownOption.txt", std::fstream::in);
			fs.read(moveDownOption, sizeof(int));
			InputManager::GetInstance().SetTranslationKey(MOVE_DOWN_KEY, moveDownOption);
			fs.close();

			int jumpOption;
			fs.open("jumpOption.txt", std::fstream::in);
			fs.read(jumpOption, sizeof(int));
			InputManager::GetInstance().SetTranslationKey(JUMP_KEY, jumpOption);
			fs.close();

			int attackOption;
			fs.open("attackOption.txt", std::fstream::in);
			fs.read(attackOption, sizeof(int));
			InputManager::GetInstance().SetTranslationKey(ATTACK_KEY, attackOption);
			fs.close();*/
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
