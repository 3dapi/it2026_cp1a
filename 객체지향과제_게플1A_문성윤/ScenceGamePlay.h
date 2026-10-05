#pragma once
#include "GameUI.h"
#include "Player.h"
#include "StoryProgress.h"
#include "BattleProgress.h"

class ScenceGamePlay
{
  public:
    int Init();
    void Reset();
    // True only after the complete ending dialogue, requesting the result scene.
    bool Update(const GameUI& ui, Player& player);
    void Render(const GameUI& ui, const Player& player);
    int Destroy();
    const StoryProgress& GetProgress() const { return m_story; }
    EndingKind GetEnding() const { return m_story.Ending(); }
    bool IsBattleMusic() const
    {
        return m_stage == Stage::Battle && m_battle.EnemyHP() > 0 && !m_battle.IsFinished();
    }

  private:
    enum class Stage { Story, Battle, Ending, Complete };
    enum class Overlay { None, Items, Pause };
    void RenderStory(const GameUI& ui, const Player& player);
    void RenderBattle(const GameUI& ui, const Player& player);
    void RenderStatus(const GameUI& ui, const Player& player, const char* title, bool classroom);
    void RenderDialogue(const GameUI& ui, const char* speaker, const char* text, bool choosing);
    void RenderOverlay(const GameUI& ui) const;
    void PlayBattleSound() const;
    bool UpdateOverlay(const GameUI& ui);
    Stage m_stage = Stage::Story;
    Overlay m_overlay = Overlay::None;
    BattleProgress m_battle;
    StoryProgress m_story;
    int m_choiceFocus = 0, m_menuFocus = 0;
    int m_attackSound = -1, m_healSound = -1;
    int m_background = -1, m_classroom = -1, m_character = -1, m_shadow = -1;
};
