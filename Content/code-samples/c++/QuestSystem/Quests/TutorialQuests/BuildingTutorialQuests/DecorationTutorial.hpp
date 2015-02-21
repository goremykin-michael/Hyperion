#ifndef DECORATIONTUTORIAL_H
#define DECORATIONTUTORIAL_H

#include "DungeonsIncludes.h"
#include "Gameplay/QuestSystem/Quest.h"

class DecorationTutorial : public Quest
{
public:
	//---------------------------------DecorationTutorial---------------------------------//
	DecorationTutorial()
	{
	}

	virtual ~DecorationTutorial()
	{
	}
	
	//-------------------------------Declarative Description------------------------------//
	virtual QuestDescription getQuestDescription()
	{
		QuestDescription questDescription;

		return questDescription;
	}

	//---------------------------------------Quest----------------------------------------//
	virtual QuestID getQuestID()
	{
		return kDecorationTutorialID;
	}

	virtual bool isSkippable()
	{
		return false;
	}

	virtual void saveState() {}

	virtual void restoreState() {}

	virtual void cleanup()
	{

	}

protected:
	//---------------------------------------Quest----------------------------------------//
	virtual void onSetPassive()
	{
	}
};

#endif //DECORATIONTUTORIAL_H