#include <cstdio>

#include "menu/InGameItens.h"
#include "InputManager.h"
#include "Text.h"

InGameItens::InGameItens(ItensManager* itensManager_):
	itensManager(itensManager_),
	rowSize(3),
	itemTitle(new Sprite()),
	itemText(new Sprite()),
	isOnHotBar(false)
{
	rowSize=HOT_BAR_SIZE;
	fontSize = 15;
}

InGameItens::~InGameItens()
{
	menuOptions.clear();
	hotBarOptions.clear();
}

void InGameItens::LoadAssets()
{
	itens = itensManager->GetActiveItems();

//	itensManager->hotItens[1] = "Arco";

	for(auto &i: itens)
	{
		menuOptions.push_back({i.name,i.sp,true,0});
	}

	for(int i=0; i<HOT_BAR_SIZE; i++)
	{
		std::string itemName = itensManager->hotItens[i];
		if (itemName.length()>0)
		{
			auto item = itensManager->GetItem(itemName);
			hotBarOptions.push_back({itemName,item.sp,true,0});
		}
		else
		{
			hotBarOptions.push_back({"",new Sprite(),false,0});
		}
	}


	bg.Open("menus/MenuItensGalahad.png");
	bg.SetBlending(true);
	SetOption(1);
	if (itens.size()!=0)
		SetItemText(itens[0]);
}

void InGameItens::SetItemText(ItensManager::itemType item)
{
	SDL_Texture *text;
	text = Text::GetText(fontName,fontSize*1.2,fontColor,item.name,400);
	itemTitle->SetTexture(text,true);
	text = Text::GetText(fontName,fontSize,fontColor,item.description,400);
	itemText->SetTexture(text,true);
}

void InGameItens::Update()
{
	if(InputManager::GetInstance().KeyPress((int)'q'))
	{
		quitRequested = true;
	}
	if (isOnHotBar)
	{
		if(InputManager::GetInstance().KeyPress(SDLK_LEFT))
		{
			SetHotBarOption(-1);
		}
		if(InputManager::GetInstance().KeyPress(SDLK_RIGHT))
		{
			SetHotBarOption(1);
		}
		if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
			InputManager::GetInstance().KeyPress(SDLK_RETURN) )
		{
			isOnHotBar = !isOnHotBar;

			hotBarOptions[currentHotBarOption] = menuOptions[currentOption];
			hotBarOptions[currentHotBarOption].sprite = menuOptions[currentOption].sprite;
			itensManager->hotItens[currentHotBarOption] = menuOptions[currentOption].key;

			for(int i=0; i<hotBarOptions.size(); i++)
			{
				if (i==currentHotBarOption)
					continue;
				if (hotBarOptions[currentHotBarOption].key == hotBarOptions[i].key)
				{
					hotBarOptions[i].sprite = new Sprite();
					hotBarOptions[i].selectable = false;
					hotBarOptions[i].key = "";
					itensManager->hotItens[i] = "";
				}
			}
		}
	}
	else
	{
		if(InputManager::GetInstance().KeyPress(SDLK_UP))
		{
			if (currentOption-rowSize<=menuOptions.size())
				SetOption(-rowSize);
		}
		if(InputManager::GetInstance().KeyPress(SDLK_DOWN))
		{
			if (currentOption+rowSize<menuOptions.size())
				SetOption(rowSize);
		}
		if(InputManager::GetInstance().KeyPress(SDLK_LEFT))
		{
			SetOption(-1);
		}
		if(InputManager::GetInstance().KeyPress(SDLK_RIGHT))
		{
			SetOption(1);
		}
		if(	InputManager::GetInstance().KeyPress(SDLK_KP_ENTER) ||
			InputManager::GetInstance().KeyPress(SDLK_RETURN) )
		{
			isOnHotBar = !isOnHotBar;
		}
	}
}

void InGameItens::SetOption(int i)
{
	MenuState::SetOption(i);
	if (itens.size()!=0)
		SetItemText(itens[currentOption]);
}

void InGameItens::SetHotBarOption(int i)
{
	if (!hotBarOptions.size())
		return;

	currentHotBarOption = currentHotBarOption+i;
	if (currentHotBarOption<0)
	{
		currentHotBarOption = hotBarOptions.size()+i;
	}
	currentHotBarOption = currentHotBarOption%hotBarOptions.size();

	for (unsigned int j=0; j<hotBarOptions.size(); j++)
	{
		hotBarOptions[j].sprite->SetScaleX(1.0);
		hotBarOptions[j].sprite->SetScaleY(1.0);
	}
	hotBarOptions[currentHotBarOption].sprite->SetScaleX(1.1);
	hotBarOptions[currentHotBarOption].sprite->SetScaleY(1.1);
}

void InGameItens::Render()
{
	Vec2 bgXY = CenterHorizontal(&bg)+CenterVertical(&bg);
	bg.Render(bgXY);
	Vec2 pos(27,101-96);
	int i=0;
	for(auto option: menuOptions)
	{
		if (i%rowSize==0)
		{
			pos.y += 96;
			pos.x = 27;
		}
		option.sprite->Render(bgXY+pos);
		pos.x += 92;
		i++;
	}
	pos = Vec2(27,373);
	for(auto option: hotBarOptions)
	{
		option.sprite->Render(bgXY+pos);
		pos.x += 92;
	}
	itemTitle->Render(bgXY+Vec2(323,111));
	itemText->Render(bgXY+Vec2(323,151));
}
