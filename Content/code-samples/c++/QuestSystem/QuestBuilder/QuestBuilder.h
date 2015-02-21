#ifndef QUESTBUILDER_H
#define QUESTBUILDER_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/QuestSystem/QuestBuilder/ConstructedQuests/CollectItemConstructedQuest.hpp"
#include "Gameplay/QuestSystem/QuestBuilder/ConstructedQuests/KillEnemyConstructedQuest.hpp"

class QuestBuilder
{
public:
	static CollectItemConstructedQuest * constructCollectItemQuest(const CollectItemQuestDefinition & crQuestDefinition);
	static KillEnemyConstructedQuest * constructKillEnemyQuest(const KillEnemyQuestDefinition & crQuestDefinition);

protected:
	static void constructQuest(ConstructedQuest * pQuest, const ConstructedQuestDefinition & crQuestDefinition);
};

#endif //QUESTBUILDER_H