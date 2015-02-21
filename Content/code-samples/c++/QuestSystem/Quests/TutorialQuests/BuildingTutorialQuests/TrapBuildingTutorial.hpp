#ifndef TRAPBUILDINGTUTORIAL_H
#define TRAPBUILDINGTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/GameObjects/Buildings/BuildingPlacement.h"
#include "Gameplay/GameObjects/SpawnObject.h"
#include "Gameplay/GameObjects/Monsters/MonsterFactory.h"

class TrapBuildingTutorial : public Quest
{
    THISIS(TrapBuildingTutorial);
    
    list<Widget*> preDisabledTools;
    BuildingPlacement* mProxyPlacement;
    CCPoint targetPos;
    SpawnObject* spawner;
    bool isMonsterFactoryPreEnabled;
    enum { kTileCount = 9 };
    
    IntPoint tilesToBuild[kTileCount];
    
    Slot<void(BuildingPlacement*,Button*)> slot_onBuildingPlacedSuccesfully;
    Slot<void(BuildingPlacement*,Button*)> slot_onBuildingPlacedAwry;
    Slot<void(void*)> slot_onBuildingExcavationStarted;
    Slot<void(BuildingExcavation*)> slot_onBuildingExcavationCompleted;
    
    Slot<void(Button*)> slot_onWorkShopButtonClicked;
    Slot<void(BuildingPlacement*)> slot_onBuildingPlacementStarted;
    
    Slot<void (Button*)> slot_onWorkShopOkBtnClicked;
public:
	TrapBuildingTutorial():isMonsterFactoryPreEnabled(false)
	{
        targetPos = ccp(7,4);
        
        _princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Princesse";

	}
    
	virtual ~TrapBuildingTutorial()
	{
	}
    
    //------------------------------Declarative Description-----------------------------//
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
        
		questDescription.sTitle = "Trap Building tutorial";
		questDescription.sRewardItemSummary.push_back("moral satisfaction");
		questDescription.sSummary = "Select the mouse trap \n and place it. \n";
        
