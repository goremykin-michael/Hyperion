#ifndef QUESTFQCTORY_H
#define QUESTFQCTORY_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/QuestSystem/QuestIDs.h"
#include "Gameplay/QuestSystem/QuestBuilder/QuestBuilder.h"

#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/ActionTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/EscapeTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/BuildingTutorialQuests/DiggingTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/BuildingTutorialQuests/RoomBuildingTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/BuildingTutorialQuests/TrapBuildingTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/BuildingTutorialQuests/DecorationTutorial.hpp"
#include "Gameplay/QuestSystem/QuestBuilder/ConstructedQuests/CollectItemConstructedQuest.hpp"
#include "Gameplay/QuestSystem/QuestBuilder/ConstructedQuests/KillEnemyConstructedQuest.hpp"

class Quest_Abstract_Factory;

class QuestFactory
{
public:
	static Quest * createQuestByID(QuestID questID)
	{
		switch(questID)
		{
			case(kDecorationTutorialID):
				{
					return new DecorationTutorial();
				}
				break;
			case(kDiggingTutorialID):
				{
					return new DiggingTutorial();
				}
				break;
			case(kRoomBuildingTutorialID):
				{
					return new RoomBuildingTutorial();
				}
				break;
			case(kTrapBuildingTutorialID):
				{
					return new TrapBuildingTutorial();
				}
				break;
			case(kActionTutorialID):
				{
					return new ActionTutorial();
				}
				break;
			case(kEscapeTutorialID):
				{
					return new EscapeTutorial();
				}
				break;
			case (kKillEnemy1ID):
				{
					KillEnemyQuestDefinition questDefinition;
					questDefinition.bIsSkippable = false;
					questDefinition.bIsStartForced = false;
					questDefinition.iCountOfEnemiesToBeKilled = 5;
					questDefinition.questID = kKillEnemy1ID;

					questDefinition.questDescription.sRewardItemSummary.push_back("XP");
					questDefinition.questDescription.sRewardItemSummary.push_back("loot");
					questDefinition.questDescription.sSummary = "Kill " + TextUtils::ToString(questDefinition.iCountOfEnemiesToBeKilled) + " enemies";
					questDefinition.questDescription.sTitle = "Kill the enemies";

					questDefinition.questButtonDescription.sIconImagePath = "assets/interface/bars/quest-bar/quest-icon-kill-enemy-1.png";
					questDefinition.questButtonDescription.bUseProgressLabel = true;
					questDefinition.questButtonDescription.iNumberOfSteps = questDefinition.iCountOfEnemiesToBeKilled;

					questDefinition.questDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/quest-dialog/quest-dialog-background1.png";
					questDefinition.questDialogDescription.sCharacterImagePath = "assets/interface/dialogs/quest-dialog/quest-character-fairy.png";

					return QuestBuilder::constructKillEnemyQuest(questDefinition);
				}
				break;
			case (kCollectItem1ID):
				{
					// setting up quest description
					ConstructedQuestDefinition questDefinition;
					questDefinition.questID = kCollectItem1ID;
					questDefinition.bSubquestsAreOrdered = false;
					questDefinition.bIsStartForced = false;
					questDefinition.questDescription.sRewardItemSummary.push_back("loot");
					questDefinition.questDescription.sSummary = "Collect following items to achieve something";
					questDefinition.questDescription.sTitle = "Collect the items";

					questDefinition.questButtonDescription.sIconImagePath = "assets/interface/bars/quest-bar/quest-icon-kill-enemy-1.png";
					questDefinition.questButtonDescription.bUseProgressLabel = true;
					questDefinition.questButtonDescription.iNumberOfSteps = 2;

					questDefinition.questDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/quest-dialog/quest-dialog-background1.png";
					questDefinition.questDialogDescription.sCharacterImagePath = "assets/interface/dialogs/quest-dialog/quest-character-fairy.png";

					CollectItemQuestDefinition quest1Definition;
					quest1Definition.bIsSkippable = true;
					quest1Definition.bIsStartForced = false;
					quest1Definition.questID = kCollectItem11ID;
					quest1Definition.sTypeOfCollectedItem = "axe";
					quest1Definition.iCountOfItemsToCollect = 1;
					quest1Definition.questDescription.sTitle = "Find the Axe";

					CollectItemQuestDefinition quest2Definition;
					quest2Definition.bIsSkippable = true;
					quest2Definition.bIsStartForced = false;
					quest2Definition.questID = kCollectItem12ID;
					quest2Definition.sTypeOfCollectedItem = "armor";
					quest2Definition.iCountOfItemsToCollect = 1;
					quest2Definition.questDescription.sTitle = "Find the Armor";

					// creating the quest
					ConstructedQuest * pContainerQuest = new ConstructedQuest();
					pContainerQuest->setQuestDescription(questDefinition.questDescription);
					pContainerQuest->setQuestButtonDescription(questDefinition.questButtonDescription);
					pContainerQuest->setQuestDialogDescription(questDefinition.questDialogDescription);

					pContainerQuest->addSubquest(QuestBuilder::constructCollectItemQuest(quest1Definition));
					pContainerQuest->addSubquest(QuestBuilder::constructCollectItemQuest(quest2Definition));

					return pContainerQuest;
				}
				break;
			default:
				{
					return nullptr;
				}
				break;
		}
	}

	static std::vector<QuestID> getAllQuestIDs()
	{
		std::vector<QuestID> allQuestIDs;

		allQuestIDs.push_back(kDecorationTutorialID);
		allQuestIDs.push_back(kDiggingTutorialID);
		allQuestIDs.push_back(kRoomBuildingTutorialID);
		allQuestIDs.push_back(kTrapBuildingTutorialID);
		allQuestIDs.push_back(kActionTutorialID);
		allQuestIDs.push_back(kEscapeTutorialID);
		allQuestIDs.push_back(kKillEnemy1ID);
		allQuestIDs.push_back(kCollectItem1ID);

		return allQuestIDs;
	}
};

#endif //QUESTFQCTORY_H