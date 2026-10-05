#pragma once
#include <vector>

enum class StoryBlock
{
    Prologue, Meeting, TrustA, TrustB, Locker, OpenLocker, SkipLocker,
    Warning, Floor, SafeFloor, RiskyFloor, ClassroomEntrance,
    Classroom, ReadRecord, LeaveRecord, Truth, SupportA, SupportB,
    Confrontation, AfterBattle, GoodEnding, NormalEnding, MissingCluesEnding, LifeLostEnding, Count
};

enum class StoryVisual { Empty, Seoyeon, Both };
enum class StoryCondition { Always, HasPhoto, NoPhoto, HasRecord, NoRecord };
enum class StoryEvent
{
    None, Key, LockerOpened, Photo, SafeFloor, FloorDamage, Record,
    FirstEmpathy, SecondEmpathy
};
enum class StoryChoice { None, FirstTrust, Locker, Floor, Record, SecondTrust };

struct StoryLine
{
    const char* id;
    const char* speaker;
    const char* text;
    StoryVisual visual;
    StoryCondition condition = StoryCondition::Always;
    StoryEvent event = StoryEvent::None;
};

struct StorySection
{
    const char* title;
    int chapter;
    std::vector<StoryLine> lines;
    StoryBlock next;
    StoryChoice choice = StoryChoice::None;
    const char* options[2] = {"", ""};
    StoryBlock branches[2] = {StoryBlock::Count, StoryBlock::Count};
};

const StorySection& GetStorySection(StoryBlock block);



enum class EndingKind { None, Good, Normal, MissingClues, LifeLost };
enum class BattleDialogue { Opening, Attack, Defend, Heal, Photo, Record, BothClues, NormalForecast, StrongForecast, NormalHit, StrongHit, BlockedHit, LowHP, ClueRelation, WeakEnemy, Retry, Victory, Count };
const std::vector<StoryLine>& GetBattleDialogue(BattleDialogue dialogue);
