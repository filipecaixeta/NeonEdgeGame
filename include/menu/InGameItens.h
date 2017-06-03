#ifndef INGAMEITENS_H
#define INGAMEITENS_H

#include "menu/MenuState.h"

class InGameItens : public MenuState
{
public:
	InGameItens();
	void LoadAssets();
	void Update();
	void Render();
};

#endif // INGAMEITENS_H