		return questDescription;
	}
    
	//--------------------------Quest Logic--------------------------//
	virtual QuestID getQuestID()
	{
		return kTrapBuildingTutorialID;
	}
    
	virtual bool isSkippable()
	{
		return false;
	}
    
	//-------------------------Event Handlers------------------------//
	virtual void onSetStarted()
	{
		/* set up */
        //GameAPI::Instance()->setTileGID(2, kTileGIDCaveTop, targetPos);
        isMonsterFactoryPreEnabled = MonsterFactory::Instance()->getIsEnabled();
        MonsterFactory::Instance()->setEnabled(false);
        
        if ( GameAPI::Instance()->getPlayersGold()-30 <= 0 )
        {
            GameAPI::Instance()->addPlayersGold( -(GameAPI::Instance()->getPlayersGold()-30) );
        }
        
        // test
        mProxyPlacement = BuildingPlacementUtils::Instance()->create("traps/mousetrap_lvl1");
        BuildingPlacementUtils::Instance()->addToMap(mProxyPlacement, nullptr, targetPos);
        BuildingPlacementUtils::Instance()->createBoundingBox(mProxyPlacement);
        BuildingPlacementUtils::Instance()->removeFromMap(mProxyPlacement);
        
        GameAPI::Instance()->focusCameraOnFloorTile( targetPos, 0.7f);
        
        _camerafocusedTimer = new Timer();
		_camerafocusedTimer->initWith(0.7f);
		connect(_camerafocusedTimer->eventTimeOut, this, &TrapBuildingTutorial::onFocusedOnRoomPlace);
		_camerafocusedTimer->start();
	}
    
    EVENT_LISTENER(CharacterDiedEvent)
	{
		CharacterDiedEvent * pCharacterDiedEvent = reinterpret_cast<CharacterDiedEvent *>(from->sender);
        
		//if(pCharacterDiedEvent->character->getName() == _sName)
		{
			UNLISTEN_TO(CharacterDiedEvent);
            //spawner->destroy();
            //spawner->release();
            
            _princessDialogDescription.sCharacterLine = "You've done it!";
            GameAPI::Instance()->showConversationDialog(_princessDialogDescription);
            
            Widget * toolBar = GameAPI::Instance()->getWidgetByID(kToolBarWidgetID);
            toolBar->setEnabled(true);
            list<Widget*> tools = *toolBar->getChildrenWidgets();
            for ( list<Widget*>::iterator it = preDisabledTools.begin(); it != preDisabledTools.end(); it++ )
            {
                (*it)->setEnabled(false);
            }
            Button* trapBtn = GameAPI::Instance()->getButtonByID(kTrapButtonID);
            trapBtn->setEnabled(true, "");
			setCompleted(); // @@@
		}
	}
    
    void onBuildingExcavationCompleted(BuildingExcavation* pE)
    {
        //_princessDialogDescription.sCharacterLine = "And here goes the monster!";
		//GameAPI::Instance()->showConversationDialog(_princessDialogDescription);
        
        MonsterFactory::Instance()->setEnabled(true);
        MonsterFactory::Instance()->spawnMonster(IntPoint(targetPos) + IntPoint(2, 0));
                
        
        GameObject* worker = GameAPI::Instance()->getObjectByName("goblin");
        if (worker)
        {
            GameTask* goAway = new GameTask;
            goAway->setTarget(ccp(targetPos.x-3, targetPos.y));
            goAway->setTimeLimit(0);
            worker->setTask(GameTaskPtr(goAway));
        }
        
        LISTEN_TO(CharacterDiedEvent);
    }
    
    void onBuildingExcavationStarted(void*)
    {
        BuildingPlacementUtils::Instance()->destroy(mProxyPlacement);
        GameAPI::Instance()->removeArrowPointer();
    }
    
    void onBuildingPlacedSuccesfully(BuildingPlacement* pBuilding, Button* btn)
    {
        GameAPI::Instance()->pointArrowAtObject(btn, kArrowPointerDirectionUp);
    }
    
    void onBuildingPlacedAwry(BuildingPlacement* pBuilding, Button* btn)
    {
        GameAPI::Instance()->removeArrowPointer();
    }
    
    void onBuildingPlacementStarted(BuildingPlacement* pBuilding)
    {
        slot_onBuildingPlacementStarted.disconnect();
        //_princessDialogDescription.sCharacterLine = "Touch on the room view\n and drag it to some good place!\n So the worker will be able \n to begin his job \n";
		//GameAPI::Instance()->showConversationDialog(_princessDialogDescription);
        
        BuildingPlacement* pPlacement = pBuilding;
        if ( pPlacement )
        {
            BuildingPlacementUtils::Instance()->select(pPlacement);
        }
        
        slot_onBuildingPlacedSuccesfully = connect(BuildingPlacementUtils::Instance()->onPlacementSuccess, this, &TrapBuildingTutorial::onBuildingPlacedSuccesfully);
        slot_onBuildingPlacedAwry = connect(BuildingPlacementUtils::Instance()->onPlacementFail, this, &TrapBuildingTutorial::onBuildingPlacedAwry);
        slot_onBuildingExcavationStarted = connect(BuildingPlacementUtils::Instance()->onExcavationStarted, this, &TrapBuildingTutorial::onBuildingExcavationStarted);
        slot_onBuildingExcavationCompleted = connect(BuildingPlacementUtils::Instance()->onExcavationCompleted, this, &TrapBuildingTutorial::onBuildingExcavationCompleted);
    }
    
    void onWorkShopOkBtnClicked( Button * btn )
    {
        GameAPI::Instance()->removeArrowPointer();
        
        BuildingPlacementUtils::Instance()->removeBoundingBox(mProxyPlacement);
        
        Button* trapBtn = GameAPI::Instance()->getButtonByID(kTrapButtonID);
        trapBtn->setEnabled(false, "no more traps during quest");
        //mProxyPlacement = BuildingPlacementUtils::Instance()->create("armory_lvl1");
        //BuildingPlacementUtils::Instance()->addToMap(mProxyPlacement, nullptr, targetPos);
        
        slot_onBuildingPlacementStarted = connect(BuildingPlacementUtils::Instance()->onPlacementStart, this, &TrapBuildingTutorial::onBuildingPlacementStarted);
    }
    
    void onBuildingSelected( BuildingData* data )
    {
        if ( !( data->buildingType.find("traps/mousetrap_lvl1") != -1) )
        {
            return;
        }
        GameAPI::Instance()->removeArrowPointer();
        WorkshopsDialog * targetDlg = reinterpret_cast<WorkshopsDialog*>( GameAPI::Instance()->getDialogByID(kTrapsDialogID) );
        Button * okBtn = targetDlg->getButtonByID(kTrapsOkButtonID);
        Button * closeBtn = targetDlg->getButtonByID(kTrapsCloseButtonID);
        
        okBtn->setEnabled(true);
        //closeBtn->setEnabled(true);
        GameAPI::Instance()->pointArrowAtObject(okBtn, kArrowPointerDirectionRight);
        connect(okBtn->eventClicked, this, &TrapBuildingTutorial::onWorkShopOkBtnClicked);
        
        // plan b
        slot_onBuildingPlacementStarted = connect(BuildingPlacementUtils::Instance()->onPlacementStart, this, &TrapBuildingTutorial::onBuildingPlacementStarted);
    }
    
    void onWorkShopButtonClicked( Button * btn )
    {
        slot_onWorkShopButtonClicked.disconnect();
        GameAPI::Instance()->removeArrowPointer();
        WorkshopsDialog * targetDlg = reinterpret_cast<WorkshopsDialog*>( GameAPI::Instance()->getDialogByID(kTrapsDialogID) );
        Button * okBtn = targetDlg->getButtonByID(kTrapsOkButtonID);
        okBtn->setEnabled(false);
        Button * closeBtn = targetDlg->getButtonByID(kTrapsCloseButtonID);
        closeBtn->setEnabled(false);
        
        CCScrollViewExtended *pScrollView = targetDlg->getScrollview();
        CCArray* items = pScrollView->getItems();//getContainer()->getChildren();
        for (int i = 0; i < items->count(); ++i) {
            WorkshopsDialog::BuildingViewItem* item = (WorkshopsDialog::BuildingViewItem*)items->objectAtIndex(i);//static_cast<WorkshopsDialog::BuildingViewItem*>(*it);
            if ( !(item->getBuildingData()->buildingType.find("traps/mousetrap_lvl1") != -1) )
            {
                item->setEnabled(false);
            }
            else
            {
                item->getParent()->reorderChild(item, 100);
                GameAPI::Instance()->pointArrowAtObject(item, kArrowPointerDirectionLeft);
                connect(targetDlg->eventBuildingSelected, this, &TrapBuildingTutorial::onBuildingSelected);
            }
        }
    }
    
    void onFirstConversationDialogClosed(bool bAccepted)
	{
		setExplicit();
	}
    
    void onThirdDialogClosed(bool bAccepted)
    {
        Button * targetBtn = GameAPI::Instance()->getButtonByID(kTrapButtonID);
        Button * menuBtn = GameAPI::Instance()->getButtonByID(kMenuButtonID);
        Widget * toolBar = GameAPI::Instance()->getWidgetByID(kToolBarWidgetID);
        list<Widget*> tools = *toolBar->getChildrenWidgets();
        for ( list<Widget*>::iterator it = tools.begin(); it != tools.end(); it++ )
        {
            if ( !(*it)->isEnabled() )
            {
                preDisabledTools.push_back((*it));
            }
        }
        toolBar->setEnabled(false);
        targetBtn->setEnabled(true);
        menuBtn->setEnabled(true);
        
        GameAPI::Instance()->pointArrowAtObject(targetBtn, kArrowPointerDirectionRight);
        slot_onWorkShopButtonClicked = connect(targetBtn->eventClicked, this, &TrapBuildingTutorial::onWorkShopButtonClicked);
		//GameAPI::Instance()->pointArrowAtObject(pBeetle->getSprite(), ArrowPointerDirection::kArrowPointerDirectionDown);
		//connect(pBeetle->eventClicked, this, &BattleTutorial::onBeetleClicked);
        
    }
    
    void onFocusedOnRoomPlace(float dt)
    {
        _camerafocusedTimer->release();
        _princessDialogDescription.sCharacterLine = "Here is the place\n for your trap!";
		GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind( &TrapBuildingTutorial::onThirdDialogClosed, this, placeholders::_1 ));
        
    }
    
    Timer * _camerafocusedTimer;
    
    EVENT_LISTENER(QuestCompletionInfo)
    {
        QuestCompletionInfo * pQuestCompletionInfo = reinterpret_cast<QuestCompletionInfo *>(from->sender);
        
        if(pQuestCompletionInfo->questID == kRoomBuildingTutorialID)
        {
			_princessDialogDescription.sCharacterLine = "It's dangerous place!\nWe must make a trap!";
			GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind(&TrapBuildingTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
        }
    }
    
    EVENT_LISTENER(MapLoadedEvent)
    {
        
        MapLoadedEvent * pMapLoadedEvent = reinterpret_cast<MapLoadedEvent *>(from->sender);
        
        const char* scMapName = pMapLoadedEvent->sMapName.c_str();
        if(pMapLoadedEvent->sMapName.find("main") != -1)
        {
            //setExplicit(); // test
            UNLISTEN_TO(MapLoadedEvent);
            
            if ( isDebugging() )
            {
                _princessDialogDescription.sCharacterLine = "It's dangerous place!\nWe must make a trap!";
                GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind(&TrapBuildingTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
            }
        }
    }
    /*
    virtual bool debug()
    {
        LISTEN_TO(MapLoadedEvent);
        return true;
    }
   */
	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{
        slot_onBuildingPlacedSuccesfully.disconnect();
        slot_onBuildingPlacedAwry.disconnect();
        slot_onBuildingExcavationStarted.disconnect();
        slot_onBuildingExcavationCompleted.disconnect();
        slot_onWorkShopButtonClicked.disconnect();
        slot_onBuildingPlacementStarted.disconnect();
        slot_onWorkShopOkBtnClicked.disconnect();
        MonsterFactory::Instance()->setEnabled(isMonsterFactoryPreEnabled);
		//throw "TrapBuildingTutorial::cleanup() is empty!";
	}

protected:
    ConversationDialogDescription _princessDialogDescription;
    
	virtual void onSetPassive()
	{
        
        LISTEN_TO(QuestCompletionInfo);
        MonsterFactory::Instance()->setEnabled(false);
	}
};

#endif //TRAPBUILDINGTUTORIAL_H