#ifndef ESCAPETUTORIAL_H
#define ESCAPETUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/TrapAvoidTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/FindDoorTutorial.hpp"
#include "Utils/Text/TextUtils.h"

class EscapeTutorial : public Quest
{
THISIS(EscapeTutorial);

public:
	//-----------------------------------EscapeTutorial---------------------------------//
	EscapeTutorial() :
	  _alertPoint(CCPoint(10, 10))
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
		
		LISTEN_TO(PlayerMovedEvent);
		LISTEN_TO(QuestCompletionInfo);
		addSubquest(new TrapAvoidTutorial());
		addSubquest(new FindDoorTutorial());
	}

	virtual ~EscapeTutorial()
	{
	}
	
	//------------------------------Declarative Description-----------------------------//
	virtual QuestButtonDescription getQuestButtonDescription()
	{
		QuestButtonDescription questButtonDescription;

		questButtonDescription.sIconImagePath = "assets/interface/bars/quest-bar/quest-icon2.png";
		questButtonDescription.bUseProgressLabel = true;
		questButtonDescription.iNumberOfSteps = 2;

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

		questDescription.sRewardItemSummary.push_back("knife");
		questDescription.sSummary = "Find your way out.";
		questDescription.sTitle = "Get out of the dungeon";

		_L("quest.escapeTutorial.rewardItemSummary.1");
		_L("quest.escapeTutorial.summary");
		_L("quest.escapeTutorial.title");

		return questDescription;
	}

	//---------------------------------------Quest--------------------------------------//
	virtual QuestID getQuestID()
	{
		return kEscapeTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{
		UNLISTEN_TO(QuestCompletionInfo);
		UNLISTEN_TO(PlayerMovedEvent);
		UNLISTEN_TO(DialogShowedEvent);
	}

	//---------------------------------Game Event Listeners-----------------------------//
	EVENT_LISTENER(QuestCompletionInfo)
	{
		QuestCompletionInfo * pQuestCompletionInfo = reinterpret_cast<QuestCompletionInfo *>(from->sender);

		if(pQuestCompletionInfo->questID == kActionTutorialID)
		{
			GameAPI::Instance()->setPlayerTargetPointerEnabled(false);

			LISTEN_TO(DialogShowedEvent);
			setExplicit();
			addArrowToQuestButton();
		}
		else if(pQuestCompletionInfo->questID == kTrapAvoidTutorialID)
		{
			addArrowToQuestButton();
		}
		else if(pQuestCompletionInfo->questID == kFindDoorTutorialID)
		{
			UNLISTEN_TO(QuestCompletionInfo);
		}
	}

	EVENT_LISTENER(PlayerMovedEvent)
	{
		PlayerMovedEvent * pPlayerMoved = reinterpret_cast<PlayerMovedEvent *>(from->sender);
		CCPoint currentPlayerPosition = pPlayerMoved->currentTilePosition;

		/*CCLog(("Player: (" + TextUtils::ToString(currentPlayerPosition.x) + "; " + TextUtils::ToString(currentPlayerPosition.y) + ")").c_str());

		if(currentPlayerPosition == _alertPoint)
		{
			setActiveImplicit();
		}
		else */if(currentPlayerPosition == _tunnelIntroPoint)
		{
			UNLISTEN_TO(PlayerMovedEvent);
			GameAPI::Instance()->removeArrowPointer();
			GameAPI::Instance()->setPlayerTargetPointerEnabled(false);
		}
	}
	
	EVENT_LISTENER(DialogShowedEvent)
	{
		Dialog * pDialog = (reinterpret_cast<DialogShowedEvent *>(from->sender))->pDialog;
		if(pDialog->getDialogID() == kQuestDialogID)
		{
			for(unsigned int i = 0; i < _subquests.size(); ++i)
			{
				if(!_subquests[i]->isCompleted() && !_subquests[i]->isStarted()) // quest is not started
				{
					bool bAnySubquestIsInProgress = false;
					for(unsigned int i = 0; i < _subquests.size(); ++i)
					{
						if(_subquests[i]->isStarted())
						{
							bAnySubquestIsInProgress = true;
							break;
						}
					}

					// if any subquest is in progress
					// then current quest's start button is disabled
					if(bAnySubquestIsInProgress)
					{
						break;
					}
					// if there is not any subquest in progress
					// check if current quest should be next to start
					else
					{
						int iNextSubquestToStart;
						for(unsigned int i = 0; i < _subquests.size(); ++i)
						{
							if(!_subquests[i]->isCompleted())
							{
								iNextSubquestToStart = i;
								break;
							}
						}

						// add an arrow pointer to the corresponding subquest start button
						ButtonID startSubquestButtonID;
						switch(iNextSubquestToStart)
						{
						case 0: // TrapAvoidTutorial
							startSubquestButtonID = kStartSubquest1ButtonID;
							break;
						case 1: // FindDoorTutorial
							UNLISTEN_TO(DialogShowedEvent);
							startSubquestButtonID = kStartSubquest2ButtonID;
							break;
						}

						Button * pStartSubquestButton = pDialog->getButtonByID(startSubquestButtonID);
						if(pStartSubquestButton != nullptr)
						{
							GameAPI::Instance()->pointArrowAtObject(pStartSubquestButton, kArrowPointerDirectionLeft);
						}

						Button * pCloseQuestDialogButton = pDialog->getButtonByID(kCloseQuestDialogID);
						pCloseQuestDialogButton->setEnabled(false);
						break;
					}
				}
			}
		}
	}

protected:
	//-----------------------------------EscapeTutorial---------------------------------//
	ConversationDialogDescription _princessDialogDescription;

	CCPoint _alertPoint, _tunnelIntroPoint;
	
	void addArrowToQuestButton()
	{
		vector<QuestButton*> questButtons = QuestBar::Instance()->getItems<QuestButton>();
		if(!questButtons.empty())
		{
			GameAPI::Instance()->pointArrowAtObject(questButtons[0], kArrowPointerDirectionLeft);
		}
	}
};

#endif //ESCAPETUTORIAL_H