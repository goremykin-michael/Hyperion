#ifndef BATTLETUTORIAL_H
#define BATTLETUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/Events/CharacterDiedEvent.h"

class BattleTutorial : public Quest
{
THISIS(BattleTutorial);

public:
	//----------------------------------BattleTutorial----------------------------------//
	BattleTutorial():
	  _availableAreaTopPoint(CCPoint(0, 0)),
	  _iAvailableAreaWidth(8),
	  _iAvailableAreaHeight(12),
	  _sBeetleName("tutorial-beetle")
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
	}

	virtual ~BattleTutorial()
	{
	}
	
	//------------------------------Declarative Description-----------------------------//
	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;

		questDescription.sRewardItemSummary.push_back("moral satisfaction");
		questDescription.sSummary = "Tap on the enemy,\nto defeat him.";
		questDescription.sTitle = "Kill the enemy";

		_L("quest.battleTutorial.rewardItemSummary.1");
		_L("quest.battleTutorial.summary");
		_L("quest.battleTutorial.title");

		return questDescription;
	}
	
	//--------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return kBattleTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void onSetStarted()
	{
		_princessDialogDescription.sCharacterLine =
			"Carefully!\n\
			There's a huge beetle\n\
			around the corner!";

		_L("quest.battleTutorial.line.firstDialog");

		GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
			bind(&BattleTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
	}

	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{
		UNLISTEN_TO(CharacterDiedEvent);
		_beetleClickedSlot.disconnect();
	}
	
	//-------------------------------Game Event Listeners-------------------------------//
	EVENT_LISTENER(CharacterDiedEvent)
	{
		CharacterDiedEvent * pCharacterDiedEvent = reinterpret_cast<CharacterDiedEvent *>(from->sender);

		//if(pCharacterDiedEvent->character->getName() == _sBeetleName)
		{
			UNLISTEN_TO(CharacterDiedEvent);

			GameAPI::Instance()->removeArrowPointer();
			
			GameAPI::Instance()->setPlayerTargetPointerEnabled(true);
			setCompleted();
		}
	}

protected:
	//----------------------------------BattleTutorial----------------------------------//
	CCPoint _availableAreaTopPoint;
	int _iAvailableAreaWidth, _iAvailableAreaHeight;
	string _sBeetleName;
    
    LightSource* _lantern;

	Slot<void(GameObject * pObject)> _beetleClickedSlot;
	ConversationDialogDescription _princessDialogDescription;
	
	void onFirstConversationDialogClosed(bool bAccepted)
	{
		GameObject * pBeetle = GameAPI::Instance()->getObjectByName(_sBeetleName);
		GameAPI::Instance()->focusCameraOnGameObject(pBeetle, 1.f);

		GameAPI::Instance()->pointArrowAtFloor(pBeetle->getPosition(), kArrowPointerDirectionDown);
		_beetleClickedSlot = connect(pBeetle->eventClicked, this, &BattleTutorial::onBeetleClicked);
		
		GameAPI::Instance()->setPlayerTargetResponseToAreaOnly(_availableAreaTopPoint, _iAvailableAreaWidth, _iAvailableAreaHeight);
        
        _lantern = GameAPI::Instance()->highlightTile(IntPoint(pBeetle->getPosition()), 0.6f); // kostya's highlighting
	}

	void onBeetleClicked(GameObject * pObject)
	{
		_beetleClickedSlot.disconnect();
		LISTEN_TO(CharacterDiedEvent);
        GameAPI::Instance()->removeArrowPointer();
        
        GameAPI::Instance()->removeLight(_lantern);
	}
};

#endif //BATTLETUTORIAL_H