#ifndef DIGGINGTUTORIAL_H
#define DIGGINGTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Graphics/LightSource.h"
#include "Gameplay/Events/TileChangedEvent.h"
#include "Gameplay/GameObjects/Monsters/MonsterFactory.h"

class DiggingTutorial : public Quest
{
public:
    THISIS(DiggingTutorial);
    
    enum { kTileCount = 9 };
    
    IntPoint tilesToDig[kTileCount];
    vector<IntPoint> selectedTiles;
    
    list<Widget*> preDisabledTools;
    
    ConversationDialogDescription mMainDialog;
	DiggingTutorial()
	{
        mTilesDone = 0;
        mTilesClicked = 0;
        int i = 0;
        tilesToDig[i] = IntPoint(2,4); i++;
        tilesToDig[i] = IntPoint(2,3); i++; // left
        tilesToDig[i] = IntPoint(2,5); i++; // right
        tilesToDig[i] = IntPoint(1,4); i++;
        tilesToDig[i] = IntPoint(1,3); i++; // left
        tilesToDig[i] = IntPoint(1,5); i++; // right
        tilesToDig[i] = IntPoint(0,4); i++;
        tilesToDig[i] = IntPoint(0,3); i++; // left
        tilesToDig[i] = IntPoint(0,5); i++; // left
        /*
        tilesToDig[i] = IntPoint(-1,4); i++;
        tilesToDig[i] = IntPoint(-1,3); i++; // left
        tilesToDig[i] = IntPoint(-1,5); i++; // left
         */
        
        mMainDialog.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		mMainDialog.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		mMainDialog.sCharacterName = "Princesse";
	}

	virtual ~DiggingTutorial()
	{
	}
    
    //------------------------------Declarative Description-----------------------------//
	virtual QuestButtonDescription getQuestButtonDescription()
	{
		QuestButtonDescription questButtonDescription;
        
		questButtonDescription.sIconImagePath = "assets/interface/bars/quest-bar/quest-icon1.png";
		questButtonDescription.bUseProgressLabel = true;
		questButtonDescription.iNumberOfSteps = kTileCount;
        
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
        
		questDescription.sTitle = "Digging tutorial";
		questDescription.sRewardItemSummary.push_back("cookies");
		questDescription.sSummary = "Learn how to dig new places";
        
		return questDescription;
	}

