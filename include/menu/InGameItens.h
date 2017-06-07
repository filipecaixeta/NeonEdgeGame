#ifndef INGAMEITENS_H
#define INGAMEITENS_H

#include "menu/MenuState.h"
#include "ItensManager.h"

class InGameItens : public MenuState
{
public:
	InGameItens(ItensManager *itensManager_);
	~InGameItens();
	void LoadAssets();
	void Update();
	void Render();
	void SetItemText(ItensManager::itemType item);
	void SetHotBarOption(int i);
	void SetOption(int i);
private:
	ItensManager *itensManager;
	std::vector<ItensManager::itemType> itens;
	unsigned int rowSize;
	Sprite *itemTitle;
	Sprite *itemText;
	std::vector<Option> hotBarOptions;
	int currentHotBarOption;
	bool isOnHotBar;
};

#endif // INGAMEITENS_H
