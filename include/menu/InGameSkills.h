#ifndef INGAMESKILLS_H
#define INGAMESKILLS_H

#include "menu/MenuState.h"

#define SCALE 2000

class InGameSkills: public MenuState
{
public:
	InGameSkills();
	void LoadAssets();
	void Update();
	void Render();
	void GetSkill(int skillNumber);
	~InGameSkills();
	Sprite* selected;
	Sprite blackOpacity;
};

#endif // INCLUDE_INGAMESKILLS_H_
