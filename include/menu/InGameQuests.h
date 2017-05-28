#ifndef INGAMEQUESTS_H
#define INGAMEQUESTS_H
#include "menu/MenuState.h"
#include <string>
#include <unordered_map>
#include "Sprite.h"

class InGameQuests : public MenuState
{
public:
	InGameQuests();
	void LoadAssets();
	void Update();
	void Render();
	void SetQuestText(std::string questName);
	void SetOption(int i);
private:
	std::unordered_map<std::string,std::string> quests;
	Sprite *questText;

};

#endif // INGAMEQUESTS_H
