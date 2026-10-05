#pragma once
#include "GameUI.h"
#include "Player.h"
#include "ScenceGameBegin.h"
#include "ScenceGamePlay.h"
#include "ScenceGameResult.h"

class CApplication
{
  public:
    int Init();
    int Update();
    int Render();
    int Destroy();

  private:
    enum class Scene
    {
        Begin,
        Play,
        Result
    };
    void StartGame();
    ScenceGameResult m_sceneResult;
    Scene m_scene = Scene::Begin;
    ScenceGameBegin m_sceneBegin;
    ScenceGamePlay m_scenePlay;
    GameUI m_ui;
    Player m_player;
    int m_storyMusic = -1;
    int m_battleMusic = -1;
    bool m_playingBattleMusic = false;
    bool m_fontLoaded = false;
};
