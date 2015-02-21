#ifndef FINDDOORTUTORIAL_H
#define FINDDOORTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/Events/DoorOpenedEvent.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Utils/Text/TextUtils.h"

class FindDoorTutorial : public Quest
{
THISIS(FindDoorTutorial);

public:
	//---------------------------------FindDoorTutorial---------------------------------//
	FindDoorTutorial() :
	  _lantern(nullptr),
	  _aboveDoorTile(CCPoint(17, 1))
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
	}

	virtual ~FindDoorTutorial()
	{
	}
	
	//------------------------------Declarative Description-----------------------------//
	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;
		
		questDescription.sRewardItemSummary.push_back("bla-bla");
		questDescription.sSummary = "Bla-bla-bla.";
		questDescription.sTitle = "Find exit from the cave";
		
		_L("quest.findDoorTutorial.rewardItemSummary.1");
		_L("quest.findDoorTutorial.summary");
		_L("quest.findDoorTutorial.title");

		return questDescription;
	}

	//--------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return kFindDoorTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void onSetStarted()
	{
		_princessDialogDescription.sCharacterLine = "There is an exit from\n\
			cave nearby.\n \
			Get there when you are\n \
			done here.";

		_L("quest.findDoorTutorial.line.firstDialog");

		GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
			bind(&FindDoorTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
	}

	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{
		UNLISTEN_TO(DoorOpenedEvent);
	}

	//---------------------------------Game Event Listeners-----------------------------//
	EVENT_LISTENER(DoorOpenedEvent)
	{
		UNLISTEN_TO(DoorOpenedEvent);
        GameAPI::Instance()->removeLight(_lantern);
		setCompleted();
	}

protected:
	//---------------------------------FindDoorTutorial---------------------------------//
	CCPoint _aboveDoorTile;
	ConversationDialogDescription _princessDialogDescription;
    
    LightSource* _lantern;
    
	void onFirstConversationDialogClosed(bool bAccepted)
	{
		GameAPI::Instance()->setPlayerTargetPointerEnabled(true);

		GameAPI::Instance()->pointArrowAtFloor(_aboveDoorTile, kArrowPointerDirectionDown);
        _lantern = GameAPI::Instance()->highlightTile(IntPoint(_aboveDoorTile));
		GameAPI::Instance()->focusCameraOnFloorTile(_aboveDoorTile, 1.f);

		LISTEN_TO(DoorOpenedEvent);
	}
};

#endif //FINDDOORTUTORIAL_H