#ifndef COLLECTITEMCONSTRUCTEDQUEST_HPP
#define COLLECTITEMCONSTRUCTEDQUEST_HPP

#include "DungeonsIncludes.h"
#include "Gameplay/Events/GameItemPickedEvent.h"
#include "Gameplay/Inventory/Inventory.h"
#include "Gameplay/QuestSystem/QuestBuilder/ConstructedQuests/ConstructedQuest.hpp"

class CollectItemQuestDefinition : public ConstructedQuestDefinition
{
public:
	string sTypeOfCollectedItem;
	int iCountOfItemsToCollect;
};

class CollectItemConstructedQuest : public ConstructedQuest
{
THISIS(CollectItemConstructedQuest);

public:
	//-------------------------------CollectItemConstructedQuest-------------------------------//
	CollectItemConstructedQuest()
	{
	}

	virtual ~CollectItemConstructedQuest()
	{
	}

	void setTypeOfCollectedItem(const string & crsTypeOfCollectedItem)
	{
		_sTypeOfCollectedItem = crsTypeOfCollectedItem;
	}

	void setCountOfItemsToCollect(int iCountOfItemsToCollect)
	{
		_iCountOfItemsToCollect = iCountOfItemsToCollect;
	}

	//------------------------------------------Quest------------------------------------------//
	virtual void onSetStarted()
	{
		LISTEN_TO(GameItemPickedEvent);
	}

	virtual bool isStartForced() { return false; }

	virtual void saveState()
	{
	}

	virtual void restoreState()
	{
	}

	virtual void cleanup()
	{
		UNLISTEN_TO(GameItemPickedEvent);
	}

	virtual bool debug()
	{
		LISTEN_TO(MapLoadedEvent);

		return true;
	}

	//-----------------------------------Game Event Listeners----------------------------------//
	EVENT_LISTENER(GameItemPickedEvent)
	{
		GameItemPickedEvent * pEvent = reinterpret_cast<GameItemPickedEvent *>(from->sender);

		if(pEvent->pGameItem->getModel()->getType() == _sTypeOfCollectedItem)
		{
			UNLISTEN_TO(GameItemPickedEvent);
			setCompleted();
		}
	}
	
	EVENT_LISTENER(MapLoadedEvent)
	{
		//setExplicit();
	}

protected:
	//------------------------------------------Quest------------------------------------------//
	virtual void onSetPassive()
	{
		LISTEN_TO(MapLoadedEvent);
	}

	virtual bool onSetSkipped(string & rsReason)
	{
		if(_sTypeOfCollectedItem == "axe")
		{
			return true;
		}
		else
		{
			rsReason = "Do It Yourself!";
			return false;
		}
	}

	//-------------------------------CollectItemConstructedQuest-------------------------------//
	string _sTypeOfCollectedItem;
	int _iCountOfItemsToCollect;

	enum
	{
		kCurrentCountOfCollectedItems
	};
};

#endif //COLLECTITEMCONSTRUCTEDQUEST_HPP