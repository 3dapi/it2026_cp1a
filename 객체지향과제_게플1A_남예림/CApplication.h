#pragma once

#include <Windows.h>
#include <string>

#include "SceneGameBegin.h"
#include "SceneGamePlay.h"
#include "SceneGameResult.h"

enum ESceneState
{
    SCENE_BEGIN = 0,
    SCENE_PLAY = 1,
    SCENE_RESULT = 2
};

class CApplication
{
public:
    CApplication();

    int Init();
    int Update();
    int Render();
    int Destroy();

    void ChangeScene(int nextScene);

    int GetSceneState() const;

private:
    int InitSdk();

private:
    POINT m_winPos{ 50, 50 };
    SIZE m_winSize{ 800, 600 };

    std::string m_winName = "26085007_NamYerim_STEPPING STONES";

    int m_nSceneState = SCENE_BEGIN;

    SceneGameBegin m_sceneBegin;
    SceneGamePlay m_scenePlay;
    SceneGameResult m_sceneResult;
};
