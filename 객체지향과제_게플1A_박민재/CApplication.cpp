#include <stdio.h>

#include "CApplication.h"
#include "glc2d.h"
#include "SceneBegin.h"


extern CApplication g_App;

int RenderApp()
{
	g_App.Render();
	//printf("렌더링 중...\n");
	return 0;
}

int UpdateApp()
{
	g_App.Update();
	//printf("업데이트 중...\n");
	return 0;
}

int CApplication::Init()
{
	g2_InitSdk();
	
	g2_SetFrameMove(UpdateApp);
	g2_SetRender(RenderApp);
	
	// window 생성.
	g2_CreateWin(m_winPos.x, m_winPos.y, m_winSize.cx, m_winSize.cy, m_winName.c_str());

	m_Resource.fontTitle = g2_FontCreate("Arial", 80, 0);
	m_Resource.fontMenu = g2_FontCreate("Arial", 50, 0);
	m_Resource.fontNormal = g2_FontCreate("Arial", 20, 0);

	m_pScene = new SceneBegin();
	m_pScene->Init();
	
	return 0;
}

int CApplication::Update()
{
	if (m_pScene) // 씬이 존재하면 업데이트
	{
		m_pScene->Update(); // 씬 업데이트
	}

	return 0;
}

int CApplication::Render()
{
	if (m_pScene != nullptr)
	{
		m_pScene->Render(*this);
	}

	return 0;
}

int CApplication::Destroy()
{
	
	if(m_pScene)
	{
		m_pScene->Destroy();
		delete m_pScene;
		m_pScene = nullptr;
	}

	// 마무리, 윈도우 해제
	g2_DestroyWin();

	return 0;
}

int CApplication::InitSdk()
{
	return 0;
}

const GameResource& CApplication::GetResource() const
{
	return m_Resource;
}

int CApplication::ChangeScene(CScene* pScene)
{
	if (m_pScene != nullptr) // 기존 씬 제거
	{
		m_pScene->Destroy();
		delete m_pScene;
		m_pScene = nullptr;
	}

	m_pScene = pScene; // 새로운 씬 등록

	if (m_pScene != nullptr) // 새로운 씬 초기화
	{
		m_pScene->Init();
	}

	return 0;	
}