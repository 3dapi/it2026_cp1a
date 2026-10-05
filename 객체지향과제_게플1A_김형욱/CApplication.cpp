#include "glc2d.h"
#include "CApplication.h"

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
	BG_sound = g2_SoundLoad("resource/sound/bgm/background.wav");
	UI_click_sound = g2_SoundLoad("resource/sound/interaction/ui_click.wav");
	g2_SoundPlay(BG_sound, true);
	Paddle_hit_sound = g2_SoundLoad("resource/sound/interaction/paddle_hit.wav");

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
void CApplication::PlayUIClick()
{
	g2_SoundPlay(UI_click_sound, false);
}

int CApplication::Destroy()
{
	m_sceneBegin.Destroy();
	g2_SoundStop(BG_sound);
	g2_SoundRelease(BG_sound);
	g2_SoundRelease(UI_click_sound);
	g2_DestroyWin();
	g2_SoundRelease(Paddle_hit_sound);

	// 윈도우 해제
	g2_DestroyWin();

	return 0;
}
void CApplication::ShowResult(int score)
{
	// RESULT Scene에 점수 전달
	m_sceneResult.SetScore(score);

	// RESULT Scene으로 이동
	ChangeScene(SceneType::RESULT);
}

SIZE CApplication::GetWinSize()
{
	return SIZE();
}

int CApplication::InitSdk()
{
	// SDK 초기화
	g2_InitSdk();	

	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);

	// 불러오기
	g2_CreateWin(m_winPos.x, m_winPos.y,
				m_winSize.cx, m_winSize.cy,
				m_winName.c_str());

	return 0;
}

void CApplication::PlayPaddleHit()
{
	g2_SoundPlay(Paddle_hit_sound, false);
}