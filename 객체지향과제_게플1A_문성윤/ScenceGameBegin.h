#pragma once
#include "GameUI.h"

class ScenceGameBegin
{
  public:
    int Init();
    bool Update(const GameUI &ui);
    void Render(const GameUI &ui);
    int Destroy();

  private:
    int m_background = -1;
};
