#ifndef QUESTIDS_H
#define QUESTIDS_H

class questGenerator;

typedef unsigned int QuestID;

enum QuestIDs : QuestID
{
	kMovementTutorialID = 1,
	kObjectOnMapInteractionTutorialID = 2,
	kInventoryTutorialID = 3,
	kBattleTutorialID = 4,
	kDecorationTutorialID = 5,
	kDiggingTutorialID = 6,
	kRoomBuildingTutorialID = 7,
	kTrapBuildingTutorialID = 8,
	kActionTutorialID = 9,
	kEscapeTutorialID = 10,
	kTrapAvoidTutorialID = 11,
	kFindDoorTutorialID = 12,
	kKillEnemy1ID = 14,
	kCollectItem1ID = 15,
	kCollectItem11ID = 16,
	kCollectItem12ID = 17,
	kCollectItem13ID = 18,
	kCollectItem14ID = 19
};

#endif //QUESTIDS_H