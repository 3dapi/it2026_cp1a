#pragma once
#include <random>
#include "GameRules.h"

class SceneGamePlay
{
public:
    void Init();
    void Render();
    void Update(float deltaTime);
    GameRules m_rules;
private:
    void NextRound();
    void Resolve(bool correct);
    std::mt19937 m_random{ std::random_device{}() };
    char m_targetKey = 'A';
    float m_feedbackTime = 0;
    bool m_correct = false;
};
