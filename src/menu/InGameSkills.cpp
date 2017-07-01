#include "menu/InGameSkills.h"

InGameSkills::InGameSkills()
{

}

InGameSkills::~InGameSkills()
{
	delete menuOptions[0].sprite;
	menuOptions.clear();
}

void InGameSkills::LoadAssets()
{
	Sprite *sp = new Sprite("menus/skillSelected.png");
	menuOptions.push_back({"skill1",sp,true,0});
	menuOptions.push_back({"skill2",sp,true,0});
	menuOptions.push_back({"skill3",sp,true,0});
	menuOptions.push_back({"skill4",sp,true,0});
	menuOptions.push_back({"skill5",sp,true,0});
	menuOptions.push_back({"skill6",sp,true,0});
	menuOptions.push_back({"skill7",sp,true,0});

	bg.Open("menus/SkillTree.png");
	bg.SetBlending(true);

	SetOption(4);
}

void InGameSkills::Update()
{
	MenuState::Update();
}

void InGameSkills::Render()
{
	Vec2 bgXY = CenterHorizontal(&bg)+CenterVertical(&bg);
	bg.Render(bgXY);

	Vec2 positions[7] = {Vec2(130.0,162.0),Vec2(257.0,163.0),Vec2(381.0,161.0),Vec2(386.0,336.0),
						Vec2(386.0,499),Vec2(262.0,501.0),Vec2(135.0,500.0)};

	menuOptions[currentOption].sprite->Render(bgXY+positions[currentOption]);
}
