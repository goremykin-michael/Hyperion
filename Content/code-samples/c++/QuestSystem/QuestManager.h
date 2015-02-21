#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include "DungeonsIncludes.h"
#include "DesignPatterns/Singleton.hpp"
#include "Gameplay/Events/QuitGameEvent.h"
#include "Gameplay/Events/ResetGameEvent.h"
#include "Gameplay/GameObjects/GameObject.h"
#include "Gameplay/QuestSystem/Quest.h"
#include "Graphics/GUI/Bars/QuestBar.h"
#include "Graphics/GUI/Buttons/QuestButton.h"

#define QUEST_MANAGER_MAX_COUNT_OF_SIMULTANEOUS_QUESTS 6

class QuestManager : public Singleton<QuestManager>
{
THISIS(QuestManager);

friend class Singleton<QuestManager>;

public:
	/// Seem to be deprecated
	void addNextQuestForCharacter(GameObjectID gameObjectID);

	/// Shoud be called only once - on startup.
	void initialize();
	
	Signal <void (Quest * /*pQuest*/) > signalQuestAdded;
	Signal <void (int /*iQuestID*/) > signalQuestRemoved;

	std::list<Quest *> getExplicitQuests();
	
	EVENT_LISTENER(QuitGameEvent);
	EVENT_LISTENER(ResetGameEvent);

protected:
	QuestManager();
	~QuestManager();

	/// Load list of explicit, started & passive quests.
	/// Passive quests only listen to game events and change their state to active if it's possible.
	void loadQuests();
	
	/// Load all quests, which override the debug()-method.
	void loadDebugQuests();

	/// Setup quest as passive and add to list of quests.
	void addPassiveQuest(Quest * pQuest);

	/// Setup quest as explicit and add to list of quests.
	void addExplicitQuest(Quest * pQuest);
	
	/// Setup quest as explicit and add to list of quests.
	void addStartedQuest(Quest * pQuest);

	void removeAllQuests();

	void saveAllQuests();
	
	std::list<Quest *> _quests;
};

#endif //QUESTMANAGER_H
