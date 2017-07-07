#ifndef INGAMEQUESTS_H
#define INGAMEQUESTS_H

#include <string>
#include <unordered_map>

#include "menu/MenuState.h"
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
	void ReadQuestsFile();
private:
	std::unordered_map<std::string,std::string> quests;
	Sprite *questTitle;
	Sprite *questText;
	Sprite blackOpacity;
};

#endif // INGAMEQUESTS_H
