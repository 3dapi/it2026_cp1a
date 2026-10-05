#include "CApplication.h"

void SceneGamePlay::Init()
{
    m_rules = GameRules{};
    m_feedbackTime = 0;
    m_correct = false;
    NextRound();
}

void SceneGamePlay::NextRound()
{
    m_targetKey = "ASDF"[std::uniform_int_distribution<int>(0, 3)(m_random)];
    m_rules.NextRound();
}

void SceneGamePlay::Resolve(bool correct)
{
    m_rules.Answer(correct);
    m_correct = correct;
    m_feedbackTime = 0.3f;
    g_app.PlaySound(correct ? CorrectSound : WrongSound);
}

void SceneGamePlay::Update(float deltaTime)
{
    if (m_feedbackTime > 0)
    {
        m_feedbackTime -= deltaTime;
        if (m_feedbackTime <= 0)
        {
            if (m_rules.m_lives == 0) g_app.FinishGame();
            else NextRound();
        }
        return;
    }
    if (m_rules.Tick(deltaTime))
    {
        Resolve(false);
        return;
    }
    int count = 0;
    char key = 0;
    for (char candidate : { 'A', 'S', 'D', 'F' })
    {
        if (g_app.Pressed(candidate)) { ++count; key = candidate; }
    }
    if (count > 0) Resolve(count == 1 && key == m_targetKey);
}

void SceneGamePlay::Render()
{
    g_app.DrawImage(BackgroundImage, 0, 0, 1280, 720, 0xFF777777);
    const bool feedback = m_feedbackTime > 0;
    const DWORD tint = feedback && !m_correct ? 0xFFFF6666 : 0xFFFFFFFF;
    g_app.DrawImage(feedback && m_correct ? ZombieHit : ZombieIdle, 384, 150, 512, 512, tint);
    g2_FontDrawText(g_app.m_largeFont, { 35, 20, 500, 95 }, 0xFFFFFFFF, "SCORE: %d", m_rules.m_score);
    for (int i = 0; i < 3; ++i)
        g_app.DrawImage(i < m_rules.m_lives ? HeartFull : HeartEmpty, 1060.0f + i * 65, 35, 51, 51);
    if (feedback)
        g2_FontDrawText(g_app.m_largeFont, { 500, 90, 1000, 160 }, m_correct ? 0xFFBBFF77 : 0xFFFF7777,
            m_correct ? "GOOD!" : "MISS!");
    else
        g2_FontDrawText(g_app.m_keyFont, { 603, 72, 740, 190 }, 0xFFFFFF88, "%c", m_targetKey);
    const int filled = static_cast<int>(20 * m_rules.m_remainingTime / m_rules.m_timeLimit);
    char bar[21];
    for (int i = 0; i < 20; ++i) bar[i] = i < filled ? '|' : '.';
    bar[20] = '\0';
    g2_FontDrawText(g_app.m_font, { 470, 610, 1100, 655 }, 0xFFFFFF88, "TIME: %.1f   %s", m_rules.m_remainingTime, bar);
    g2_FontDrawText(g_app.m_font, { 355, 665, 1200, 715 }, 0xFFFFFFFF, "A / S / D / F : Attack      ESC : Exit");
}
