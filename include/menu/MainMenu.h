#ifndef MAINMENU_H
#define MAINMENU_H
#include <menu/MenuState.h>
#include <vector>
#include <Input.h>

class MainMenu: public MenuState
{
	public:
		MainMenu();
		void LoadAssets();
		void Update();
		void Render();
};

#endif // MAINMENU_H
