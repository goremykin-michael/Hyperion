#ifndef OBJECTONMAPINTERACTIONTUTORIAL_H
#define OBJECTONMAPINTERACTIONTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/GameObjects/GameContainer.h"
#include "Gameplay/Events/GameItemPickedEvent.h"
#include "Gameplay/Inventory/Inventory.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Graphics/GUI/Bars/InventoryBar.h"
#include "Gameplay/Inventory/GameItem.h"

class ObjectOnMapInteractionTutorial : public Quest
{
THISIS(ObjectOnMapInteractionTutorial);

public:

	//--------------------------ObjectOnMapInteractionTutorial--------------------------//
	ObjectOnMapInteractionTutorial():
	  _lantern(nullptr),
	  _availableAreaTopPoint(CCPoint(0, 0)),
	  _iAvailableAreaWidth(5),
	  _iAvailableAreaHeight(8)
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
	}

	virtual ~ObjectOnMapInteractionTutorial()
	{
	}

	//------------------------------Declarative Description-----------------------------//
	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;

		questDescription.sRewardItemSummary.push_back("chest contents");
		questDescription.sSummary = "Tap on the chest,\nand see, what's inside.";
		questDescription.sTitle = "Find some weapon";
		
		_L("quest.objectOnMapInteractionTutorial.rewardItemSummary.1");
		_L("quest.objectOnMapInteractionTutorial.summary");
		_L("quest.objectOnMapInteractionTutorial.title");

		return questDescription;
	}

	//--------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return kObjectOnMapInteractionTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void onSetStarted()
	{
		_princessDialogDescription.sCharacterLine =
			"It's a dangerous place!\n\
			You need a weapon\n\
			to equip.\n\
			Look, what's in the chest!";
		_L("quest.objectOnMapInteractionTutorial.line.firstDialog");

		GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
			bind(&ObjectOnMapInteractionTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
	}

	virtual void saveState()
	{
	}

	virtual void restoreState()
	{
	}

	virtual void cleanup()
	{
		UNLISTEN_TO(GameItemPickedEvent);

		_chestClickedSlot.disconnect();
		_inventoryItemAddedSlot.disconnect();
	}
	
	//-------------------------------Game Event Listeners-------------------------------//
	EVENT_LISTENER(GameItemPickedEvent)
	{
		UNLISTEN_TO(GameItemPickedEvent);
		GameAPI::Instance()->removeArrowPointer();
	}

protected:
	//--------------------------ObjectOnMapInteractionTutorial--------------------------//
	CCPoint _availableAreaTopPoint;
	int _iAvailableAreaWidth, _iAvailableAreaHeight;

	ConversationDialogDescription _princessDialogDescription;
	Slot<void (GameObject *)> _chestClickedSlot;
	Slot<void (Inventory *, Item *, int)> _inventoryItemAddedSlot;

    LightSource* _lantern;
    
	void onFirstConversationDialogClosed(bool bAccepted)
	{
		GameObject * pChest = GameAPI::Instance()->getObjectByName("containers/chest-tutorial");
		GameAPI::Instance()->pointArrowAtFloor(pChest->getPosition(), kArrowPointerDirectionDown);//(pChest->getSprite(), kArrowPointerDirectionDown);
        _lantern = GameAPI::Instance()->highlightTile(IntPoint(pChest->getPosition()));
		GameAPI::Instance()->focusCameraOnGameObject(pChest, 1.f);

		_chestClickedSlot = connect(pChest->eventClicked, this, &ObjectOnMapInteractionTutorial::onChestClicked);
		_inventoryItemAddedSlot = connect(GameAPI::Instance()->getInventory()->eventItemAdded, this, &ObjectOnMapInteractionTutorial::onInventoryItemAdded);

		GameAPI::Instance()->setPlayerTargetResponseToAreaOnly(_availableAreaTopPoint, _iAvailableAreaWidth, _iAvailableAreaHeight);

		LISTEN_TO(GameItemPickedEvent);
	}

	void onLastConversationDialogClosed(bool bAccepted)
	{
		setCompleted();
	}
    
    void onItemDropped( Inventory*, GameItem* pItem, int n )
    {
        if ( !pItem )
        {
            CCLog("something wrong");
            return;
        }
        
        pItem->addParentNode();
        
        GameAPI::Instance()->pointArrowAtObject(pItem->getView()->getParent(), kArrowPointerDirectionDown);
    }

	void onChestClicked(GameObject * pGameObject)
	{
        GameContainer * pChestContainer = static_cast<GameContainer*>(pGameObject);
		_chestClickedSlot.disconnect();
        
		GameAPI::Instance()->removeArrowPointer();
        GameAPI::Instance()->removeLight(_lantern);
        
        Inventory* targetInventory = pChestContainer->getInventory();
        connect( targetInventory->eventItemDropped, this, &ObjectOnMapInteractionTutorial::onItemDropped );
        InventoryBar::Instance()->show();
	}

	void onInventoryItemAdded(Inventory * pInventory, Item * pItemArray, int iNumberOfItems)
	{
		if(pItemArray->getType() == "axe")
		{
			_inventoryItemAddedSlot.disconnect();
			_princessDialogDescription.sCharacterLine =
				"Very good!\n \
				Now you can punish\n\
				any bad guy!";
		_L("quest.objectOnMapInteractionTutorial.line.lastDialog");

			GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
				bind(&ObjectOnMapInteractionTutorial::onLastConversationDialogClosed, this, placeholders::_1));
		}
	}
};

#endif //OBJECTONMAPINTERACTIONTUTORIAL_H