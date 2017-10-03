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

	fontSize = 24;

	for (auto &q: questsV)
	{
		quests[q.first]=q.second;
		SDL_Texture* text = Text::GetText(fontName,fontSize,fontColor,q.first,320);
		menuOptions.push_back({q.first,new Sprite(text,1,0,true),true,0});
	}

	std::string path = "menus/"+StageState::player->name;

	bg.OpenFile(path+"MenuQuest.png");
	bg.SetBlending(true);

	blackOpacity.OpenFile("menus/smallBlack.png",true);
	blackOpacity.SetScaleX(2000);
	blackOpacity.SetScaleY(2000);
	blackOpacity.SetTransparency(0.5);

	SetOption(1);
}

void InGameQuests::Update()
{
	MenuState::Update();
}

void InGameQuests::SetQuestText(std::string questName)
{
	SDL_Texture *text;
	text = Text::GetText(fontName,fontSize,fontColor,questName,320);
	questTitle->SetTexture(text,true);
	std::string& textStr = quests[questName];
	text = Text::GetText(fontName,fontSize*0.8,fontColor,textStr,320);
	questText->SetTexture(text,true);
}

void InGameQuests::Render()
{
	blackOpacity.RenderTexture(0,0);
	int offset = 50;
	Vec2 bgXY = CenterHorizontal(&bg)+CenterVertical(&bg);
	bg.RenderScreenPosition(bgXY);
	Vec2 pos(17,50);
	for(auto option: menuOptions)
	{
		option.sprite->RenderScreenPosition(bgXY+pos);
		pos.y += offset;
	}
	questTitle->RenderScreenPosition(bgXY+Vec2(255,50));
	questText->RenderScreenPosition(bgXY+Vec2(255,100));
}

void InGameQuests::SetOption(int i)
{
	MenuState::SetOption(i);
	if (menuOptions.size()>0)
		SetQuestText(menuOptions[currentOption].key);
}
