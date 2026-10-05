#include "SceneGameResult.h"
#include "CApplication.h"

int SceneGameResult::Init()
{
	// font
	this->m_fntTitle = g2_FontCreate("NeoµÕ±Ù¸ð", 110);
	this->m_fntScore = g2_FontCreate("NeoµÕ±Ù¸ð", 70);
	this->m_fntRestart = g2_FontCreate("NeoµÕ±Ù¸ð", 40);
	this->m_fntExit = g2_FontCreate("NeoµÕ±Ù¸ð", 32);

	return 0;
}

int SceneGameResult::Destroy()
{
	
	return 0;
}

void SceneGameResult::SetScore(int score)
{
	this->m_gameScore = score;
}

int SceneGameResult::Update()
{
	// regame blink
	long long currentTime = g2_TimeGetTime();

	if (0 == (currentTime / BLINK_INTERVAL) % 2)
	{
		m_isTextVisible = false;
	}
	else
	{
		m_isTextVisible = true;
	}

	// scene change   regame quit
	const KEYCODE* pKey = g2_GetKeyboard();
	if (pKey[VK_RETURN])
	{
		g_app.ChangeScene(Scene::Play);
	}
	else if (pKey[VK_ESCAPE])
	{
		g_app.RequestQuit();
		return 0;
	}
	
	return 0;
}

int SceneGameResult::Render()
{
	RECT rcTitle	{ 390, 220, 950, 345 };
	RECT rcScore	{ 480, 380, 950, 465 };
	RECT rcRestart	{ 480, 455, 1000, 510 };
	RECT rcExit		{ 565, 495, 900, 535 };

	g2_FontDrawText( m_fntTitle, rcTitle, 0xFF8B352B, "%s", m_gameTitle.c_str());
	g2_FontDrawText(m_fntScore, rcScore, 0xFF59432F, "SCORE : %d", m_gameScore);
	if (m_isTextVisible)
	{
		g2_FontDrawText(m_fntRestart, rcRestart, 0xFF444444, "%s", m_restartText.c_str());
	}
	g2_FontDrawText(m_fntExit, rcExit, 0xFF444444, "%s", m_exitText.c_str());
	return 0;
}
