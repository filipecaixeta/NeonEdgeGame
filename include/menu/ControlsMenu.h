#ifndef CONTROLSMENU_H
#define CONTROLSMENU_H
#include "menu/MenuState.h"

class ControlsMenu : public MenuState
{
public:
	ControlsMenu();
	void LoadAssets();
	void Update();
	void Render();
	std::string CreateKeyString(int c);
private:
	bool replaceKey;
};

#endif // CONTROLSMENU_H
