#ifndef ROOMBUILDINGTUTORIAL_H
#define ROOMBUILDINGTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/GameObjects/Buildings/BuildingPlacement.h"
#include "Graphics/GUI/Dialogs/WorkshopsDialog.h"
#include "Gameplay/GameObjects/Monsters/MonsterFactory.h"

class RoomBuildingTutorial : public Quest
{
    THISIS(RoomBuildingTutorial);
    
    list<Widget*> preDisabledTools;
    BuildingPlacement* mProxyPlacement;
    CCPoint targetPos;
    enum { kTileCount = 9 };
    
    IntPoint tilesToBuild[kTileCount];

public:
	RoomBuildingTutorial():mProxyPlacement(nullptr)
	{
        targetPos = ccp(2,5);
        _princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Princesse";
        int i = 0;
        tilesToBuild[i] = IntPoint(2,4); i++;
        tilesToBuild[i] = IntPoint(2,3); i++; // left
        tilesToBuild[i] = IntPoint(2,5); i++; // right
        tilesToBuild[i] = IntPoint(1,4); i++;
        tilesToBuild[i] = IntPoint(1,3); i++; // left
        tilesToBuild[i] = IntPoint(1,5); i++; // right
        tilesToBuild[i] = IntPoint(0,4); i++;
        tilesToBuild[i] = IntPoint(0,3); i++; // left
        tilesToBuild[i] = IntPoint(0,5); i++; // left
        
        targetPos = ccp( tilesToBuild[2].x, tilesToBuild[2].y );;
	}

	virtual ~RoomBuildingTutorial()
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

		questDescription.sTitle = "Room Building tutorial";
		questDescription.sRewardItemSummary.push_back("moral satisfaction");
		questDescription.sSummary = "Select the armory room \n and place it somewhere. \n";
        
