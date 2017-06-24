#include "ItensManager.h"

ItensManager::ItensManager()
{
	std::string imageName = "items.png";
	int frameCount = 12;
	itens.emplace("Picareta",itemType{
					  new Sprite(imageName,frameCount),
					  true,
					  1,
					  std::string("Picareta"),
					  std::string("Item legal 1")});
	itens["Picareta"].sp->SetFrame(1);
	itens.emplace("Arco",itemType{
					  new Sprite(imageName,frameCount),
					  true,
					  1,
					  std::string("Arco"),
					  std::string("Item legal 2")});
	itens["Arco"].sp->SetFrame(2);
	itens.emplace("Vara de Pescar",itemType{
					  new Sprite(imageName,frameCount),
					  true,
					  1,
					  std::string("Vara de Pescar"),
					  std::string("Item legal 3")});
	itens["Vara de Pescar"].sp->SetFrame(3);
	itens.emplace("Frango",itemType{
					  new Sprite(imageName,frameCount),
					  true,
					  1,
					  std::string("Frango"),
					  std::string("Item legal 4")});
	itens["Frango"].sp->SetFrame(4);
	itens.emplace("Couro",itemType{
					  new Sprite(imageName,frameCount),
					  true,
					  1,
					  std::string("Couro"),
					  std::string("Item legal 5")});
	itens["Couro"].sp->SetFrame(5);
	itens.emplace("Carne",itemType{
					  new Sprite(imageName,frameCount),
					  true,
					  1,
					  std::string("Carne"),
					  std::string("Item legal 6")});
	itens["Carne"].sp->SetFrame(6);
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
