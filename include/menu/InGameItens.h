#ifndef INGAMEITENS_H
#define INGAMEITENS_H

#include "menu/MenuState.h"
#include "ItemsManager.h"

class InGameItens : public MenuState
{
public:
	InGameItens(ItemsManager *itensManager_);
	~InGameItens();
	void LoadAssets();
	void Update();
	void Render();
	void SetItemText(ItemsManager::itemType item);
	void SetHotBarOption(int i);
	void SetOption(int i);
private:
	ItemsManager *itemsManager;
	std::vector<ItemsManager::itemType> items;
	unsigned int rowSize;
	Sprite *itemTitle;
	Sprite *itemText;
	std::vector<Option> hotBarOptions;
	int currentHotBarOption;
	bool isOnHotBar;
	Sprite blackOpacity;
	Sprite* selected;
	Vec2 currentPosition;
};

#endif // INGAMEITENS_H
