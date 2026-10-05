#pragma once
#include "Character.h"

class Player : public Character
{
public:
    int Init() override;
    int Update(float deltaTime) override;
    int Render() override;
    int Destroy() override;

public:
    void SetDead();

protected:
    int m_txPlayer{ -1 };
    int m_txDead{ -1 };

private:
    bool isDead{};
};

