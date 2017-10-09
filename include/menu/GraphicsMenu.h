#ifndef GRAPHICSMENU_H
#define GRAPHICSMENU_H
#include "MenuState.h"

class GraphicsMenu : public MenuState
{
public:
	GraphicsMenu();
	void LoadAssets();
	void Update();
	void Render();
	void UpdateScreenSizeSprite(int option, Sprite* sprite);
	void UpdateWindowModeSprite(int option, Sprite* sprite);
	void UpdateFPSSprite(int option, Sprite* sprite);
	std::vector<Option> menuOptions2;
	Sprite selectedArrow;

private:
	int const INITIAL_VALUE = 0;
	int const FRAMES_PER_SECOND_30 =  30;
	int const FRAMES_PER_SECOND_60 = 60;
	int const FRAMES_PER_SECOND_480 = 480;
	int const FIRST_OPTION = 0 ;
	int const SECOND_OPTION = 1 ;
	int const THIRD_OPTION = 2 ;


};

#endif // GRAPHICSMENU_H
