#include "CApplication.h"
#include <algorithm>

extern CApplication g_app;

int AppUpdate()
{
    return g_app.Update();
}

int AppRender()
{
    return g_app.Render();
}

int CApplication::Init()
{
    m_player.Init();
    int sdk = g2_InitSdk();
    if (sdk < 0)
        return -1;
    g2_SetFrameMove(AppUpdate);
    g2_SetRender(AppRender);
    g2_SetClearColor(0xFF101722);
    // Keep the planned 4:3 layout on smaller desktop displays.
    RECT work{};
    SystemParametersInfo(SPI_GETWORKAREA, 0, &work, 0);
    int height = (std::min)(900, int(work.bottom - work.top - 100));
    height = (std::max)(360, height);
    int width = height * 4 / 3;
    if (g2_CreateWin(work.left + 30, work.top + 30, width, height, "The Last Clue", true) < 0)
        return -1;
    g2_SetStateShow(false);
    m_fontLoaded = AddFontResourceExW(L"resource/font/에이투지체-6SemiBold.ttf", FR_PRIVATE, nullptr) > 0;
    if (!m_fontLoaded)
    {
        MessageBoxW(g2_GetHwnd(), L"Cannot load resource/font/에이투지체-6SemiBold.ttf", L"Font error", MB_OK | MB_ICONERROR);
        return -1;
    }
    m_storyMusic = g2_SoundLoad("resource/sound/bgm_story.mp3");
    m_battleMusic = g2_SoundLoad("resource/sound/bgm_battle.mp3");
    if (m_battleMusic < 0 || m_storyMusic < 0 || m_ui.Init() < 0 || m_sceneBegin.Init() < 0 || m_scenePlay.Init() < 0 || m_sceneResult.Init() < 0)
    {
        MessageBoxW(g2_GetHwnd(), L"게임 리소스를 불러오지 못했습니다. 실행 파일 옆 resource 폴더를 확인하세요.",
                    L"리소스 오류", MB_OK | MB_ICONERROR);
        return -1;
    }
    g2_SoundPlay(m_storyMusic, true);
    return 0;
}


void CApplication::StartGame()
{
    m_player.Init();
    m_scenePlay.Reset();
    m_sceneResult.SetResult(EndingKind::None, 0, 0);
    m_scene = Scene::Play;
}

int CApplication::Update()
{
    m_ui.Update();
    switch (m_scene)
    {
    case Scene::Begin:
        if (m_sceneBegin.Update(m_ui)) StartGame();
        break;
    case Scene::Play:
        if (m_scenePlay.Update(m_ui, m_player))
        {
            m_sceneResult.SetResult(m_scenePlay.GetEnding(), m_player.GetScore(), m_scenePlay.GetProgress().ClueCount());
            m_scene = Scene::Result;
        }
        break;
    case Scene::Result:
        if (m_sceneResult.Update(m_ui)) StartGame();
        break;
    }
    const bool battleMusic = m_scene == Scene::Play && m_scenePlay.IsBattleMusic();
    if (battleMusic != m_playingBattleMusic)
    {
        g2_SoundStop(m_playingBattleMusic ? m_battleMusic : m_storyMusic);
        g2_SoundPlay(battleMusic ? m_battleMusic : m_storyMusic, true);
        m_playingBattleMusic = battleMusic;
    }
    return 0;
}

int CApplication::Render()
{
    switch (m_scene)
    {
    case Scene::Begin: m_sceneBegin.Render(m_ui); break;
    case Scene::Play: m_scenePlay.Render(m_ui, m_player); break;
    case Scene::Result: m_sceneResult.Render(m_ui); break;
    }
    return 0;
}

int CApplication::Destroy()
{
    if (m_battleMusic >= 0)
    {
        g2_SoundStop(m_battleMusic);
        g2_SoundRelease(m_battleMusic);
        m_battleMusic = -1;
    }
    if (m_storyMusic >= 0)
    {
        g2_SoundStop(m_storyMusic);
        g2_SoundRelease(m_storyMusic);
        m_storyMusic = -1;
    }
    m_sceneResult.Destroy();
    m_scenePlay.Destroy();
    m_sceneBegin.Destroy();
    m_ui.Destroy();
    g2_DestroyWin();
    if (m_fontLoaded)
    {
        RemoveFontResourceExW(L"resource/font/에이투지체-6SemiBold.ttf", FR_PRIVATE, nullptr);
        m_fontLoaded = false;
    }
    return 0;
}
