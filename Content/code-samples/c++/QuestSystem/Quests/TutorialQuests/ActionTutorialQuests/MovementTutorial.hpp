#ifndef MOVEMENTTUTORIAL_H
#define MOVEMENTTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Utils/Text/TextUtils.h"

class MovementTutorial : public Quest
{
THISIS(MovementTutorial);

public:
	//---------------------------------MovementTutorial---------------------------------//
	MovementTutorial() :
	  _availableAreaTopPoint(CCPoint(0, 0)),
	  _iAvailableAreaWidth(6),
	  _iAvailableAreaHeight(5),
	  _moveTo(4.f, 5.f),
	  _pHero(nullptr),
	  _pFairy(nullptr)
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
	}

	virtual ~MovementTutorial()
	{
	}
	
	//------------------------------Declarative Description-----------------------------//
	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;

		questDescription.sRewardItemSummary.push_back("knife");
		questDescription.sRewardItemSummary.push_back("the fairy");
		questDescription.sRewardItemSummary.push_back("health bottles (x2)");
		questDescription.sSummary = "Tap the blue target pointer,\nso the king will move there.";
		questDescription.sTitle = "Learn to walk";
		
		_L("quest.movementTutorial.rewardItemSummary.1");
		_L("quest.movementTutorial.rewardItemSummary.2");
		_L("quest.movementTutorial.rewardItemSummary.3");
		_L("quest.movementTutorial.summary");
		_L("quest.movementTutorial.title");

		return questDescription;
	}

	//--------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return kMovementTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void onSetStarted()
	{
		_pHero = GameAPI::Instance()->getObjectByName("Hero");
		_pFairy = GameAPI::Instance()->getObjectByName("fairy");

		//TODO: set fairy invisible on animation finished
		_pFairy->setAnimationActive(kAnimationStatDisappear, _pHero);
		_pFairy->getSprite()->setVisible(false);

        _lantern = GameAPI::Instance()->highlightTile(IntPoint(_moveTo), 0.6f); // kostya's highlighting
		GameAPI::Instance()->pointArrowAtFloor(_moveTo, kArrowPointerDirectionDown);
		GameAPI::Instance()->setPlayerTargetPointer(_moveTo, cocos2d::ccBLUE);
		GameAPI::Instance()->setPlayerTargetForceVisible(true);
		GameAPI::Instance()->setPlayerTargetResponseToPointOnly(_moveTo);
		GameAPI::Instance()->focusCameraOnFloorTile(CCPoint(3, 4), 1);
		
		LISTEN_TO(PlayerMovedEvent);
	}

	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{
		UNLISTEN_TO(PlayerMovedEvent);
	}

	//---------------------------------Game Event Listeners-----------------------------//
    EVENT_LISTENER(PlayerMovedEvent)
	{
		PlayerMovedEvent * pPlayerMoved = reinterpret_cast<PlayerMovedEvent *>(from->sender);
		CCPoint currentPlayerPosition = pPlayerMoved->currentTilePosition;

		if(currentPlayerPosition == _moveTo)
		{
			UNLISTEN_TO(PlayerMovedEvent);

            GameAPI::Instance()->removeLight(_lantern); // kostya's highlighting
			GameAPI::Instance()->removeArrowPointer();
			GameAPI::Instance()->setPlayerTargetForceVisible(false);
			GameAPI::Instance()->setPlayerTargetResponseToAreaOnly(_availableAreaTopPoint, _iAvailableAreaWidth, _iAvailableAreaHeight);

			_princessDialogDescription.sCharacterLine = "That was amazing!\n\
            You are very smart.";
			_L("quest.movementTutorial.line.firstDialog");

			GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind(&MovementTutorial::onLastConversationDialogClosed, this, placeholders::_1));
		}
	}

protected:
	//---------------------------------MovementTutorial---------------------------------//
	CCPoint _availableAreaTopPoint;
	int _iAvailableAreaWidth, _iAvailableAreaHeight;

    LightSource* _lantern;
	CCPoint _moveTo;
	GameObject * _pHero;
	GameObject * _pFairy;
	ConversationDialogDescription _princessDialogDescription;

	void onLastConversationDialogClosed(bool bAccepted)
	{
		setCompleted();
	}
};

#endif //MOVEMENTTUTORIAL_H