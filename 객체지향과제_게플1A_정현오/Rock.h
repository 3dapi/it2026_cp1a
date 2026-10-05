#pragma once
#include "Character.h"
#include <random>

class Rock : public Character
{
public:
    int Init() override;
    int Update(float deltaTime) override;
    int Render() override;
    int Destroy() override;

protected:
    int m_txRock{ -1 };
};

