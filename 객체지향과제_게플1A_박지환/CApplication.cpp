#include "CApplication.h"
#include "glc2d.h"

CApplication g_app;

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
    InitSdk();

    m_sceneBegin.Init();
    m_scenePlay.Init();
    m_sceneResult.Init();

    return 0;
}

int CApplication::Update()
{
    switch (m_currentScene)
	{
	case Scene::Begin:
		m_sceneBegin.Update();
		break;

	case Scene::Play:
		m_scenePlay.Update();
		break;

	case Scene::Result:
		m_sceneResult.Update();
		break;

	default:
		break;
	}
        

    return 0;
}

int CApplication::Render()
{
    // 공통 배경, 차
    m_scenePlay.RenderWorld();

    switch (m_currentScene)
	{
	case Scene::Begin:
		m_sceneBegin.Render();
		break;

	case Scene::Play:
		m_scenePlay.Render();
		break;

	case Scene::Result:
		m_sceneResult.Render();
		break;

	default:
		break;
	}
    return 0;
}

int CApplication::Destroy()
{
    m_sceneResult.Destroy();
    m_scenePlay.Destroy();
    m_sceneBegin.Destroy();

    // 윈도우 해제
    g2_DestroyWin();

    return 0;
}

SIZE CApplication::GetWinSize()
{
    return m_winSize;
}

void CApplication::ChangeScene(Scene scene)
{
    if (m_currentScene == scene)
    {
        return;
    }

    // Begin -> Play, Result -> Play일땐 새 게임 시작
    switch (scene)
    {
    case Scene::Play:    
        m_scenePlay.ResetGame();
        break;
    
    case Scene::Result:
        m_sceneResult.SetScore(m_scenePlay.GetGameScore());
        break;
    
    default:
        break;
    }

    m_currentScene = scene;
}

void CApplication::RequestQuit()
{
	PostQuitMessage(0);
}

int CApplication::InitSdk()
{
    // SDK 초기화
    g2_InitSdk();

    g2_SetFrameMove(AppUpdate);
    g2_SetRender(AppRender);

    // window 생성.
    g2_CreateWin(m_winPos.x, m_winPos.y, m_winSize.cx, m_winSize.cy, m_winName.c_str());

    //배경색을 바꾼다.
    g2_SetClearColor(0xFF336699);

    return 0;
}
