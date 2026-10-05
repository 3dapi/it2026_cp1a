#pragma once
#include "YachtScore.h"

// 야추의 턴, 굴리기 횟수, 점수 기록과 점수판 표시를 관리합니다.
class YachtSystem
{
public:
    enum class ClickResult { Outside, Ignored, Recorded };
    void Init();
    void Restart();
    bool CanRoll() const { return !Finished() && m_rolls < 3; }
    void OnRolled() { if (CanRoll()) ++m_rolls; }
    bool HasRolled() const { return m_rolls > 0; }
    bool Finished() const { return m_score.Finished(); }
    ClickResult ClickScore(float x, float y, const int (&values)[5]);
    void Render(const int (&values)[5]) const;

private:
    YachtScore m_score;
    int m_rolls = 0;
    int m_font = -1;
};