	//--------------------------Quest Logic--------------------------//
	virtual QuestID getQuestID()
	{
		return kDiggingTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	//-------------------------Event Handlers------------------------//
    EVENT_LISTENER(MapLoadedEvent)
    {
        MapLoadedEvent * pMapLoadedEvent = reinterpret_cast<MapLoadedEvent *>(from->sender);
        
        const char* scMapName = pMapLoadedEvent->sMapName.c_str();
        if(pMapLoadedEvent->sMapName.find("main") != -1)
        {
            //LISTEN_TO(UpdateEvent);
            setExplicit();
            UNLISTEN_TO(MapLoadedEvent);
            // 
            
            Button * targetBtn = GameAPI::Instance()->getButtonByID(kDigButtonID);
            targetBtn->setEnabled(false);
            targetBtn = GameAPI::Instance()->getButtonByID(kUndigButtonID);
            targetBtn->setEnabled(false);
        }
    }
    
    EVENT_LISTENER(TileChangedEvent)
    {
        
        if ( mTilesDone >= kTileCount - 1 )
        {
            mTilesDone = 0;
            GameObject* worker = GameAPI::Instance()->getObjectByName("goblin");
            if (worker)
            {
                GameTask* goAway = new GameTask;
				goAway->setTarget(ccp(4, 4));
                goAway->setTimeLimit(0);
				worker->setTask(GameTaskPtr(goAway));
            }
            Widget* toolBar = GameAPI::Instance()->getWidgetByID(kToolBarWidgetID);
            
            GameAPI::Instance()->getWidgetByID(kToolBarWidgetID)->setEnabled(true);

            for ( list<Widget*>::iterator it = preDisabledTools.begin(); it != preDisabledTools.end(); it++ )
            {
                (*it)->setEnabled(false);
            }
            Button * targetBtn = GameAPI::Instance()->getButtonByID(kDigButtonID);
            targetBtn->setEnabled(true);
            targetBtn = GameAPI::Instance()->getButtonByID(kUndigButtonID);
            targetBtn->setEnabled(true);
            setCompleted();
            return;
        }
        
        TileChangedEvent* data = reinterpret_cast<TileChangedEvent*>(from->sender);
        IntPoint tile(data->tile);
        mTilesDone++;
        signalProgress(QuestProgressInfo(getQuestID(), mTilesDone, getQuestButtonDescription().iNumberOfSteps ));
        
        
    }
    
    EVENT_LISTENER(TileClickedEvent)
    {
        
        TileClickedEvent* data = reinterpret_cast<TileClickedEvent*>(from->sender);
        IntPoint tile(data->x, data->y);
        
        if ( mTilesClicked >= kTileCount - 1 )
        {
            GameAPI::Instance()->removeArrowPointer();
            UNLISTEN_TO(TileClickedEvent);
            Dialog* dlg = GameAPI::Instance()->getDialogByID(kBuildConfirmDialogID);
            Button * okBtn = dlg->getButtonByID(kDigOkButton);

            if (okBtn)
            {
                okBtn->setEnabled(true);
                GameAPI::Instance()->pointArrowAtObject(okBtn, kArrowPointerDirectionRight);
            }
            
            LISTEN_TO(TileChangedEvent);
            
            mTilesClicked = 0;
            return;
        }
        
        if ( !isQuestTile(tile) )
        {
            data->handled = true;
            return;
        }
        else
        {
            if ( !isTileSelected(tile) )
            {
                selectedTiles.push_back(tile);
                GameAPI::Instance()->removeArrowPointer();
                mTilesClicked++;
                CCPoint nextTile = ccp(-999,-999);
                //nextTile = nearestFreeTile(tile);
                
                for ( int i = 0; i < kTileCount; i++ )
                {
                    if ( !isTileSelected(tilesToDig[i]) )
                    {
                        nextTile = ccp(tilesToDig[i].x, tilesToDig[i].y);
                        break;
                    }
                }
                
                if ( nextTile.x != -999 && nextTile.y != -999 )
                    GameAPI::Instance()->pointArrowAtFloor( nextTile, kArrowPointerDirectionDown );
                //GameAPI::Instance()->focusCameraOnFloorTile(ccp(tilesToDig[mTilesClicked].x, tilesToDig[mTilesClicked].y), 0.2f);
            }
            else
            {
                data->handled = true;
                return;
                ccColor3B prevColor = GameAPI::Instance()->getTileColor(2, tile);
                //prevColor.r -= prevColor.r*0.35;
                //prevColor.g += prevColor.g*0.35;
                //prevColor.b -= prevColor.b*0.35;
                
                //GameAPI::Instance()->setTileColor(2, prevColor, tilesToDig[i]);
                GameAPI::Instance()->setTileColor(prevColor, tile);
            }
        }
        
    }
    
    bool isQuestTile( const IntPoint& tile )
    {
        for ( int i = 0; i < kTileCount; ++i )
        {
            if ( tilesToDig[i] == tile )
            {
                return true;
            }
        }
        return false;
    }
    
    CCPoint nearestFreeTile(const IntPoint& tile)
    {
        CCPoint nextTile = ccp(-999,-999);
        int n = 1;
        int k = 0;
//        for ( int n = 1; n < 6; n++ )
//        {
            for (int i = -1*n; i <= 1*n; i++)
            {
                for (int j = -1*n; j <= 1*n; j++)
                {
                    if ( i == 0 && j == 0 ) continue;
                    IntPoint candidateTile = IntPoint(tile.x+i, tile.y+i);
                    if ( isQuestTile(candidateTile) && !isTileSelected(candidateTile) )
                    {
                        nextTile = ccp(candidateTile.x, candidateTile.y);
                        k = 1;
                        break;
                    }
                    else
                    {
                        k = 0;
                        if ( nextTile.x == -999 && nextTile.y == -999 )
                        {
                            return nextTile;
                        }
                    }
                }
                if (k)
                    break;
            }
//            if (k)
//                break;
//        }
        
        //return nextTile;
        
        if ( nextTile.x == -999 && nextTile.y == -999 )
        {
            int i = 1, j = 1;
            IntPoint nextDomain = IntPoint(tile.x+i, tile.y+j);
            if ( isQuestTile(nextDomain) )
            {
                nextTile = nearestFreeTile(nextDomain);
                if ( nextTile.x != -999 && nextTile.y != -999 )
                {
                    return nextTile;
                }
            }
            i = 1, j = 0;
            nextDomain = IntPoint(tile.x+i, tile.y+j);
            if ( isQuestTile(nextDomain) )
            {
                nextTile = nearestFreeTile(nextDomain);
                if ( nextTile.x != -999 && nextTile.y != -999 )
                {
                    return nextTile;
                }
            }
            
            i = 0, j = 1;
            nextDomain = IntPoint(tile.x+i, tile.y+j);
            if ( isQuestTile(nextDomain) )
            {
                nextTile = nearestFreeTile(nextDomain);
                if ( nextTile.x != -999 && nextTile.y != -999 )
                {
                    return nextTile;
                }
            }
            
            i = -1, j = 0;
            nextDomain = IntPoint(tile.x+i, tile.y+j);
            if ( isQuestTile(nextDomain) )
            {
                nextTile = nearestFreeTile(nextDomain);
                if ( nextTile.x != -999 && nextTile.y != -999 )
                {
                    return nextTile;
                }
            }
            
            i = 0, j = -1;
            nextDomain = IntPoint(tile.x+i, tile.y+j);
            if ( isQuestTile(nextDomain) )
            {
                nextTile = nearestFreeTile(nextDomain);
                if ( nextTile.x != -999 && nextTile.y != -999 )
                {
                    return nextTile;
                }
            }
            
            i = -1, j = -1;
            nextDomain = IntPoint(tile.x+i, tile.y+j);
            if ( isQuestTile(nextDomain) )
            {
                nextTile = nearestFreeTile(nextDomain);
                if ( nextTile.x != -999 && nextTile.y != -999 )
                {
                    return nextTile;
                }
            }
            
            return nextTile;
        }
        else
        {
            return nextTile;
        }
        
        return nextTile;
    }
    
    bool isTileSelected( const IntPoint& tile )
    {
        for ( vector<IntPoint>::iterator it = selectedTiles.begin(); it != selectedTiles.end(); ++it )
        {
            if ( (*it) == tile )
            {
                return true;
            }
        }
        return false;
    }
    
    void onSecondTalkEnd(bool Accepted)
    {
        GameAPI::Instance()->focusCameraOnFloorTile(ccp(tilesToDig[0].x, tilesToDig[0].y), 0.4f);
        GameAPI::Instance()->pointArrowAtFloor( ccp(tilesToDig[0].x, tilesToDig[0].y), kArrowPointerDirectionDown );
        Button * targetBtn = GameAPI::Instance()->getButtonByID(kDigButtonID);
        targetBtn->setEnabled(false);
        
        Dialog* dlg = GameAPI::Instance()->getDialogByID(kBuildConfirmDialogID);
        dlg->setVisible(true);
        Button * okBt = dlg->getButtonByID(kDigOkButton);
        Button * cancelBt = dlg->getButtonByID(kDigCloseButton);
        okBt->setEnabled(false);
        cancelBt->setEnabled(false);
        LISTEN_TO(TileClickedEvent);
    }
    Slot<void(Button*)> slot_onDigButtonClicked;
    void onDigButtonClicked( Button * btn )
    {
        GameAPI::Instance()->removeArrowPointer();
        Dialog* dlg = GameAPI::Instance()->getDialogByID(kBuildConfirmDialogID);
        if (dlg)
        dlg->setVisible(false);
        
        mMainDialog.sCharacterLine = "  Oh! Do you see those blocks\nof ground?\nLet's dig it!";
        GameAPI::Instance()->showConversationDialog(mMainDialog, bind(&DiggingTutorial::onSecondTalkEnd, this, placeholders::_1));
        
        slot_onDigButtonClicked.disconnect();
        
    }
    
    void onFirstConversationDialogClosed(bool bAccepted)
	{
        Button * targetBtn = GameAPI::Instance()->getButtonByID(kDigButtonID);
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
        slot_onDigButtonClicked = connect(targetBtn->eventClicked, this, &DiggingTutorial::onDigButtonClicked);
	}

	virtual void onSetStarted()
	{
        MonsterFactory::Instance()->setEnabled(false);
        mMainDialog.sCharacterLine = "Seem's you have\nto prepare\na place for your new room\n";
		GameAPI::Instance()->showConversationDialog(mMainDialog,
                                                    bind(&DiggingTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
        // --- set up --- //
        for ( int i = 0; i < kTileCount; ++i )
        {
            GameAPI::Instance()->setTileGID( tilesToDig[i], kTileGIDCaveTop );
            ccColor3B prevColor = GameAPI::Instance()->getTileColor(2, tilesToDig[i]);
            
            
            
            prevColor.r -= static_cast<GLubyte>(prevColor.r*0.35);
            prevColor.g += static_cast<GLubyte>(prevColor.g*0.35);
            prevColor.b -= static_cast<GLubyte>(prevColor.b*0.35);
             
            //GameAPI::Instance()->setTileColor(2, prevColor, tilesToDig[i]);
            GameAPI::Instance()->setTileColor(prevColor, tilesToDig[i]);
        }
        
        Button * targetBtn = GameAPI::Instance()->getButtonByID(kDigButtonID);
        targetBtn->setEnabled(true);
        
        //LightSource* lantern = GameAPI::Instance()->highlightTile(tilesToDig[3], 0.2f);
        //lantern->setDistance(0.3f);
        
	}

	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{
        slot_onDigButtonClicked.disconnect();
        
        Widget * toolBar = GameAPI::Instance()->getWidgetByID(kToolBarWidgetID);
        list<Widget*> tools = *toolBar->getChildrenWidgets();
        GameAPI::Instance()->getWidgetByID(kToolBarWidgetID)->setEnabled(true);
        for ( list<Widget*>::iterator it = tools.begin(); it != tools.end(); it++ )
        {
            if ( !(*it)->isEnabled() )
            {
                (*it)->setEnabled(false);
            }
        }
        Button * targetBtn = GameAPI::Instance()->getButtonByID(kDigButtonID);
        targetBtn->setEnabled(true);
        targetBtn = GameAPI::Instance()->getButtonByID(kUndigButtonID);
        targetBtn->setEnabled(true);
        
		//throw "DiggingTutorial::cleanup() is empty!";
	}

protected:
    int mTilesDone;
    int mTilesClicked;

	virtual void onSetPassive()
	{
        LISTEN_TO(MapLoadedEvent);
        MonsterFactory::Instance()->setEnabled(false);
	}
};

#endif //DIGGINGTUTORIAL_H