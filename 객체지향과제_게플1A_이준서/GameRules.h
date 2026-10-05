#pragma once
#include <algorithm>

struct GameRules
{
    int m_score = 0;
    int m_lives = 3;
    float m_elapsedTime = 0;
    float m_remainingTime = 3;
    float m_timeLimit = 3;

    void NextRound()
    {
        m_timeLimit = (std::max)(0.65f, 3.0f - m_elapsedTime * 0.02f);
        m_remainingTime = m_timeLimit;
    }
    void Answer(bool correct)
    {
        if (m_lives <= 0) return;
        if (correct) ++m_score;
        else --m_lives;
    }
    bool Tick(float deltaTime)
    {
        m_elapsedTime += deltaTime;
        m_remainingTime = (std::max)(0.0f, m_remainingTime - deltaTime);
        return m_remainingTime <= 0;
    }
};
