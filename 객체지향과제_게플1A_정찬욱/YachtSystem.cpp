#include "YachtSystem.h"
#include "glc2d.h"


// 점수판 그림의 실제 표시 영역은 (20,60)부터 300×600
// 원본 그림의 비율 좌표를 쓰므로 행 위치와 클릭 영역이 일치한다
namespace
{
    constexpr float BoardX = 20.0f, BoardY = 60.0f;
    constexpr float BoardW = 300.0f, BoardH = 600.0f;
    constexpr float RowTop[12] = {306,390,475,560,645,730,1040,1144,1230,1316,1402,1488};
    constexpr float RowBottom[12] = {380,465,550,635,720,804,1114,1220,1304,1390,1475,1560};
    RECT BoardRect(float left, float top, float right, float bottom)
    {
        return {static_cast<LONG>(BoardX + left / 887.0f * BoardW),
                static_cast<LONG>(BoardY + top / 1774.0f * BoardH),
                static_cast<LONG>(BoardX + right / 887.0f * BoardW),
                static_cast<LONG>(BoardY + bottom / 1774.0f * BoardH)};
    }
}


void YachtSystem::Init()
{
    Restart();
    if (m_font < 0) m_font = g2_FontCreate("Arial", 18, 0);
}


void YachtSystem::Restart()
{
    m_score.Reset();
    m_rolls = 0;
}


YachtSystem::ClickResult YachtSystem::ClickScore(float x, float y, const int (&values)[5])
{
    if (x < BoardX || x >= BoardX + BoardW) return ClickResult::Outside;
    for (int category = 0; category < YachtScore::Categories; ++category)
    {
        const RECT row = BoardRect(0, RowTop[category], 887, RowBottom[category]);
        if (y < row.top || y >= row.bottom) continue;
        if (m_rolls > 0 && !m_score.Finished())
        {
            if (m_score.Record(category, values))
            {
                m_rolls = 0;
                return ClickResult::Recorded;
            }
        }
        return ClickResult::Ignored;
    }
    return ClickResult::Outside;
}


void YachtSystem::Render(const int (&values)[5]) const
{
    if (m_font < 0) return;
    for (int category = 0; category < YachtScore::Categories; ++category)
    {
        const int score = m_score.Get(category);
        const RECT saved = BoardRect(480, RowTop[category] + 8, 647, RowBottom[category]);
        const RECT preview = BoardRect(700, RowTop[category] + 8, 870, RowBottom[category]);
        if (score >= 0) g2_FontDrawText(m_font, saved, 0xFF17202A, "%d", score);
        else
        {
            g2_FontDrawText(m_font, saved, 0xFF5B6066, "-");
            if (m_rolls > 0 && !m_score.Finished())
                g2_FontDrawText(m_font, preview, 0xFF136AA5, "%d", YachtScore::Calculate(category, values));
        }
    }

    g2_FontDrawText(m_font, BoardRect(475,100,650,190), 0xFF17202A, "Score");
    g2_FontDrawText(m_font, BoardRect(685,100,882,190), 0xFF136AA5, "Next");
    g2_FontDrawText(m_font, BoardRect(90,140,420,210), 0xFF17202A, "%d/12", m_score.Finished() ? 12 : m_score.Used()+1);
    g2_FontDrawText(m_font, BoardRect(480,825,650,890), 0xFFFFFFFF, "%d", m_score.Subtotal());
    g2_FontDrawText(m_font, BoardRect(480,905,650,970), 0xFFFFFFFF, "%d", m_score.Bonus());
    g2_FontDrawText(m_font, BoardRect(480,1620,650,1710), 0xFF17202A, "%d", m_score.Total());
    RECT status = {360, 25, 1260, 60};
    if (m_score.Finished())
        g2_FontDrawText(m_font, status, 0xFFFFFFFF, "GAME OVER  |  Total: %d  |  R: New game", m_score.Total());
    else
        g2_FontDrawText(m_font, status, 0xFFFFFFFF,
            "Turn %d/12 | Rolls %d/3 | SPACE: Roll | Click dice: Hold | Click score row: Save",
            m_score.Used()+1, m_rolls);
}
