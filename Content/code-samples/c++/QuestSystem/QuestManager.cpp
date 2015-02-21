#include "Gameplay/QuestSystem/QuestManager.h"

#include "Data/DataBase/DataProviders/QuestDataProvider.h"
#include "Gameplay/QuestSystem/Quests/TestQuest1.hpp"
#include "Gameplay/QuestSystem/QuestFactory.hpp"

QuestManager::QuestManager()
{
	LISTEN_TO(QuitGameEvent);
	LISTEN_TO(ResetGameEvent);
	/*auto lambda = [] ()
					{
						CCLog("I am LAMBDA...");
					};
	lambda();*/
}

QuestManager::~QuestManager()
{
	UNLISTEN_TO(QuitGameEvent);
	UNLISTEN_TO(ResetGameEvent);
}

void QuestManager::addNextQuestForCharacter(GameObjectID gameObjectID)
{
	//TODO: that's obvious
	//addActiveQuest(new MovementTutorial());
}

std::list<Quest *> QuestManager::getExplicitQuests()
{
	std::list<Quest *> explicitQuests;

	std::list<Quest *>::iterator it = _quests.begin();
	for(; it != _quests.end(); ++it)
	{
		if((*it)->isExplicit())
		{
			explicitQuests.push_back((*it));
		}
	}

	return explicitQuests;
}

void QuestManager::initialize()
{
#ifdef DUNGEONS_DEBUG_QUESTS
	loadDebugQuests();
#else
	loadQuests();
#endif
}

void QuestManager::loadQuests()
{
	std::vector<QuestID> completedQuestIDs;	// completed quests
	std::vector<QuestID> explicitQuestIDs;	// explicit quests but not started yet(ono est v spiske questov no knopka start eshe ne nazhata)
	std::vector<QuestID> startedQuestIDs;	// quests in progress
	std::vector<QuestID> allQuestIDs;		// all quests
	std::vector<QuestID> passiveQuestIDs;	// quests to be loaded as passive, passive = all - completed - current

	// initializing various lists of quest IDs
	QuestDataProvider::Instance()->getCompletedQuestIDs(completedQuestIDs);
	QuestDataProvider::Instance()->getExplicitQuestIDs(explicitQuestIDs);
	QuestDataProvider::Instance()->getStartedQuestIDs(startedQuestIDs);
	allQuestIDs = QuestFactory::getAllQuestIDs();
	
	// calculating passive quest IDs
	for(unsigned int i = 0; i < allQuestIDs.size(); ++i)
	{
		// if the quest is not explicit & is not started & is not completed
		if(find(startedQuestIDs.begin(), startedQuestIDs.end(), allQuestIDs[i]) == startedQuestIDs.end() &&
			find(explicitQuestIDs.begin(), explicitQuestIDs.end(), allQuestIDs[i]) == explicitQuestIDs.end() &&
			find(completedQuestIDs.begin(), completedQuestIDs.end(), allQuestIDs[i]) == completedQuestIDs.end())
		{
			passiveQuestIDs.push_back(allQuestIDs[i]);
		}
	}

#ifndef DUNGEONS_DEBUG_QUESTS
	// if EscapeTutorial isn't finished yet, than we need to start from scratch both ActionTutorial & EscapeTutorial
    // ivan's advise
	if(find(completedQuestIDs.begin(), completedQuestIDs.end(), kEscapeTutorialID) == completedQuestIDs.end())
	{
        // if escape tutorial was not completed - remove all explicit and started quests
        explicitQuestIDs.clear();
        startedQuestIDs.clear();
        
		// if ActionTutorial was not added to passive quest IDs, than add it
		if(find(passiveQuestIDs.begin(), passiveQuestIDs.end(), kActionTutorialID) == passiveQuestIDs.end())
		{
			passiveQuestIDs.push_back(kActionTutorialID);
		}

		// if EscapeTutorial was not added to passive quest IDs, than add it
		if(find(passiveQuestIDs.begin(), passiveQuestIDs.end(), kEscapeTutorialID) == passiveQuestIDs.end())
		{
			passiveQuestIDs.push_back(kEscapeTutorialID);
		}
	}
#endif

	// loading passive quests
	for(unsigned int i = 0; i < passiveQuestIDs.size(); ++i)
	{
		addPassiveQuest(QuestFactory::createQuestByID(passiveQuestIDs[i]));
	}

	// loading explicit quests
	for(unsigned int i = 0; i < explicitQuestIDs.size(); ++i)
	{
		addExplicitQuest(QuestFactory::createQuestByID(explicitQuestIDs[i]));
	}

	// loading started quests
	for(unsigned int i = 0; i < startedQuestIDs.size(); ++i)
	{
		addStartedQuest(QuestFactory::createQuestByID(startedQuestIDs[i]));
	}
}

void QuestManager::addPassiveQuest(Quest * pQuest)
{
	pQuest->setPassive();
	_quests.push_back(pQuest);
}

void QuestManager::addExplicitQuest(Quest * pQuest)
{
	pQuest->_bIsExplicit = true;
	_quests.push_back(pQuest);
}

void QuestManager::addStartedQuest(Quest * pQuest)
{
	if(pQuest->isSingleQuest())
	{
		pQuest->restoreState();
		pQuest->setStarted();
	}
	else if(pQuest->isSubquestContainer())
	{
		vector<Quest *>::iterator it = pQuest->_subquests.begin();
		for(; it != pQuest->_subquests.end(); ++it)
		{
			// check if subquest is already completed
			if(QuestDataProvider::Instance()->isQuestCompleted((*it)->getQuestID()))
			{
				// then just set it completed and do nothing else
				(*it)->_bIsCompleted = true;
			}
			// check if subquest is already started
			else if(QuestDataProvider::Instance()->isQuestStarted((*it)->getQuestID()))
			{
				(*it)->restoreState();
				(*it)->setStarted();
			}
		}
	}
}

void QuestManager::loadDebugQuests()
{
	vector<QuestID> allQuestIDs = QuestFactory::getAllQuestIDs();
	for(unsigned int i = 0; i < allQuestIDs.size(); ++i)
	{
		Quest * pQuest = QuestFactory::createQuestByID(allQuestIDs[i]);
		if(pQuest->debug())
		{
			_quests.push_back(pQuest);
		}
		else
		{
			delete pQuest;
		}
	}
}

void QuestManager::removeAllQuests()
{
	list<Quest *>::iterator it = _quests.begin();
	while(it != _quests.end())
	{
		(*it)->cleanup();
		delete *it;

		it++;
	}

    _quests.clear();
}

void QuestManager::saveAllQuests()
{
	list<Quest *>::iterator it = _quests.begin();
	while(it != _quests.end())
	{
		(*it)->saveState();
		++it;
	}
}

void QuestManager::handle(Event<QuitGameEvent> event, IEventDispatcher * from)
{
	saveAllQuests();
	removeAllQuests();
}

void QuestManager::handle(Event<ResetGameEvent> event, IEventDispatcher * from)
{
	removeAllQuests();
    initialize();
}
