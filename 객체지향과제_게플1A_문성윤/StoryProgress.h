#pragma once
#include "Player.h"
#include "StoryData.h"
#include <cstddef>
#include <cstdint>

// Narrative state is independent of rendering, audio and window input.
class StoryProgress
{
  public:
    void Reset();
    bool Advance(Player& player);
    void BeginEnding(bool victory, Player& player);
    EndingKind Ending() const { return m_ending; }
    bool Choose(int option, Player& player);
    const StorySection& Section() const;
    const StoryLine& Line() const;
    bool IsChoosing() const { return m_choosing; }
    bool IsComplete() const { return m_complete; }
    bool HasKey() const { return m_hasKey; }
    bool HasPhoto() const { return m_hasPhoto; }
    bool HasRecord() const { return m_hasRecord; }
    int ClueCount() const { return int(m_hasPhoto) + int(m_hasRecord); }

  private:
    void Enter(StoryBlock block, Player& player);
    void FindVisibleLine(Player& player);
    bool Matches(StoryCondition condition) const;
    void Apply(StoryEvent event, Player& player);

    EndingKind m_ending = EndingKind::None;
    StoryBlock m_block = StoryBlock::Prologue;
    std::size_t m_line = 0;
    bool m_choosing = false;
    bool m_complete = false;
    bool m_hasKey = false;
    bool m_hasPhoto = false;
    bool m_hasRecord = false;
    std::uint32_t m_appliedEvents = 0;
};
