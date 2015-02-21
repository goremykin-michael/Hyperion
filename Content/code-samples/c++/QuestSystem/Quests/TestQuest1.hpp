#ifndef TESTQUEST1_H
#define TESTQUEST1_H

#include "../Quest.h"

class TestQuest1 : public Quest
{
public:
	TestQuest1()
	{
	}

	virtual ~TestQuest1()
	{
	}

	virtual QuestID getQuestID()
	{
		return -1;
	}

	virtual void checkWhatsAlreadyDone()
	{
	}

	virtual void saveState()
	{
	}

	virtual void restoreState()
	{
	}

	virtual void cleanup()
	{
	}

	virtual bool prerequisitesAreAccepted()
	{
		return true;
	}
    
    
    virtual bool isSkippable() { return false; }
    
    virtual void onStartQuestImplicit(){}

	virtual void onStartQuestExplicit(){}

	virtual QuestButtonDescription getQuestButtonDescription()
	{
		QuestButtonDescription questButtonDescription;

		questButtonDescription.sIconImagePath = "assets/interface/bars/quest-bar/quest-icon1.png";
		questButtonDescription.bUseProgressLabel = false;

		return questButtonDescription;
	}

	virtual QuestDialogDescription getQuestDialogDescription()
	{
		QuestDialogDescription questDialogDescription;
		questDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/quest-dialog/quest-dialog-background1.png";
		questDialogDescription.sCharacterImagePath = "assets/interface/dialogs/quest-dialog/quest-character-fairy.png";

		return questDialogDescription;
	}

	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;

		questDescription.sRewardItemSummary.push_back("axe");
		questDescription.sRewardItemSummary.push_back("the fairy");
		questDescription.sRewardItemSummary.push_back("(optionally) health\nbottles (x2)");
		questDescription.sSummary = "To get out of the dungeon alive,\nyou should learn how to behave\nin this world.";
		questDescription.sTitle = "Get Out Of The Dungeon";

		return questDescription;
	}

	virtual void rewardPlayer()
	{
	}

	virtual void onStartQuest()
	{
	}

protected:
	virtual void onSetPassive()
	{
	}
};

#endif //TESTQUEST1_H
