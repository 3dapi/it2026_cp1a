#include "CApplication.h"
#include "glc2d.h"


extern CApplication g_app;

int AppUpdate()
{
    return g_app.Update();
}

int AppRender()
{
    return g_app.Render();
}

// 생성자: 초기 씬 상태 지정
CApplication::CApplication()
    : m_nSceneState(SCENE_BEGIN)
{
}

// InitSdk(): 2D 라이브러리 초기화 및 창 등록
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

// Init(): SDK 및 각 씬 초기화
int CApplication::Init()
{
    InitSdk();

    m_sceneBegin.Init();
    m_scenePlay.Init();
    m_sceneResult.Init();

    m_nSceneState = SCENE_BEGIN;

    return 0;
}

// Update(): 현재 씬 갱신 후 전환 요청 처리
int CApplication::Update()
{
    const KEYCODE* keys = g2_GetKeyboard();

    int nextScene = m_nSceneState;

    switch (m_nSceneState)
    {
    case SCENE_BEGIN:
        nextScene = m_sceneBegin.Update(keys);
        break;

    case SCENE_PLAY:
        nextScene = m_scenePlay.Update(keys);
        break;

    case SCENE_RESULT:
        nextScene = m_sceneResult.Update(keys);
        break;
    }

    if (nextScene == -1)
    {
        PostQuitMessage(0);
        return 0;
    }

    if (nextScene != m_nSceneState)
    {
        ChangeScene(nextScene);
    }

    return 0;
}

// Render(): 현재 씬 렌더링
int CApplication::Render()
{
    g2_SetClearColor(0xFFEEE4D0);

    switch (m_nSceneState)
    {
    case SCENE_BEGIN:
        m_sceneBegin.Render();
        break;

    case SCENE_PLAY:
        m_scenePlay.Render();
        break;

    case SCENE_RESULT:
        m_sceneResult.Render();
        break;
    }

    return 0;
}

// Destroy(): 각 씬 자원 해제 후 창 종료
int CApplication::Destroy()
{
    m_sceneBegin.Destroy();
    m_scenePlay.Destroy();
    m_sceneResult.Destroy();

    g2_DestroyWin();

    return 0;
}

// ChangeScene(): 상태 값 검증 후 씬별 초기화 처리
void CApplication::ChangeScene(int nextScene)
{
    if (nextScene < SCENE_BEGIN || nextScene > SCENE_RESULT)
    {
        return;
    }

    m_nSceneState = nextScene;

    switch (m_nSceneState)
    {
    case SCENE_BEGIN:
        m_sceneBegin.Init();
        break;

    case SCENE_PLAY:
        m_scenePlay.ResetGame(); // 게임 재시작 시 말 위치/상태 초기화
        m_scenePlay.StartBgm();
        break;

    case SCENE_RESULT:
        m_sceneResult.SetPlayerWin(m_scenePlay.GetPlayerWin()); // 승패 전달
        break;
    }
}

int CApplication::GetSceneState() const
{
    return m_nSceneState;
}
