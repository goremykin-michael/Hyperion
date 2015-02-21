#ifndef TRAPAVOIDTUTORIAL_H
#define TRAPAVOIDTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Utils/Text/TextUtils.h"

class TrapAvoidTutorial : public Quest
{
THISIS(TrapAvoidTutorial);

public:
	//---------------------------------TrapAvoidTutorial--------------------------------//
	TrapAvoidTutorial() :
	  _availableAreaTopPoint(CCPoint(13, 0)),
	  _iAvailableAreaWidth(5),
	  _iAvailableAreaHeight(8),
	  _trapPoint(13, 5),
	  _tunnelIntroPoint(CCPoint(13, 8)),
	  _bTunnelIntroPointPassed(false)
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
	}

	virtual ~TrapAvoidTutorial()
	{
	}
	
	//------------------------------Declarative Description-----------------------------//
	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;

		questDescription.sRewardItemSummary.push_back("bla-bla");
		questDescription.sSummary = "Bla-bla-bla.";
		questDescription.sTitle = "Pass through traps";
		
		_L("quest.trapAvoidTutorial.rewardItemSummary.1");
		_L("quest.trapAvoidTutorial.summary");
		_L("quest.trapAvoidTutorial.title");

		return questDescription;
	}
	
	//--------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return kTrapAvoidTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void saveState()
	{
	}

	virtual void restoreState()
	{
	}

	virtual void cleanup()
	{
		UNLISTEN_TO(PlayerMovedEvent);
	}

	virtual void onSetStarted()
	{
		_princessDialogDescription.sCharacterLine = "Look!\n \
			There might be\n \
			an exit from the cave!";
		_L("quest.trapAvoidTutorial.line.firstDialog");

		GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
			bind(&TrapAvoidTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
	}
	
	//-------------------------------Game Event Listeners-------------------------------//
	EVENT_LISTENER(PlayerMovedEvent)
	{
		PlayerMovedEvent * pPlayerMoved = reinterpret_cast<PlayerMovedEvent *>(from->sender);
		CCPoint currentPlayerPosition = pPlayerMoved->currentTilePosition;

		if(!_bTunnelIntroPointPassed && currentPlayerPosition == _tunnelIntroPoint)
		{
			_bTunnelIntroPointPassed = true;

			_princessDialogDescription.sCharacterLine = "Look!\n \
				There is a trap in front\n \
				of you!\n \
				You can quickly pass\n \
				throught it!";
			_L("quest.trapAvoidTutorial.line.secondDialog");

			GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
				bind(&TrapAvoidTutorial::onSecondConversationDialogClosed, this, placeholders::_1));
		}
		else if(currentPlayerPosition.y < _trapPoint.y)
		{
			UNLISTEN_TO(PlayerMovedEvent);
			
			_princessDialogDescription.sCharacterLine = "That was amazing!\nYou are very smart.";
			GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind(&TrapAvoidTutorial::onLastConversationDialogClosed, this, placeholders::_1));
            GameAPI::Instance()->removeLight(_lantern);
		}
	}

protected:
	//---------------------------------TrapAvoidTutorial--------------------------------//
	CCPoint _availableAreaTopPoint;
	int _iAvailableAreaWidth, _iAvailableAreaHeight;

	ConversationDialogDescription _princessDialogDescription;

	bool _bTunnelIntroPointPassed;
	CCPoint _trapPoint, _tunnelIntroPoint;
    
    LightSource* _lantern;

	void onFirstConversationDialogClosed(bool bAccepted)
	{
		GameAPI::Instance()->pointArrowAtFloor(_tunnelIntroPoint, kArrowPointerDirectionDown);
        _lantern = GameAPI::Instance()->highlightTile(IntPoint(_tunnelIntroPoint), 0.6f); // kostya's highlighting
		GameAPI::Instance()->focusCameraOnFloorTile(_tunnelIntroPoint, 1.f, true);

		//TODO: restrict the player to go behind the ArrowPointer
		GameAPI::Instance()->setPlayerTargetPointerEnabled(true);

		LISTEN_TO(PlayerMovedEvent);
	}

	void onSecondConversationDialogClosed(bool bAccepted)
	{
		GameAPI::Instance()->setPlayerTargetResponseToAreaOnly(_availableAreaTopPoint, _iAvailableAreaWidth, _iAvailableAreaHeight);

		CCPoint destinationPoint = _trapPoint;
		destinationPoint.y -= 2;

		GameAPI::Instance()->pointArrowAtFloor(destinationPoint, kArrowPointerDirectionDown);
        GameAPI::Instance()->moveLight(_lantern, IntPoint(destinationPoint));    
		GameAPI::Instance()->focusCameraOnFloorTile(destinationPoint, 1.f);
	}

	void onLastConversationDialogClosed(bool bAccepted)
	{
		GameAPI::Instance()->setPlayerTargetPointerEnabled(false);
		setCompleted();
	}
};

#endif //TRAPAVOIDTUTORIAL_H