#ifndef ACTIONTUTORIAL_H
#define ACTIONTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Graphics/GUI/Bars/QuestBar.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/BattleTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/InventoryTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/MovementTutorial.hpp"
#include "Gameplay/QuestSystem/Quests/TutorialQuests/ActionTutorialQuests/ObjectOnMapInteractionTutorial.hpp"
#include "Utils/Text/TextUtils.h"

#define NUMBER_OF_SECONDS_AFTER_FAIRY_APPEARS 2
#define NUMBER_OF_SECONDS_AFTER_FAIRY_STARTS_TALKING 2

class ActionTutorial : public Quest
{
THISIS(ActionTutorial);

public:
	//----------------------------------ActionTutorial----------------------------------//
	ActionTutorial() :
		_pFairyAppearedTimer(nullptr),
		_pFairyStartsTalkingTimer(nullptr)
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
		
		LISTEN_TO(QuestCompletionInfo);
		addSubquest(new MovementTutorial());
		addSubquest(new ObjectOnMapInteractionTutorial());
		addSubquest(new InventoryTutorial());
		addSubquest(new BattleTutorial());
	}

	virtual ~ActionTutorial()
	{
	}
	
	//------------------------------Declarative Description-----------------------------//
	virtual QuestButtonDescription getQuestButtonDescription()
	{
		QuestButtonDescription questButtonDescription;

		questButtonDescription.sIconImagePath = "assets/interface/bars/quest-bar/quest-icon1.png";
		questButtonDescription.bUseProgressLabel = true;
		questButtonDescription.iNumberOfSteps = 4;

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
		
		_L("quest.actionTutorial.rewardItemSummary.1");
		_L("quest.actionTutorial.rewardItemSummary.2");
		_L("quest.actionTutorial.rewardItemSummary.3");
		_L("quest.actionTutorial.summary");
		_L("quest.actionTutorial.title");

		return questDescription;
	}
	
	//--------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return kActionTutorialID;
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
		UNLISTEN_TO(MapLoadedEvent);
		UNLISTEN_TO(DialogShowedEvent);
		UNLISTEN_TO(QuestCompletionInfo);

		if(_pFairyAppearedTimer != nullptr)
		{
			delete _pFairyAppearedTimer;
		}

		if(_pFairyStartsTalkingTimer != nullptr)
		{
			delete _pFairyStartsTalkingTimer;
		}
	}
	
	//-------------------------------Game Event Listeners-------------------------------//
    EVENT_LISTENER(MapLoadedEvent)
	{
		MapLoadedEvent * pMapLoadedEvent = reinterpret_cast<MapLoadedEvent *>(from->sender);

		if(pMapLoadedEvent->sMapName == "map-tutorial")
		{
            UNLISTEN_TO(MapLoadedEvent);
			GameAPI::Instance()->setPlayerTargetResponseToPointOnly(CCPoint(-345, -456));
			_pHero = GameAPI::Instance()->getObjectByName("Hero");
			_pFairy = GameAPI::Instance()->getObjectByName("fairy");
			_pFairy->getSprite()->setVisible(false);

			_pFairyAppearedTimer = new Timer();
			_pFairyAppearedTimer->initWith(NUMBER_OF_SECONDS_AFTER_FAIRY_APPEARS);
			connect(_pFairyAppearedTimer->eventTimeOut, this, &ActionTutorial::onFairyAppearedTimeOut);
			_pFairyAppearedTimer->start();

			GameAPI::Instance()->getButtonByID(kDigButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kUndigButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kWorkshopButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kDecorationButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kRefinementButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kTrapButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kAchievementsButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kCollectionsButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kInventoryButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kFriendsButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kWarehouseButtonID)->setEnabled(false);
			GameAPI::Instance()->getButtonByID(kMenuButtonID)->setEnabled(true);
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
						case 0: // MovementTutorial
							startSubquestButtonID = kStartSubquest1ButtonID;
							break;
						case 1: // ObjectOnMapInteractionTutorial
							startSubquestButtonID = kStartSubquest2ButtonID;
							break;
						case 2: // InventoryTutorial
							startSubquestButtonID = kStartSubquest3ButtonID;
							break;
						case 3: // BattleTutorial
							UNLISTEN_TO(DialogShowedEvent);
							startSubquestButtonID = kStartSubquest4ButtonID;
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

	EVENT_LISTENER(QuestCompletionInfo)
	{
		QuestCompletionInfo * pQuestCompletionInfo = reinterpret_cast<QuestCompletionInfo *>(from->sender);

		if(pQuestCompletionInfo->questID == kMovementTutorialID)
		{
			addArrowToQuestButton();
		}
		else if(pQuestCompletionInfo->questID == kObjectOnMapInteractionTutorialID)
		{
			addArrowToQuestButton();
		}
		else if(pQuestCompletionInfo->questID == kInventoryTutorialID)
		{
			addArrowToQuestButton();
		}
		else if(pQuestCompletionInfo->questID == kBattleTutorialID)
		{
            UNLISTEN_TO(QuestCompletionInfo);
		}
	}

protected:
	//--------------------------------------Quest---------------------------------------//
	virtual void onSetPassive()
	{
		LISTEN_TO(MapLoadedEvent);
	}

	//----------------------------------ActionTutorial----------------------------------//
	GameObject * _pHero;
	GameObject * _pFairy;
	ConversationDialogDescription _princessDialogDescription;

	Timer * _pFairyAppearedTimer;
	void onFairyAppearedTimeOut(float fUnused)
	{
		_pFairy->getSprite()->setVisible(true);
		_pFairy->setAnimationActive(kAnimationStatAppear, _pHero);

		_pFairyStartsTalkingTimer = new Timer();
		_pFairyStartsTalkingTimer->initWith(NUMBER_OF_SECONDS_AFTER_FAIRY_STARTS_TALKING);
		connect(_pFairyStartsTalkingTimer->eventTimeOut, this, &ActionTutorial::onFairyStartsTalkingTimeOut);
		_pFairyStartsTalkingTimer->start();
	}

	Timer * _pFairyStartsTalkingTimer;
	void onFairyStartsTalkingTimeOut(float fUnused)
	{
		_princessDialogDescription.sCharacterLine = "Hello, stranger!\n \
			I am the Fairy.\n \
			\n \
			I will teach you,\n \
			how to behave\n \
			in this world!\n \
			\n \
			Check your first quest!";

		_L("quest.actionTutorial.line.firstDialog");

		//string sTemp = TextDataProvider::Instance()->getText("quest.actionTutorial.line.firstDialog");

		GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
			bind(&ActionTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
	}

	void onFirstConversationDialogClosed(bool bAccepted)
	{
		setExplicit();
		addArrowToQuestButton();
		LISTEN_TO(DialogShowedEvent);
	}

	void addArrowToQuestButton()
	{
		vector<QuestButton*> questButtons = QuestBar::Instance()->getItems<QuestButton>();
		if(!questButtons.empty())
		{
			GameAPI::Instance()->pointArrowAtObject(questButtons[0], kArrowPointerDirectionLeft);
		}
	}
};

#endif //ACTIONTUTORIAL_H
