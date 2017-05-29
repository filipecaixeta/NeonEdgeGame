#include <vector>
#include <iostream>
#include <fstream>

#include "menu/InGameQuests.h"
#include "Text.h"
#include "InputManager.h"
#include "IOFunctions.h"
#include "QuestManager.h"

InGameQuests::InGameQuests():
	questTitle(new Sprite()),
	questText(new Sprite())
{

}

void InGameQuests::LoadAssets()
{

	QuestManager qm;
	qm.ReadQuestsFile();
	questType& questsV = qm.GetQuests();

	fontSize = 28;

	for (auto &q: questsV)
	{
		quests[q.first]=q.second;
		SDL_Texture* text = Text::GetText(fontName,fontSize,fontColor,q.first);
		menuOptions.push_back({q.first,new Sprite(text,1,0,true),true,0});
	}

	bg.Open("inGameMenu.png");
	bg.SetBlending(true);

	SetOption(1);
}

void InGameQuests::Update()
{
	MenuState::Update();
}

void InGameQuests::SetQuestText(std::string questName)
{
	SDL_Texture *text;
	text = Text::GetText(fontName,fontSize*1.2,fontColor,questName,420);
	questTitle->SetTexture(text,true);
	std::string& textStr = quests[questName];
	text = Text::GetText(fontName,fontSize,fontColor,textStr,420);
	questText->SetTexture(text,true);
}

void InGameQuests::Render()
{
	int offset = 70;
	Vec2 bgXY = CenterHorizontal(&bg)+CenterVertical(&bg);
	bg.Render(bgXY);
	Vec2 pos(90,90);
	for(auto option: menuOptions)
	{
		option.sprite->Render(bgXY+pos);
		pos.y += offset;
	}
	questTitle->Render(bgXY+Vec2(400,100));
	questText->Render(bgXY+Vec2(400,150));
}

void InGameQuests::SetOption(int i)
{
	MenuState::SetOption(i);
	if (menuOptions.size()>0)
		SetQuestText(menuOptions[currentOption].key);
}
