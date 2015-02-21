#ifndef KILLENEMYCONSTRUCTEDQUEST_HPP
#define KILLENEMYCONSTRUCTEDQUEST_HPP

#include "DungeonsIncludes.h"
#include "Gameplay/Events/CharacterDiedEvent.h"
#include "Gameplay/QuestSystem/QuestBuilder/ConstructedQuests/ConstructedQuest.hpp"

class KillEnemyQuestDefinition : public ConstructedQuestDefinition
{
public:
	int iCountOfEnemiesToBeKilled;
};

class KillEnemyConstructedQuest : public ConstructedQuest
{
THISIS(KillEnemyConstructedQuest);

public:
	//-------------------------------KillEnemyConstructedQuest-------------------------------//
	KillEnemyConstructedQuest() :
		_iCurrentCountOfKilledEnemies(0)
	{
	}

	virtual ~KillEnemyConstructedQuest()
	{
	}

	int getCountOfEnemiesToBeKilled()
	{
		return _iCountOfEnemiesToBeKilled;
	}

	void setCountOfEnemiesToBeKilled(int iCountOfEnemiesToBeKilled)
	{
		_iCountOfEnemiesToBeKilled = iCountOfEnemiesToBeKilled;
	}

	//------------------------------------------Quest------------------------------------------//
	virtual void onSetStarted()
	{
		LISTEN_TO(CharacterDiedEvent);
	}

	virtual void saveState()
	{
		QuestDataProvider::Instance()->setQuestParameter(getQuestID(), kCurrentCountOfKilledEnemies, TextUtils::ToString(_iCurrentCountOfKilledEnemies));
	}

	virtual void restoreState()
	{
		string sCurrentCountOfKilledEnemies;
		QuestDataProvider::Instance()->getQuestParameter(getQuestID(), kCurrentCountOfKilledEnemies, sCurrentCountOfKilledEnemies);

		_iCurrentCountOfKilledEnemies = TextUtils::ToInt32(sCurrentCountOfKilledEnemies);
	}

	virtual void cleanup()
	{
		UNLISTEN_TO(MapLoadedEvent);
	}

	virtual bool debug()
	{
		LISTEN_TO(MapLoadedEvent);

		return true;
	}

	//-----------------------------------Game Event Listeners----------------------------------//
	EVENT_LISTENER(MapLoadedEvent)
	{
		MapLoadedEvent * pMapLoadedEvent = reinterpret_cast<MapLoadedEvent *>(from->sender);

		if(pMapLoadedEvent->sMapName == "quest1")
		{
			setExplicit();
		}
	}

	EVENT_LISTENER(CharacterDiedEvent)
	{
		CharacterDiedEvent * pCharacterDiedEvent = reinterpret_cast<CharacterDiedEvent *>(from->sender);

		++_iCurrentCountOfKilledEnemies;
		saveState();

		if(_iCurrentCountOfKilledEnemies == _iCountOfEnemiesToBeKilled)
		{
			UNLISTEN_TO(CharacterDiedEvent);
			UNLISTEN_TO(MapLoadedEvent);

			setCompleted();
		}
		else
		{
			signalProgress(QuestProgressInfo(getQuestID(), _iCurrentCountOfKilledEnemies, _iCountOfEnemiesToBeKilled));
		}
	}

protected:
	//------------------------------------------Quest------------------------------------------//
	virtual void onSetPassive()
	{
		LISTEN_TO(MapLoadedEvent);
	}

	//-------------------------------KillEnemyConstructedQuest-------------------------------//
	int _iCountOfEnemiesToBeKilled;
	int _iCurrentCountOfKilledEnemies;

	enum
	{
		kCurrentCountOfKilledEnemies
	};
};

#endif //KILLENEMYCONSTRUCTEDQUEST_HPP