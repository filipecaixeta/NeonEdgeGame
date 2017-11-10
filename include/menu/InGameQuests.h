#ifndef INGAMEQUESTS_H
#define INGAMEQUESTS_H

#include <string>
#include <unordered_map>

#include "menu/MenuState.h"
#include "Sprite.h"

#define FONT_SIZE 24
#define LETTER_SPACING 320
#define FIFTY_PER_CENT 0.5
#define EIGHTY_PER_CENT 0.8
#define OFFSET_VALUE 50
#define SCALE 2000

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

#endif // INCLUDE_INGAMEQUESTS_H
