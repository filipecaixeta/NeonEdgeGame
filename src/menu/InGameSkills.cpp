#include "menu/InGameSkills.h"

InGameSkills::InGameSkills()
{

}

void InGameSkills::LoadAssets()
{
	bg.Open("menus/SkillTree.png");
	bg.SetBlending(true);

}

void InGameSkills::Update()
{
	MenuState::Update();
}

void InGameSkills::Render()
{
	Vec2 bgXY = CenterHorizontal(&bg)+CenterVertical(&bg);
	bg.Render(bgXY);
}
