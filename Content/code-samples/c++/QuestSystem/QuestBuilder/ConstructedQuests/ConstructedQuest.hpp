#ifndef CONSTRUCTEDQUEST_HPP
#define CONSTRUCTEDQUEST_HPP

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"

class ConstructedQuestDefinition
{
public:
	QuestID questID;
	bool bIsSkippable;
	bool bIsStartForced;
	bool bSubquestsAreOrdered;

	QuestButtonDescription questButtonDescription;
	QuestDialogDescription questDialogDescription;
	QuestDescription questDescription;
};

class ConstructedQuest : public Quest
{
THISIS(ConstructedQuest);

public:
	//-----------------------------------ConstructedQuest---------------------------------//
	ConstructedQuest()
	{
	}

	~ConstructedQuest()
	{
	}

	//-------------------------------Declarative Description------------------------------//
	virtual QuestDescription getQuestDescription()
	{
		return _questDescription;
	}

	void setQuestDescription(const QuestDescription & crQuestDescription)
	{
		_questDescription = crQuestDescription;
	}

	virtual QuestButtonDescription getQuestButtonDescription()
	{
		return _questButtonDescription;
	}

	void setQuestButtonDescription(const QuestButtonDescription & crQuestButtonDescription)
	{
		_questButtonDescription = crQuestButtonDescription;
	}

	virtual QuestDialogDescription getQuestDialogDescription()
	{
		return _questDialogDescription;
	}

	void setQuestDialogDescription(const QuestDialogDescription & crQuestDialogDescription)
	{
		_questDialogDescription = crQuestDialogDescription;
	}

	void setSubquestsAreOrdered(bool bSubquestsAreOrdered)
	{
		_bSubquestsAreOrdered = bSubquestsAreOrdered;
	}

	virtual bool areSubquestsOrdered()
	{
		return _bSubquestsAreOrdered;
	}

	//---------------------------------------Quest---------------------------------------//
	virtual QuestID getQuestID()
	{
		return _questID;
	}

	void setQuestID(QuestID questID)
	{
		_questID = questID;
	}

	void setSkippable(bool bIsSkippable)
	{
		_bIsSkippable = bIsSkippable;
	}

	virtual bool isSkippable()
	{
		return _bIsSkippable;
	}

	void setStartForced(bool bIsStartForced)
	{
		_bIsStartForced = bIsStartForced;
	}

	virtual bool isStartForced()
	{
		return _bIsStartForced;
	}

	virtual void saveState()
	{
		//TODO: save state of a general quest container
		vector<Quest *>::iterator it = _subquests.begin();
		for(; it != _subquests.end(); ++it)
		{
			(*it)->saveState();
		}
	}

	virtual void restoreState()
	{
		//TODO: restore state of a general quest container
		vector<Quest *>::iterator it = _subquests.begin();
		for(; it != _subquests.end(); ++it)
		{
			(*it)->restoreState();
		}
	}

	virtual void cleanup()
	{
		//TODO: cleanup a general quest container
		vector<Quest *>::iterator it = _subquests.begin();
		for(; it != _subquests.end(); ++it)
		{
			(*it)->cleanup();
		}
	}

	virtual bool debug()
	{
		LISTEN_TO(MapLoadedEvent);

		return true;
	}

	//-------------------------------Game Event Listeners-------------------------------//
    EVENT_LISTENER(MapLoadedEvent)
	{
		MapLoadedEvent * pMapLoadedEvent = reinterpret_cast<MapLoadedEvent *>(from->sender);

		//if(pMapLoadedEvent->sMapName == "map-tutorial")
		{
            UNLISTEN_TO(MapLoadedEvent);

			setExplicit();
		}
	}

protected:
	QuestID _questID;
	bool _bIsSkippable, _bIsStartForced, _bSubquestsAreOrdered;

	QuestButtonDescription _questButtonDescription;
	QuestDialogDescription _questDialogDescription;
	QuestDescription _questDescription;
};

#endif //CONSTRUCTEDQUEST_HPP