#include "Gameplay/QuestSystem/QuestBuilder/QuestBuilder.h"

CollectItemConstructedQuest * QuestBuilder::constructCollectItemQuest(const CollectItemQuestDefinition & crQuestDefinition)
{
	CollectItemConstructedQuest * pCollectItemConstructedQuest = new CollectItemConstructedQuest();
	
	// construct quest as ConstructedQuest
	constructQuest(pCollectItemConstructedQuest, crQuestDefinition);

	// construct quest as CollectItemConstructedQuest
	pCollectItemConstructedQuest->setTypeOfCollectedItem(crQuestDefinition.sTypeOfCollectedItem);
	pCollectItemConstructedQuest->setCountOfItemsToCollect(crQuestDefinition.iCountOfItemsToCollect);

	return pCollectItemConstructedQuest;
}

KillEnemyConstructedQuest * QuestBuilder::constructKillEnemyQuest(const KillEnemyQuestDefinition & crQuestDefinition)
{
	KillEnemyConstructedQuest * pKillEnemyConstructedQuest = new KillEnemyConstructedQuest();

	// construct quest as ConstructedQuest
	constructQuest(pKillEnemyConstructedQuest, crQuestDefinition);

	// construct quest as KillEnemyConstructedQuest
	pKillEnemyConstructedQuest->setCountOfEnemiesToBeKilled(crQuestDefinition.iCountOfEnemiesToBeKilled);

	return pKillEnemyConstructedQuest;
}

void QuestBuilder::constructQuest(ConstructedQuest * pQuest, const ConstructedQuestDefinition & crQuestDefinition)
{
	pQuest->setQuestID(crQuestDefinition.questID);
	pQuest->setSkippable(crQuestDefinition.bIsSkippable);
	pQuest->setStartForced(crQuestDefinition.bIsStartForced);
	pQuest->setSubquestsAreOrdered(crQuestDefinition.bSubquestsAreOrdered);

	pQuest->setQuestDescription(crQuestDefinition.questDescription);
	pQuest->setQuestButtonDescription(crQuestDefinition.questButtonDescription);
	pQuest->setQuestDialogDescription(crQuestDefinition.questDialogDescription);
}