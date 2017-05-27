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
};

#endif // GRAPHICSMENU_H
