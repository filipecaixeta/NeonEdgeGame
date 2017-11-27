#include "QuestManager.h"
#include "IOFunctions.h"
#include <cstdio>

QuestManager::QuestManager() {
}

void QuestManager::ReadQuestsFile() {
    quests.clear();
    std::string fileStr = IOFunctions::Open("resources/quests", true);
    std::stringstream file(fileStr);

		unsigned int questsNumber = 0;
		file >> questsNumber;
    questsActive.resize(questsNumber);

    for (unsigned int i = 0; i < questsNumber; i++) {
        file >> questsActive[i];
    }

    std::string newLineChar = "";
    std::getline(file, newLineChar);

    for (unsigned int i = 0; i < questsNumber; i++) {
        std::string buffLine1Key = "";
        std::getline(file, buffLine1Key);
				std::string buffLine2Text = "";
        std::getline(file, buffLine2Text);

        if (questsActive[i] == 0) {
            continue;
        }

        quests.push_back(std::make_pair(buffLine1Key, buffLine2Text));
    }
}

questType& QuestManager::GetQuests() {
    return quests;
}

void QuestManager::SetQuestStatus(std::string questName, bool active) {
    ReadQuestsFile();

    std::stringstream questS;
		char buff[255] = {};
    std::sprintf(buff, "%d", (int)quests.size());
    questS << buff << std::endl;

    for (unsigned int i = 0; i < quests.size(); i++) {
        if (quests[i].first == questName) {
            questsActive[i] = active?1:0;
				}

				std::sprintf(buff, "%d ", questsActive[i]);
				questS << buff;
    }
    questS << std::endl;
    for (unsigned int i = 0; i < quests.size(); i++) {
        questS << quests[i].first << std::endl;
        questS << quests[i].second << std::endl;
		}

    IOFunctions::Save("resources/quests", questS.str(), true);
}

bool QuestManager::GetQuestStatus(std::string questName) {
    for (unsigned int i = 0; i < quests.size(); i++) {
        if (quests[i].first == questName) {
					return questsActive[i] == 0 ? false : true;
				}
    }
    return false;
}
