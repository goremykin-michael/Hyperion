#include "Gameplay/QuestSystem/Quest.h"
#include "Gameplay/QuestSystem/QuestManager.h"
#include "Data/DataBase/DataProviders/QuestDataProvider.h"

Quest::Quest() :
	_bIsCompleted(false),
	_bIsStarted(false),
	_bIsExplicit(false),
	_bDebug(true),
	_iCountOfCompletedSubquests(0)
{
	_questProgressSlot = connect(Quest::signalProgress, this, &Quest::onQuestProgress);
	_questCompletionSlot = connect(Quest::signalCompletion, this, &Quest::onQuestCompletion);
}

Quest::~Quest()
{
	_questProgressSlot.disconnect();
	_questCompletionSlot.disconnect();

	vector<Quest *>::iterator it = _subquests.begin();
	while(it != _subquests.end())
	{
		delete *it;
		it++;
	}

    _subquests.clear();
}

bool Quest::isSubquestContainer()
{
	return !_subquests.empty();
}

bool Quest::isSubquest()
{
	return getQuestButtonDescription().sIconImagePath.empty();
}

bool Quest::isSingleQuest()
{
	return !isSubquestContainer() && !isSubquest();
}

QuestButtonDescription Quest::getQuestButtonDescription()
{
	return QuestButtonDescription();
}

QuestDialogDescription Quest::getQuestDialogDescription()
{
	return QuestDialogDescription();
}

std::vector<Quest *> Quest::getSubquests()
{
	return _subquests;
}

void Quest::setStarted()
{
	_bIsStarted = true;
	QuestDataProvider::Instance()->setQuestStarted(getQuestID());
	onSetStarted();
}

void Quest::setExplicit()
{
	_bIsExplicit = true;

	if(!isStartForced() && isSingleQuest())
	{
		setStarted();
	}
	else
	{
		QuestDataProvider::Instance()->setQuestExplicit(getQuestID());
	}

	if(isSubquestContainer())
	{
		vector<Quest *>::iterator it = _subquests.begin();
		for(; it != _subquests.end(); ++it)
		{
			if(!(*it)->isStartForced())
			{
				(*it)->setStarted();
			}
		}
	}
	//TODO: rename signal. Make an event.
	QuestManager::Instance()->signalQuestAdded(this);
}

bool Quest::isExplicit()
{
	return _bIsExplicit;
}

void Quest::addSubquest(Quest * pSubquest)
{
	LISTEN_TO(QuestCompletionInfo);
	_subquests.push_back(pSubquest);
}

void Quest::setPassive()
{
	onSetPassive();
}

bool Quest::isStarted()
{
	return _bIsStarted;
}

vector<QuestID> Quest::getSubquestIDs()
{
	vector<QuestID> subquestIDs;

	for(unsigned int i = 0; i < _subquests.size(); ++i)
	{
		subquestIDs.push_back(_subquests[i]->getQuestID());
	}

	return subquestIDs;
}

bool Quest::isCompleted()
{
	return _bIsCompleted;
}

void Quest::setCompleted()
{
	_bIsStarted = false;
	_bIsCompleted = true;

	QuestDataProvider::Instance()->setQuestCompleted(getQuestID());
    signalCompletion(QuestCompletionInfo(getQuestID(), true));
    cleanup();
}

bool Quest::setSkipped(string & rsReason)
{
	bool bResult = onSetSkipped(rsReason);

	if(bResult)
	{
		setCompleted();
		cleanup();
	}

	return bResult;
}

void Quest::onQuestProgress(QuestProgressInfo questProgressInfo)
{
	saveState();
	IEventDispatcher::fire<QuestProgressInfo>(&questProgressInfo);
}

void Quest::onQuestCompletion(QuestCompletionInfo questCompletionInfo)
{
	IEventDispatcher::fire<QuestCompletionInfo>(&questCompletionInfo);
}

void Quest::handle(Event<QuestCompletionInfo> event, IEventDispatcher * from)
{
	QuestCompletionInfo * pQuestCompletionInfo = reinterpret_cast<QuestCompletionInfo *>(from->sender);
		
	auto subquestIDs = getSubquestIDs();

	if(find(subquestIDs.begin(), subquestIDs.end(),
		pQuestCompletionInfo->questID) != subquestIDs.end())
	{
		++_iCountOfCompletedSubquests;
		signalProgress(QuestProgressInfo(getQuestID(), _iCountOfCompletedSubquests, subquestIDs.size()));

		if(_iCountOfCompletedSubquests == 1)
		{
			QuestDataProvider::Instance()->setQuestStarted(getQuestID());
		}
		else if(_iCountOfCompletedSubquests == subquestIDs.size())
		{
			setCompleted();
		}
	}
}