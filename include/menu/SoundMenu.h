#ifndef SOUNDMENU_H
#define SOUNDMENU_H
#include <menu/MenuState.h>

class SoundMenu : public MenuState
{
	public:
		SoundMenu();
		void LoadAssets();
		void Update();
		void Render();
};

#endif // SOUNDMENU_H