		return questDescription;
	}
    
	//--------------------------Quest Logic--------------------------//
	virtual QuestID getQuestID()
	{
		return kRoomBuildingTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	//-------------------------Event Handlers------------------------//
    void onFinalDialogClosed(bool bAccepted)
    {
         setCompleted();
    }
    void onBuildingExcavationCompleted(BuildingExcavation* pE)
    {
        slot_onBuildingExcavationCompleted.disconnect();
        Widget * toolBar = GameAPI::Instance()->getWidgetByID(kToolBarWidgetID);
        toolBar->setEnabled(true);
        list<Widget*> tools = *toolBar->getChildrenWidgets();
        for ( list<Widget*>::iterator it = preDisabledTools.begin(); it != preDisabledTools.end(); it++ )
        {
            (*it)->setEnabled(false);
        }
        
        _princessDialogDescription.sCharacterLine = "Whoooa!! \n You are so clever boy!";
		GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind(&RoomBuildingTutorial::onFinalDialogClosed, this, placeholders::_1));
    }
    
    void onBuildingExcavationStarted(void*)
    {
        slot_onBuildingPlacedSuccesfully.disconnect();
        slot_onBuildingPlacedAwry.disconnect();
        slot_onBuildingExcavationStarted.disconnect();
        slot_onBuildingPlacementStarted.disconnect();
        BuildingPlacementUtils::Instance()->destroy(mProxyPlacement);
        mProxyPlacement = nullptr;
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
        _princessDialogDescription.sCharacterLine = "Touch on the room view\n and drag it to some good place!\n So the worker will be able \n to begin his job \n";
		GameAPI::Instance()->showConversationDialog(_princessDialogDescription);
        
        BuildingPlacement* pPlacement = pBuilding;
        if ( pPlacement )
        {
            BuildingPlacementUtils::Instance()->select(pPlacement);
        }
        
        slot_onBuildingPlacedSuccesfully = connect(BuildingPlacementUtils::Instance()->onPlacementSuccess, this, &RoomBuildingTutorial::onBuildingPlacedSuccesfully);
        slot_onBuildingPlacedAwry = connect(BuildingPlacementUtils::Instance()->onPlacementFail, this, &RoomBuildingTutorial::onBuildingPlacedAwry);
        slot_onBuildingExcavationStarted = connect(BuildingPlacementUtils::Instance()->onExcavationStarted, this, &RoomBuildingTutorial::onBuildingExcavationStarted);
        slot_onBuildingExcavationCompleted = connect(BuildingPlacementUtils::Instance()->onExcavationCompleted, this, &RoomBuildingTutorial::onBuildingExcavationCompleted);
    }
    Slot<void(BuildingPlacement*,Button*)> slot_onBuildingPlacedSuccesfully;
    Slot<void(BuildingPlacement*,Button*)> slot_onBuildingPlacedAwry;
    Slot<void(void*)> slot_onBuildingExcavationStarted;
    Slot<void(BuildingExcavation*)> slot_onBuildingExcavationCompleted;
    
    Slot<void(Button*)> slot_onWorkShopButtonClicked;
    Slot<void(BuildingPlacement*)> slot_onBuildingPlacementStarted;
    
    Slot<void (Button*)> slot_onWorkShopOkBtnClicked;
    void onWorkShopOkBtnClicked( Button * btn )
    {
        slot_onWorkShopOkBtnClicked.disconnect();
        GameAPI::Instance()->removeArrowPointer();
        //BuildingPlacementUtils::Instance()->removeFromMap(mProxyPlacement);
        BuildingPlacementUtils::Instance()->removeBoundingBox(mProxyPlacement);
        
        //mProxyPlacement = BuildingPlacementUtils::Instance()->create("armory_lvl1");
        //BuildingPlacementUtils::Instance()->addToMap(mProxyPlacement, nullptr, targetPos);
        
        slot_onBuildingPlacementStarted = connect(BuildingPlacementUtils::Instance()->onPlacementStart, this, &RoomBuildingTutorial::onBuildingPlacementStarted);
    }
    
    void onBuildingSelected( BuildingData* data )
    {
        if ( !( data->buildingType.find("armory_lvl1") != -1) )
        {
            return;
        }
        GameAPI::Instance()->removeArrowPointer();
        WorkshopsDialog * targetDlg = reinterpret_cast<WorkshopsDialog*>( GameAPI::Instance()->getDialogByID(kWorkshopDialogID) );
        Button * okBtn = targetDlg->getButtonByID(kWorkShopOkButtonID);
        Button * closeBtn = targetDlg->getButtonByID(kWorkShopCloseButtonID);
        
        okBtn->setEnabled(true);
        //closeBtn->setEnabled(true);
        GameAPI::Instance()->pointArrowAtObject(okBtn, kArrowPointerDirectionRight);
        slot_onWorkShopOkBtnClicked = connect(okBtn->eventClicked, this, &RoomBuildingTutorial::onWorkShopOkBtnClicked);
        
        // plan b
        slot_onBuildingPlacementStarted = connect(BuildingPlacementUtils::Instance()->onPlacementStart, this, &RoomBuildingTutorial::onBuildingPlacementStarted);
    }
    
    void onWorkShopButtonClicked( Button * btn )
    {
        slot_onWorkShopButtonClicked.disconnect();
        GameAPI::Instance()->removeArrowPointer();
        WorkshopsDialog * targetDlg = reinterpret_cast<WorkshopsDialog*>( GameAPI::Instance()->getDialogByID(kWorkshopDialogID) );
        Button * okBtn = targetDlg->getButtonByID(kWorkShopOkButtonID);
        okBtn->setEnabled(false);
        Button * closeBtn = targetDlg->getButtonByID(kWorkShopCloseButtonID);
        closeBtn->setEnabled(false);
        
        CCScrollViewExtended *pScrollView = targetDlg->getScrollview();
        CCArray* items = pScrollView->getItems();
        
        for (int i = 0; i < items->count(); ++i) {
            WorkshopsDialog::BuildingViewItem* item = (WorkshopsDialog::BuildingViewItem*)items->objectAtIndex(i);//static_cast<WorkshopsDialog::BuildingViewItem*>(*it);
            
            if ( !(item->getBuildingData()->buildingType.find("armory_lvl1") != -1) )
            {
                item->setEnabled(false);
            }
            else
            {
                item->getParent()->reorderChild(item, 100);
                GameAPI::Instance()->pointArrowAtObject(item, kArrowPointerDirectionLeft);
                connect(targetDlg->eventBuildingSelected, this, &RoomBuildingTutorial::onBuildingSelected);
            }
        }
    }

	//-------------------------Event Handlers------------------------//
	virtual void onSetStarted()
	{
        MonsterFactory::Instance()->setEnabled(false);
        /* set up */
        for ( int i = 0; i < kTileCount; i++ )
        {
            GameAPI::Instance()->digTileImmediately(tilesToBuild[i]);
        }
        
        if ( GameAPI::Instance()->getPlayersGold()-100 <= 0 )
        {
            GameAPI::Instance()->addPlayersGold( -(GameAPI::Instance()->getPlayersGold()-100) );
        }
                
        // test
        mProxyPlacement = BuildingPlacementUtils::Instance()->create("armory_lvl1");
        BuildingPlacementUtils::Instance()->addToMap(mProxyPlacement, nullptr, targetPos);
        BuildingPlacementUtils::Instance()->createBoundingBox(mProxyPlacement);
        BuildingPlacementUtils::Instance()->removeFromMap(mProxyPlacement);
        
        GameAPI::Instance()->focusCameraOnFloorTile( tilesToBuild[2], 0.7f);
        
        _camerafocusedTimer = new Timer();
		_camerafocusedTimer->initWith(0.7f);
		connect(_camerafocusedTimer->eventTimeOut, this, &RoomBuildingTutorial::onFocusedOnRoomPlace);
		_camerafocusedTimer->start();
	}
    
    void onFirstConversationDialogClosed(bool bAccepted)
	{
		setExplicit();
	}
    
    void onThirdDialogClosed(bool bAccepted)
    {
        Button * targetBtn = GameAPI::Instance()->getButtonByID(kWorkshopButtonID);
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
        slot_onWorkShopButtonClicked = connect(targetBtn->eventClicked, this, &RoomBuildingTutorial::onWorkShopButtonClicked);
		//GameAPI::Instance()->pointArrowAtObject(pBeetle->getSprite(), ArrowPointerDirection::kArrowPointerDirectionDown);
		//connect(pBeetle->eventClicked, this, &BattleTutorial::onBeetleClicked);

    }
    
    void onFocusedOnRoomPlace(float dt)
    {
        _camerafocusedTimer->release();
        _princessDialogDescription.sCharacterLine = "Do you see\nthe highlighted area?\nIt's a perfect place\n for your new room!";
		GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind( &RoomBuildingTutorial::onThirdDialogClosed, this, placeholders::_1 ));
        
    }
    
    Timer * _camerafocusedTimer;

    EVENT_LISTENER(QuestCompletionInfo)
    {
        QuestCompletionInfo * pQuestCompletionInfo = reinterpret_cast<QuestCompletionInfo *>(from->sender);
        
        if(pQuestCompletionInfo->questID == kDiggingTutorialID)
        {
			UNLISTEN_TO(QuestCompletionInfo);
			_princessDialogDescription.sCharacterLine = "Now!\nIt is time to build a room";
			GameAPI::Instance()->showConversationDialog(_princessDialogDescription, bind(&RoomBuildingTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
        }
    }
    
    EVENT_LISTENER(MapLoadedEvent)
    {
        MapLoadedEvent * pMapLoadedEvent = reinterpret_cast<MapLoadedEvent *>(from->sender);
        const char* scMapName = pMapLoadedEvent->sMapName.c_str();
        if(pMapLoadedEvent->sMapName.find("main") != -1)
        {
            setExplicit(); // test
            UNLISTEN_TO(MapLoadedEvent);
            
        }
    }

	virtual void saveState() {}

	virtual void restoreState() {}
    
    
    virtual bool debug()
    {
        LISTEN_TO(MapLoadedEvent);
        return true;
    }

	virtual void cleanup()
	{
        slot_onWorkShopButtonClicked.disconnect();
        slot_onWorkShopOkBtnClicked.disconnect();
        
        slot_onBuildingPlacedSuccesfully.disconnect();
        slot_onBuildingPlacedAwry.disconnect();
        slot_onBuildingExcavationStarted.disconnect();
        slot_onBuildingPlacementStarted.disconnect();
        if ( mProxyPlacement )
            BuildingPlacementUtils::Instance()->destroy(mProxyPlacement);
        GameAPI::Instance()->removeArrowPointer();
        
        slot_onBuildingExcavationCompleted.disconnect();
        
        Button * targetBtn = GameAPI::Instance()->getButtonByID(kWorkshopButtonID);
        Button * menuBtn = GameAPI::Instance()->getButtonByID(kMenuButtonID);
        Widget * toolBar = GameAPI::Instance()->getWidgetByID(kToolBarWidgetID);
        toolBar->setEnabled(true);
        list<Widget*> tools = *toolBar->getChildrenWidgets();
        for ( list<Widget*>::iterator it = preDisabledTools.begin(); it != preDisabledTools.end(); it++ )
        {
            (*it)->setEnabled(false);
        }
        targetBtn->setEnabled(false);
        menuBtn->setEnabled(false);
		//throw "RoomBuildingTutorial::cleanup() is empty!";
	}


protected:
    ConversationDialogDescription _princessDialogDescription;

	virtual void onSetPassive()
	{
        MonsterFactory::Instance()->setEnabled(false);
        LISTEN_TO(QuestCompletionInfo);

	}
};

#endif //ROOMBUILDINGTUTORIAL_H