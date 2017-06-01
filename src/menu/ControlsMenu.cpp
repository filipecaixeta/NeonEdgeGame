#include "menu/ControlsMenu.h"
#include "Text.h"
#include "InputManager.h"
//#include <fstream>

ControlsMenu::ControlsMenu():
	MenuState(),
	replaceKey(false)
{

}

void ControlsMenu::LoadAssets()
{
	SDL_Texture *text;

	text = Text::GetText(fontName,fontSize,fontColor,"Move Left");
	menuOptions.push_back({"moveLeft",new Sprite(text,1,0,true),false,0});

	text = Text::GetText(fontName,fontSize,fontColor,CreateKeyString(MOVE_LEFT_KEY));
	menuOptions.push_back({"moveLeftOption",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Move Right");
	menuOptions.push_back({"moveRight",new Sprite(text,1,0,true),false,0});

	text = Text::GetText(fontName,fontSize,fontColor,CreateKeyString(MOVE_RIGHT_KEY));
	menuOptions.push_back({"moveRightOption",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Crouch");
	menuOptions.push_back({"CrouchDown",new Sprite(text,1,0,true),false,0});

	text = Text::GetText(fontName,fontSize,fontColor,CreateKeyString(CROUCH_KEY));
	menuOptions.push_back({"CrouchOption",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Jump");
	menuOptions.push_back({"jump",new Sprite(text,1,0,true),false,0});

	text = Text::GetText(fontName,fontSize,fontColor,CreateKeyString(JUMP_KEY));
	menuOptions.push_back({"jumpOption",new Sprite(text,1,0,true),true,0});

	text = Text::GetText(fontName,fontSize,fontColor,"Attack");
	menuOptions.push_back({"attack",new Sprite(text,1,0,true),false,0});

	text = Text::GetText(fontName,fontSize,fontColor,CreateKeyString(ATTACK_KEY));
	menuOptions.push_back({"attackOption",new Sprite(text,1,0,true),true,0});

	bg.Open("mainMenuBg.png");

	SetOption(1);
}

std::string ControlsMenu::CreateKeyString(int c)
{
	char buff[10];
	int v = InputManager::GetInstance().GetTranslationKey(c);
	if (v == SDLK_LEFT)
		sprintf(buff,"[ < ]");
	else if (v == SDLK_RIGHT)
		sprintf(buff,"[ > ]");
	else if (v == SDLK_UP)
		sprintf(buff,"[ ^ ]");
	else if (v == SDLK_DOWN)
		sprintf(buff,"[ v ]");
	else if (v == SDLK_SPACE)
		sprintf(buff,"[ space ]");
	else
		sprintf(buff,"[ %c ]",v);
	return buff;
}

void ControlsMenu::Update()
{
	if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
		InputManager::GetInstance().KeyPress(SDLK_RETURN) )
	{
		replaceKey = true;
		InputManager::GetInstance().GetLastKey();
	}
	else if (replaceKey == true)
	{
		int lk = InputManager::GetInstance().GetLastKey();
		if (lk != -1)
		{
//			std::fstream fs;
//			replaceKey = false;
			if (menuOptions[currentOption].key == "moveLeftOption")
			{
				InputManager::GetInstance().SetTranslationKey(MOVE_LEFT_KEY,lk);
				SDL_Texture *text = Text::GetText(fontName,fontSize,fontColor,
												  CreateKeyString(MOVE_LEFT_KEY));
				menuOptions[currentOption].sprite->SetTexture(text,true);
//				fs.open("moveLeftOption.txt", std::fstream::out | std::fstream::trunc);
//				fs.write((char*)lk, sizeof(lk));
			}
			else if (menuOptions[currentOption].key == "moveRightOption")
			{
				InputManager::GetInstance().SetTranslationKey(MOVE_RIGHT_KEY,lk);
				SDL_Texture *text = Text::GetText(fontName,fontSize,fontColor,
												  CreateKeyString(MOVE_RIGHT_KEY));
				menuOptions[currentOption].sprite->SetTexture(text,true);
//				fs.open("moveRightOption.txt", std::fstream::out | std::fstream::trunc);
//				fs.write((char*)lk, sizeof(lk));
			}
			else if (menuOptions[currentOption].key == "moveDownOption")
			{
				InputManager::GetInstance().SetTranslationKey(CROUCH_KEY,lk);
				SDL_Texture *text = Text::GetText(fontName,fontSize,fontColor,
												  CreateKeyString(CROUCH_KEY));
				menuOptions[currentOption].sprite->SetTexture(text,true);
//				fs.open("moveDownOption.txt", std::fstream::out | std::fstream::trunc);
//				fs.write((char*)lk, sizeof(lk));
			}
			else if (menuOptions[currentOption].key == "jumpOption")
			{
				InputManager::GetInstance().SetTranslationKey(JUMP_KEY,lk);
				SDL_Texture *text = Text::GetText(fontName,fontSize,fontColor,
												  CreateKeyString(JUMP_KEY));
				menuOptions[currentOption].sprite->SetTexture(text,true);
//				fs.open("jumpOption.txt", std::fstream::out | std::fstream::trunc);
//				fs.write((char*)lk, sizeof(lk));
			}
			else if (menuOptions[currentOption].key == "attackOption")
			{
				InputManager::GetInstance().SetTranslationKey(ATTACK_KEY,lk);
				SDL_Texture *text = Text::GetText(fontName,fontSize,fontColor,
												  CreateKeyString(ATTACK_KEY));
				menuOptions[currentOption].sprite->SetTexture(text,true);
//				fs.open("attackOption.txt", std::fstream::out | std::fstream::trunc);
//				fs.write((char*)lk, sizeof(lk));
			}
//			fs.close();
		}
	}
	else
		MenuState::Update();
}

void ControlsMenu::Render()
{
	MenuState::Render();
}
