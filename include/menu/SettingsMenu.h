#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H
#include "MenuState.h"

class SettingsMenu : public MenuState
{
public:
	SettingsMenu();
	void LoadAssets();
	void Update();
	void Render();
};

#endif // SETTINGSMENU_H
