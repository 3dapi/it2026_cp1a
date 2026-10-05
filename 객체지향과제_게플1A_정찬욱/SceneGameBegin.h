#pragma once
#include "PlaySysteam.h"

class SceneGameBegin
{
public:
    int Init();
    int Update();
    int Render();
    int Destroy();

private:
    PlaySysteam m_playSysteam;
    int m_floor = -1;
    int m_basket = -1;
    int m_scoreboard = -1;
};