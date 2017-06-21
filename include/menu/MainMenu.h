#ifndef MAINMENU_H
#define MAINMENU_H
#include <vector>
#include "menu/MenuState.h"
#include "Input.h"
#include "Sprite.h"

class MainMenu: public MenuState
{
	public:
		MainMenu();
		~MainMenu();
		void LoadAssets();
		void Update();
		void Render();
};

#endif // MAINMENU_H
