#ifndef QUEST_H
#define QUEST_H

#include "DungeonsIncludes.h"
#include "Data/DataBase/DataProviders/QuestDataProvider.h"
#include "Data/DataBase/DataProviders/TextDataProvider.h"
#include "Gameplay/GameAPI.h"
#include "Gameplay/QuestSystem/QuestIDs.h"
#include "Utils/Signals.h"

/// Uncomment this to enable check for debug()-method in all-quests.
#define DUNGEONS_DEBUG_QUESTS

/// QuestButtonDescription - contains data to create a corresponding to the quest button.
/// Usable for a container quest or a single quest.
class QuestButtonDescription
{
public:
	std::string sIconImagePath;
	bool bUseProgressLabel;
	int iNumberOfSteps;
};

/// QuestDialogDescription - contains data to create a corresponding to the quest dialog.
/// Usable for a container quest or a single quest.
class QuestDialogDescription
{
public:
	std::string sBackgroundImagePath;
	std::string sCharacterImagePath;
};

/// QuestDescription - contains data which describes a quest.
/// Usable for all types of quest.
class QuestDescription
{
public:
	std::string sTitle;
	std::string sSummary;
	std::vector<std::string> sRewardItemSummary;
};

class QuestCompletionInfo
{
public:
	QuestCompletionInfo(QuestID questID, bool bSucceded)
	{
		this->questID = questID;
		this->bSucceded = bSucceded;
	}

	~QuestCompletionInfo()
	{
	}

	QuestID questID;
	bool bSucceded;
};

class QuestProgressInfo
{
public:
	QuestProgressInfo(QuestID questID, int iCurrentStep, int iNumberOfSteps)
	{
		this->questID = questID;
		this->iCurrentStep = iCurrentStep;
		this->iNumberOfSteps = iNumberOfSteps;
	}

	QuestID questID;
	int iCurrentStep;
	int iNumberOfSteps;
};

class QuestManager;

/// Quest — a base class for all game quests.
/// Contains only game logic and provides ability to subscribe to its' events (onQuestProgress, onQuestComplete, etc).
class Quest
{
THISIS(Quest);

friend class QuestManager;

public:
	Quest();
	virtual ~Quest();
	
	//-------------------------------Declarative Description------------------------------//
	virtual QuestButtonDescription getQuestButtonDescription();
	virtual QuestDialogDescription getQuestDialogDescription();
	virtual QuestDescription getQuestDescription() = 0;

	//------------------------------------Quest States------------------------------------//
	/// Starts the quest externally.
	/// This method is called when "Start" button in QuestDialog is pressed or
	/// when the quest is not force started and is set explicit.
	/// Usable for a container quest, a subquest or a single quest.
	void setStarted();
	
	/// The quest publicly signals that it is added to the list of quests.
	/// E.g. when that method is called the QuestBar adds corresponding QuestButton.
	/// Usable for a container quest or a single quest.
	void setExplicit();

	/// The quests starts listening to passive game events.
	/// It is called by QuestManager on app startup.
	/// Usable for a container quest or a single quest.
	void setPassive();
    
	/// The corresponding signal is emmited.
	/// Usable for a container quest, a subquest or a single quest.
    void setCompleted();

	/// If the quest is started.
	/// Usable for a container quest, a subquest or a single quest.
	bool isStarted();

	/// If the quest is completed.
	/// Usable for a container quest or a single quest.
	bool isExplicit();

	/// If the quest is completed.
	/// Usable for a container quest, a subquest or a single quest.
	bool isCompleted();

	/// Saves the quest's state to the data base.
	/// The method can be called both from the inside and outside of the quest.
	/// From the inside: the quest saves its state when, it "thinks", it should be done.
	/// From the outside: when closing application all quests are forced to save their current state.
	virtual void saveState() = 0;

	/// Restores the quest's state on game startup,
	/// as it was when the game was quited last time.
	virtual void restoreState() = 0;

	/// When the quest is forced to be ended due to quiting game
	/// or starting a new game or whatever it should unsubscribe, unlisten and release
	// everything it acquired correctly.
	virtual void cleanup() = 0;

	//------------------------------------Quest Logic------------------------------------//
	virtual QuestID getQuestID() = 0;

	/// If player should press "Start"-button to start the quest.
	/// @return. "true" - should press, "false" - should not press.
	virtual bool isStartForced() { return true; }

	/// If you want to debug only this very quest,
	/// you should override that method.
	/// Write there setup-code, as if it was onSetPassive() method:
	/// setup listening to game events, which will cause the quest to be
	/// setExplicit().
	/// @return. "true" - should debug, "false" - should not debug.
	virtual bool debug() { return _bDebug = false; }
    
    bool isDebugging() { return _bDebug; }

	//----------------------------------Skipping Quest-----------------------------------//
	/// If this quest can be skipped.
	virtual bool isSkippable() { return false; }
	
	/// Try to skip the quest.
	/// @param rsReason. If skipping quest was rejected (due to lack of money), than rsReason contains the reason, why it was rejected.
	/// return. true - if quest was skipped, false - otherwise.
	bool setSkipped(string & rsReason);
	
	//-------------------------------------SubQuests-------------------------------------//
	/// If the quest contains subquests.
	bool isSubquestContainer();

	/// If the quest is a subquest.
	bool isSubquest();

	/// If the quest doesn't have subquests and is not a subquest itself.
	bool isSingleQuest();

	/// Add damn subquest.
	void addSubquest(Quest * pSubquest);

	/// That's obvious.
	vector<Quest *> getSubquests();

	/// Get list of all subquests' IDs.
	vector<QuestID> getSubquestIDs();

	/// Does order of quest execution matter?
	/// E.g "Get to the Mordor"->"Destroy the Ring" => true
	/// E.g "Find 100 wood"->"Find 50 iron" => false
	virtual bool areSubquestsOrdered() { return true; }

	//--------------------------------------Signals-------------------------------------//
	/// Is signaled on quest progress.
	Signal <void (QuestProgressInfo) > signalProgress;

	/// Is signaled when quest is completed.
	Signal <void (QuestCompletionInfo) > signalCompletion;
	
	
	//-------------------------------Game Event Listeners-------------------------------//
	/// If the quest is a quest-container then it should signal its progress when
	/// any of its subquests is completed.
	EVENT_LISTENER(QuestCompletionInfo);

protected:
	std::vector<Quest *> _subquests;
	bool _bIsCompleted, _bIsStarted, _bIsExplicit;
	bool _bDebug;
	int _iCountOfCompletedSubquests;

	/// In this method subquest starts its execution.
	/// Is called when "Start"-button is tapped.
	/// Usable for a single quest and a subquest.
	virtual void onSetStarted() {}
	
	/// Start listening to game events.
	/// Is called on startup when loading all quests.
	/// Usable for a container quest or a single quest.
	virtual void onSetPassive() {}

	/// What should be done if player decided to skip this quest.
	/// @param rsReason. If skipping quest was rejected (due to lack of money), than rsReason contains the reason, why it was rejected.
	/// return. true - if quest was skipped, false - otherwise.
	virtual bool onSetSkipped(string & rsReason) { rsReason = "onSetSkipped() was not overrided!"; return false; }
	
	//-------------------------------------SubQuests-------------------------------------//
	
	/// Architecture hack: automatically fire global events when emmiting signals.
	void onQuestProgress(QuestProgressInfo questProgressInfo);
	void onQuestCompletion(QuestCompletionInfo questCompletionInfo);
	Slot<void(QuestProgressInfo)> _questProgressSlot;
	Slot<void(QuestCompletionInfo)> _questCompletionSlot;
};

#endif //QUEST_H
