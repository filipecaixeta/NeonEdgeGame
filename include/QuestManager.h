#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H
#include <unordered_map>
#include <string>
#include <vector>

typedef std::vector<std::pair<std::string,std::string>> questType;

class QuestManager
{
public:
	QuestManager();
	void ReadQuestsFile();
	questType & GetQuests();
	void SetQuestStatus(std::string questName, bool active);
	bool GetQuestStatus(std::string questName);
private:
	questType quests;
	std::vector<int> questsActive;
};

#endif // INCLUDE_QUESTMANAGER_H_
