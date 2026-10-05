#pragma once
#include "GameUI.h"
#include "StoryData.h"

class ScenceGameResult
{
  public:
    int Init();
    void SetResult(EndingKind ending, int score, int clues);
    bool Update(const GameUI& ui);
    void Render(const GameUI& ui);
    int Destroy();

  private:
    EndingKind m_ending = EndingKind::None;
    int m_score = 0, m_clues = 0, m_focus = 0;
    int m_background = -1;
};
