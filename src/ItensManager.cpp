#include "ItensManager.h"

ItensManager::ItensManager()
{
}

std::vector<ItensManager::itemType> ItensManager::GetActiveItems()
{
	std::vector<ItensManager::itemType> v;
	for(auto i: itens)
	{
		if (i.second.active==true)
			v.emplace_back(i.second);
	}
	return v;
}

std::vector<ItensManager::itemType> ItensManager::GetItems()
{
	std::vector<ItensManager::itemType> v;
	for(auto i: itens)
	{
		v.emplace_back(i.second);
	}
	return v;
}

ItensManager::itemType ItensManager::GetItem(std::string name)
{
	return itens[name];
}

void ItensManager::AddItem(int id)
{
	std::string imageName = "items.png";
	int frameCount = 12;
	std::string name = "";
	std::string desc = "";
	switch (id)
	{
		case 1:
			name = "Picareta";
			desc = "Picareta Legal";
			break;
		case 2:
			name = "Arco";
			desc = "Arco legal";
			break;
		case 3:
			name = "Vara de pesca";
			desc = "Vara de pesca legal";
			break;
		case 4:
			name = "Coro";
			desc = "Coro legal";
			break;
		default:
			break;
	}
	if (name!="")
	{
		if (!itens.count(name))
		{
			itens.emplace(name,itemType{
							  new Sprite(imageName,frameCount),
							  true,
							  1,
							  name,
							  desc});
			itens[name].sp->SetFrame(id);
		}
		else
			itens[name].count++;
	}
}

bool ItensManager::IsActive(std::string name)
{
	return itens[name].active;
}

bool ItensManager::IsHot(std::string name)
{
	for(auto &i: hotItens)
	{
		if (i==name)
			return true;
	}
	return false;
}

void ItensManager::SetActive(std::string name, bool active)
{
	itens[name].active = active;
}
