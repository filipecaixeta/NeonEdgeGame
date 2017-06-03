#include "menu/InGameItens.h"

InGameItens::InGameItens()
{

}

void InGameItens::LoadAssets()
{
	bg.Open("inGameItens.png");
	bg.SetBlending(true);
}

void InGameItens::Update()
{
	MenuState::Update();
}

void InGameItens::Render()
{
	int offset = 70;
	Vec2 bgXY = CenterHorizontal(&bg)+CenterVertical(&bg);
	bg.Render(bgXY);
}
