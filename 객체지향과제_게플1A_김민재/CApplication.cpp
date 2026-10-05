#include <stdio.h>

#include "glc2d.h"
#include "CApplication.h"

CApplication g_app;

int AppUpdate()
{
    return g_app.Update();
}

int AppRender()
{
    return g_app.Render();
}

bool CApplication::Init()
{
    InitSdk();

    m_sceneBegin.Init();

    BG_sound = g2_SoundLoad(
        "resource/sound/bgm/background.wav"
    );

    g2_SoundPlay(BG_sound, true);

    return true;
}

int CApplication::Update()
{
    if (m_scene == SceneType::BEGIN)
    {
        m_sceneBegin.Update();
    }
    else if (m_scene == SceneType::PLAY)
    {
        m_scenePlay.Update();
    }
    else if (m_scene == SceneType::RESULT)
    {
        m_sceneResult.Update();
    }

    return 0;
}

int CApplication::Render()
{
    if (m_scene == SceneType::BEGIN)
    {
        m_sceneBegin.Render();
    }
    else if (m_scene == SceneType::PLAY)
    {
        m_scenePlay.Render();
    }
    else if (m_scene == SceneType::RESULT)
    {
        m_sceneResult.Render();
    }

    return 0;
}

void CApplication::ChangeScene(SceneType scene)
{
    if (m_scene == SceneType::BEGIN)
    {
        m_sceneBegin.Destroy();
    }
    else if (m_scene == SceneType::PLAY)
    {
        m_scenePlay.Destroy();
    }
    else if (m_scene == SceneType::RESULT)
    {
        m_sceneResult.Destroy();
    }

    m_scene = scene;

    if (m_scene == SceneType::BEGIN)
    {
        m_sceneBegin.Init();
    }
    else if (m_scene == SceneType::PLAY)
    {
        m_scenePlay.Init();
    }
    else if (m_scene == SceneType::RESULT)
    {
        m_sceneResult.Init();
    }
}

void CApplication::ShowResult(bool clear)
{
    m_sceneResult.SetResult(clear);
    ChangeScene(SceneType::RESULT);
}

int CApplication::Destroy()
{
    if (m_scene == SceneType::BEGIN)
    {
        m_sceneBegin.Destroy();
    }
    else if (m_scene == SceneType::PLAY)
    {
        m_scenePlay.Destroy();
    }
    else if (m_scene == SceneType::RESULT)
    {
        m_sceneResult.Destroy();
    }

    g2_SoundStop(BG_sound);
    g2_SoundRelease(BG_sound);

    g2_DestroyWin();

    return 0;
}

SIZE CApplication::GetWinSize()
{
    return m_winSize;
}

int CApplication::InitSdk()
{
    g2_InitSdk();

    g2_SetFrameMove(AppUpdate);
    g2_SetRender(AppRender);

    g2_CreateWin(
        m_winPos.x,
        m_winPos.y,
        m_winSize.cx,
        m_winSize.cy,
        m_winName.c_str()
    );

    return 0;
}