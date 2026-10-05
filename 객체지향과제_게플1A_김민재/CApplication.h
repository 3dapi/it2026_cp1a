#pragma once

#include <windows.h>
#include <string>

#include "SceneBegin.h"
#include "ScenePlay.h"
#include "SceneResult.h"

enum class SceneType
{
    BEGIN,
    PLAY,
    RESULT
};

class CApplication
{
public:
    bool Init();
    int Update();
    int Render();
    int Destroy();

    void ChangeScene(SceneType scene);
    void ShowResult(bool clear);

public:
    SIZE GetWinSize();

protected:
    int InitSdk();

protected:
    POINT m_winPos{ 100, 50 };
    SIZE m_winSize{ 1774, 887 };
    std::string m_winName = "JUMP RUN";

    SceneType m_scene = SceneType::BEGIN;

    SceneBegin m_sceneBegin;
    ScenePlay m_scenePlay;
    SceneResult m_sceneResult;

protected:
    int BG_sound = -1;

public:
    int m_score = 0;
};