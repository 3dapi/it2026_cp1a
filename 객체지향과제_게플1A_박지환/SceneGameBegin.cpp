#include "SceneGameBegin.h"
#include "CApplication.h"
#include "glc2d.h"
#include <windows.h>

int SceneGameBegin::Init()
{
	// texture
	this->m_txTitle = g2_TextureLoad("Resource/Texture/Title.png");

	// font
	this->m_fntMessage = g2_FontCreate("NeoµÕ±Ù¸ð", 40);

	return 0;
}

int SceneGameBegin::Destroy()
{
	g2_TextureRelease(m_txTitle);
	return 0;
}

int SceneGameBegin::Update()
{
	// start blink
	long long currentTime = g2_TimeGetTime();

	if (0 == (currentTime / BLINK_INTERVAL) % 2)
	{
		m_isTextVisible = false;
	}
	else
	{
		m_isTextVisible = true;
	}

	// scene change   
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

int SceneGameBegin::Render()
{
	// title
	g2_Draw2D(m_txTitle, nullptr, &m_titlePos);
	
	// start guide
	RECT rcStart{ 435, 410, 1000, 465 };
	if (m_isTextVisible)
	{
		g2_FontDrawText(m_fntMessage, rcStart, 0xFF444444, "%s", m_startText.c_str());
	}
	return 0;
}

