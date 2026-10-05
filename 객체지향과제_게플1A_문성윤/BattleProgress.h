#pragma once
#include "Player.h"
#include "StoryData.h"
#include <string>
#include <vector>

// Combat and its dialogue are independent of the window, rendering and audio.
class BattleProgress
{
  public:
    enum class Command { Attack, Defend, Heal, Clue };
    enum class Phase { Inactive, Opening, Choosing, PlayerResult, EnemyResult, Interlude, Forecast, Retry, Victory, Won, Lost };
    enum class Sound { None, Attack, Heal };
    void Reset();
    void Start(bool photo, bool record);
    bool CanUse(Command command, const Player& player) const;
    bool Choose(Command command, Player& player);
    bool Advance(Player& player);
    Phase GetPhase() const { return m_phase; }
    Sound GetSound() const { return m_sound; }
    int EnemyHP() const { return m_enemyHP; }
    int ExpectedDamage() const { return m_strong ? 25 : 15; }
    int Potions() const { return m_potions; }
    int Turn() const { return m_turn; }
    bool ClueUsed() const { return m_clueUsed; }
    bool IsActive() const { return m_phase != Phase::Inactive; }
    bool IsFinished() const { return m_phase == Phase::Won || m_phase == Phase::Lost; }
    const char* Speaker() const;
    const char* Message() const;
    StoryVisual Visual() const;

  private:
    struct DialogueLine { std::string speaker, text; StoryVisual visual; };
    void ResetAttempt();
    void BeginLines(Phase phase);
    void Append(BattleDialogue dialogue, const char* replaceId = nullptr, const char* replacement = nullptr);
    void NextTurn();
    void Relations(const Player& player);
    Phase m_phase = Phase::Inactive;
    Sound m_sound = Sound::None;
    int m_enemyHP = 100, m_potions = 1, m_turn = 1;
    bool m_photo = false, m_record = false;
    bool m_strong = false, m_defending = false, m_clueUsed = false;
    bool m_lowHPShown = false, m_clueShown = false, m_weakEnemyShown = false;
    std::vector<DialogueLine> m_lines;
    std::size_t m_page = 0;
};
