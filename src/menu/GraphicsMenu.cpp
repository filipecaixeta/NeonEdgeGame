#include "menu/GraphicsMenu.h"
#include "Text.h"
#include "InputManager.h"
//#include <fstream>

GraphicsMenu::GraphicsMenu():
	MenuState()
{

}

void GraphicsMenu::LoadAssets()
{
	SDL_Texture *text;

	text = Text::GetText(fontName,fontSize,fontColor,"Resolution");
	menuOptions.push_back({"Resolution",new Sprite(text,1,0,true),false,0});

	menuOptions.push_back({"ResolutionOption",new Sprite(),true,0});
	SDL_Point ss = Game::GetInstance().GetScreenSize();
	if (ss.x == 1024)
	{
		menuOptions[menuOptions.size()-1].current = 0;
		UpdateScreenSizeSprite(	0, menuOptions[menuOptions.size()-1].sprite);
	}
	else if (ss.x == 1360)
	{
		menuOptions[menuOptions.size()-1].current = 1;
		UpdateScreenSizeSprite(	1, menuOptions[menuOptions.size()-1].sprite);
	}
	else if (ss.x == 1792)
	{
		menuOptions[menuOptions.size()-1].current = 2;
		UpdateScreenSizeSprite(	2, menuOptions[menuOptions.size()-1].sprite);
	}

	text = Text::GetText(fontName,fontSize,fontColor,"Window Mode");
	menuOptions.push_back({"WindowMode",new Sprite(text,1,0,true),false,0});

	menuOptions.push_back({"WindowModeOption",new Sprite(),true,0});
	bool fs = Game::GetInstance().isFullScreen();
	if (fs)
	{
		menuOptions[menuOptions.size()-1].current = 1;
		UpdateWindowModeSprite(	1, menuOptions[menuOptions.size()-1].sprite);
	}
	else
	{
		menuOptions[menuOptions.size()-1].current = 0;
		UpdateWindowModeSprite(	0, menuOptions[menuOptions.size()-1].sprite);
	}

	text = Text::GetText(fontName,fontSize,fontColor,"FPS");
	menuOptions.push_back({"FPS",new Sprite(text,1,0,true),false,0});

	menuOptions.push_back({"FPSOption",new Sprite(),true,0});
	int fps = Game::GetInstance().fps;
	if (fps == 30)
	{
		menuOptions[menuOptions.size()-1].current = 0;
		UpdateFPSSprite(0, menuOptions[menuOptions.size()-1].sprite);
	}
	else if (fps == 60)
	{
		menuOptions[menuOptions.size()-1].current = 1;
		UpdateFPSSprite(1, menuOptions[menuOptions.size()-1].sprite);
	}
	else if (fps == 480)
	{
		menuOptions[menuOptions.size()-1].current = 2;
		UpdateFPSSprite(2, menuOptions[menuOptions.size()-1].sprite);
	}

	bg.Open("mainMenuBg.png");

	SetOption(1);
}

void GraphicsMenu::Update()
{
	MenuState::Update();
	int rl = 0;

	if(	InputManager::GetInstance().KeyPress(SDLK_RIGHT) )
		rl = 1;
	if(	InputManager::GetInstance().KeyPress(SDLK_LEFT) )
		rl = -1;
	if (rl!=0)
	{

		if (menuOptions[currentOption].key=="ResolutionOption")
		{
//			std::fstream fs;
			menuOptions[currentOption].current = (menuOptions[currentOption].current+rl)%3;
			if (menuOptions[currentOption].current<0)
				menuOptions[currentOption].current = 2;

			if (menuOptions[currentOption].current == 0)
			{
				Game::GetInstance().SetScreenSize(Game::GetInstance().res4x3);
//				fs.open("Resolution.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("4x3", sizeof(std::string));
			}
			else if (menuOptions[currentOption].current == 1)
			{
				Game::GetInstance().SetScreenSize(Game::GetInstance().res16x9);
//				fs.open("Resolution.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("16x9", sizeof(std::string));
			}
			else if (menuOptions[currentOption].current == 2)
			{
				Game::GetInstance().SetScreenSize(Game::GetInstance().res21x9);
//				fs.open("Resolution.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("21x9", sizeof(std::string));
			}
			UpdateScreenSizeSprite(menuOptions[currentOption].current,
								   menuOptions[currentOption].sprite);
//			fs.close();
		}
		if (menuOptions[currentOption].key=="WindowModeOption")
		{
//			std::fstream fs;
			menuOptions[currentOption].current = (menuOptions[currentOption].current+rl)%2;
			if (menuOptions[currentOption].current<0)
				menuOptions[currentOption].current = 1;

			if (menuOptions[currentOption].current == 0)
			{
				Game::GetInstance().setFullScreen(false);
//				fs.open("WindowMode.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("Windowed", sizeof(std::string));
			}
			else if (menuOptions[currentOption].current == 1)
			{
				Game::GetInstance().setFullScreen(true);
//				fs.open("WindowMode.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("Fullscreen", sizeof(std::string));
			}
			UpdateWindowModeSprite(menuOptions[currentOption].current,
								   menuOptions[currentOption].sprite);
//			fs.close();
		}
		if (menuOptions[currentOption].key=="FPSOption")
		{
//			std::fstream fs;			
			menuOptions[currentOption].current = (menuOptions[currentOption].current+rl)%3;
			if (menuOptions[currentOption].current<0)
				menuOptions[currentOption].current = 2;

			if (menuOptions[currentOption].current == 0)
			{
				Game::GetInstance().fps = 30;
//				fs.open("FPS.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("30", sizeof(std::string));
			}
			else if (menuOptions[currentOption].current == 1)
			{
				Game::GetInstance().fps = 60;
//				fs.open("FPS.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("60", sizeof(std::string));
			}
			else if (menuOptions[currentOption].current == 2)
			{
				Game::GetInstance().fps = 480;
//				fs.open("FPS.txt", std::fstream::out | std::fstream::trunc);
//				fs.write("480", sizeof(std::string));
			}
			UpdateFPSSprite(menuOptions[currentOption].current,
							menuOptions[currentOption].sprite);
		}
	}
}

void GraphicsMenu::UpdateScreenSizeSprite(int option, Sprite *sprite)
{
	if (option == 0)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"< 1024x768  (4:3) >");
		sprite->SetTexture(text,true);
	}
	else if (option == 1)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"< 1360x768 (16:9) >");
		sprite->SetTexture(text,true);
	}
	else if (option == 2)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"< 1792x768 (21:9) >");
		sprite->SetTexture(text,true);
	}
}

void GraphicsMenu::UpdateWindowModeSprite(int option, Sprite *sprite)
{
	if (option == 0)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"<   Windowed  >");
		sprite->SetTexture(text,true);
	}
	else if (option == 1)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"< Full Screen >");
		sprite->SetTexture(text,true);
	}
}

void GraphicsMenu::UpdateFPSSprite(int option, Sprite *sprite)
{
	if (option == 0)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"<  30fps  >");
		sprite->SetTexture(text,true);
	}
	else if (option == 1)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"<  60fps  >");
		sprite->SetTexture(text,true);
	}
	else if (option == 2)
	{
		SDL_Texture *text = Text::GetText(fontName,fontSize/2,fontColor,"< 480fps  >");
		sprite->SetTexture(text,true);
	}
}

void GraphicsMenu::Render()
{
	MenuState::Render();
}
