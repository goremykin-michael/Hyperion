#ifndef INVENTORYTUTORIAL_H
#define INVENTORYTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/Events/ItemDraggingEvents.h"
#include "Gameplay/Events/ItemEquippedEvent.h"
#include "Gameplay/Events/ItemUnequippedEvent.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Graphics/GUI/Bars/InventoryBar.h"
#include "Graphics/GUI/Dialogs/InventoryDialog.h"

class InventoryTutorial : public Quest
{
THISIS(InventoryTutorial);

public:
	//---------------------------------InventoryTutorial--------------------------------//
	InventoryTutorial()
	{
		_princessDialogDescription.sBackgroundImagePath = "assets/interface/dialogs/conversation-dialog/background-paper-1.png";
		_princessDialogDescription.sCharacterImagePath = "assets/interface/dialogs/conversation-dialog/conversation-character-1.png";
		_princessDialogDescription.sCharacterName = "Fairy";
		_L("character.fairy.name");
	}

	virtual ~InventoryTutorial()
	{
	}
	
	//------------------------------Declarative Description-----------------------------//
	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;

		questDescription.sRewardItemSummary.push_back("sorrow");
		questDescription.sSummary = "Press the button\nto see your inventory!";
		questDescription.sTitle = "Check the inventory";
		
		_L("quest.inventoryTutorial.rewardItemSummary.1");
		_L("quest.inventoryTutorial.summary");
		_L("quest.inventoryTutorial.title");

		return questDescription;
	}

	//--------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return kInventoryTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void onSetStarted()
	{
		_princessDialogDescription.sCharacterLine =
			"Wow! You have an axe!\n\
			You should equip it\n \
			right now.\n\
			Check the quest!";
		_L("quest.inventoryTutorial.line.firstDialog");
		GameAPI::Instance()->showConversationDialog(_princessDialogDescription,
			bind(&InventoryTutorial::onFirstConversationDialogClosed, this, placeholders::_1));
	}

	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{
		UNLISTEN_TO(DialogShowedEvent);
		UNLISTEN_TO(DialogClosedEvent);
		UNLISTEN_TO(ItemDragReturnedEvent);
		UNLISTEN_TO(ItemEquippedEvent);
		UNLISTEN_TO(ItemDragStartedEvent);
	}

	//---------------------------------Game Event Listeners-----------------------------//
	EVENT_LISTENER(DialogShowedEvent)
	{
		_pInventoryDialog = (reinterpret_cast<DialogShowedEvent *>(from->sender))->pDialog;
		if(_pInventoryDialog->getDialogID() == kInventoryDialogID)
		{
			UNLISTEN_TO(DialogShowedEvent);

			GameAPI::Instance()->removeArrowPointer();

			Button * pCloseInventoryDialogButton = _pInventoryDialog->getButtonByID(kCloseInventoryDialogID);
			//pCloseInventoryDialogButton->setEnabled(false);

			InventoryBar * pInventoryBar = (InventoryBar *)GameAPI::Instance()->getWidgetByID(kInventoryBarWidgetID);
			vector<Widget *> itemViews = pInventoryBar->getScrollView()->getItems<Widget>();
			if(!itemViews.empty())
			{
				GameAPI::Instance()->pointArrowAtObject(itemViews[0], kArrowPointerDirectionDown);
			}
			
			LISTEN_TO(ItemDragStartedEvent);
			LISTEN_TO(ItemDragReturnedEvent);
			LISTEN_TO(ItemEquippedEvent);
			LISTEN_TO(DialogClosedEvent);
		}
	}

	EVENT_LISTENER(DialogClosedEvent)
	{
		Dialog * pDialog = (reinterpret_cast<DialogShowedEvent *>(from->sender))->pDialog;
		if(pDialog->getDialogID() == kInventoryDialogID)
		{
			UNLISTEN_TO(ItemDragStartedEvent);
			UNLISTEN_TO(ItemDragReturnedEvent);
			UNLISTEN_TO(ItemEquippedEvent);
			UNLISTEN_TO(DialogClosedEvent);
			setCompleted();
		}
	}

	EVENT_LISTENER(ItemDragReturnedEvent)
	{
		//TODO: uncomment this when dragging works properly
		//Button * pCloseInventoryDialogButton = _pInventoryDialog->getButtonByID(kCloseInventoryDialogID);
		//pCloseInventoryDialogButton->setEnabled(false);
		
		pointArrowOnInventoryBarItem();
	}

	EVENT_LISTENER(ItemEquippedEvent)
	{
		Button * pCloseInventoryDialogButton = _pInventoryDialog->getButtonByID(kCloseInventoryDialogID);
		pCloseInventoryDialogButton->setEnabled(true);
		
		pointArrowOnCloseButton();
	}

	EVENT_LISTENER(ItemDragStartedEvent)
	{
		pointArrowOnWeaponSlot();
	}

protected:
	//---------------------------------InventoryTutorial--------------------------------//
	Dialog * _pInventoryDialog;
	ConversationDialogDescription _princessDialogDescription;

	void pointArrowOnWeaponSlot()
	{
		ItemSlotView * pWeaponSlotView = ((InventoryDialog *)_pInventoryDialog)->getSlotByID(kInventoryDialogSlotWeapon);
		GameAPI::Instance()->pointArrowAtObject(pWeaponSlotView, kArrowPointerDirectionRight);
	}

	void pointArrowOnInventoryBarItem()
	{
		InventoryBar * pInventoryBar = (InventoryBar *)GameAPI::Instance()->getWidgetByID(kInventoryBarWidgetID);
		vector<Widget *> itemViews = pInventoryBar->getScrollView()->getItems<Widget>();
		if(!itemViews.empty())
		{
			GameAPI::Instance()->pointArrowAtObject(itemViews[0], kArrowPointerDirectionDown);
		}
	}

	void pointArrowOnCloseButton()
	{
		Button * pCloseInventoryDialogButton = _pInventoryDialog->getButtonByID(kCloseInventoryDialogID);
		GameAPI::Instance()->pointArrowAtObject(pCloseInventoryDialogButton, kArrowPointerDirectionUp);
	}
	
	void onFirstConversationDialogClosed(bool bAccepted)
	{
		Button * pInventoryButton = GameAPI::Instance()->getButtonByID(kInventoryButtonID);
		pInventoryButton->setEnabled(true);
		GameAPI::Instance()->pointArrowAtObject(pInventoryButton, kArrowPointerDirectionRight);

		LISTEN_TO(DialogShowedEvent);
	}
};

#endif //INVENTORYTUTORIAL_H