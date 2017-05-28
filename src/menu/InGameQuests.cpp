#include "menu/InGameQuests.h"
#include "Text.h"
#include "InputManager.h"
#include <vector>

InGameQuests::InGameQuests():
	questText(new Sprite())
{

}

void InGameQuests::LoadAssets()
{
	SDL_Texture *text;

	fontSize = 28;

	std::string key;

	key = "Quest 1";
	quests[key]="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Vivamus tristique eros in blandit sodales. Aliquam erat volutpat. Praesent bibendum hendrerit neque in sagittis. Suspendisse nec nisl lobortis, eleifend quam at, interdum mauris. Mauris eu accumsan neque. Etiam pulvinar pulvinar ex, ut mattis enim consectetur tincidunt";
	text = Text::GetText(fontName,fontSize,fontColor,key);
	menuOptions.push_back({key,new Sprite(text,1,0,true),true,0});

	SetQuestText(key);

	key = "Quest 2";
	quests[key]="Vestibulum tristique, enim vel tristique commodo, diam erat dignissim arcu, vel lacinia nunc urna ut mauris. In viverra, tellus quis posuere maximus, purus orci posuere purus, sed iaculis velit ante at odio. Vivamus non odio lorem. Sed vitae condimentum lectus.";
	text = Text::GetText(fontName,fontSize,fontColor,key);
	menuOptions.push_back({key,new Sprite(text,1,0,true),true,0});

	key = "Quest 3";
	quests[key]="Nam sagittis, libero vel tincidunt fermentum, ligula nisl ullamcorper ante, a iaculis ante arcu sit amet lorem. Orci varius natoque penatibus et magnis dis parturient montes, nascetur ridiculus mus. Morbi ante massa, vulputate non enim ac, dignissim elementum leo.";
	text = Text::GetText(fontName,fontSize,fontColor,key);
	menuOptions.push_back({key,new Sprite(text,1,0,true),true,0});

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
	std::string& textStr = quests[questName];
	SDL_Texture *text = Text::GetText(fontName,fontSize,fontColor,textStr,420);
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
	questText->Render(bgXY+Vec2(400,100));
}

void InGameQuests::SetOption(int i)
{
	MenuState::SetOption(i);
	SetQuestText(menuOptions[currentOption].key);
}
