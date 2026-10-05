#include <iostream>
#include <Windows.h>
#include "glc2d.h"
#include "SceneGameStart.h"
#include "CApplication.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Entity.h"
#include "Obstacle.h"
#include "Background.h"
#include "Image.h"
#include "TextureManager.h"

extern CApplication g_app;
extern GameManager g_gameManager;

FLOAT scaleX;
FLOAT scaleY;

int BackGroundScaling(Background* background)
{
	int nTexW{ 0 };
	int nTexH{ 0 };

	int nTx = background->m_image.texture;
	nTexW = g2_TextureWidth(nTx);
	nTexH = g2_TextureHeight(nTx);

	scaleX = (FLOAT)g_app.m_winSize.cx / nTexW;
	scaleY = (FLOAT)g_app.m_winSize.cy / nTexH;

	return 0;
}

int SceneGameStart::Init()
{
	m_background = g_gameManager.CreateBackground(BackgroundType::SCREEN_PLAY);
	g_gameManager.m_currentBackgroundType = BackgroundType::SCREEN_PLAY;
	m_background->Init(TextureType::BACKGROUND);

	m_gameTitle = g_gameManager.CreateObject<Image>();
	m_gameTitle->Init(TextureType::UI_TITLE_GAMEMAINMENU);
	VEC2 objPos = { 310, 10 };
	m_gameTitle->SetPosition(objPos);

	m_guidTextImage = g_gameManager.CreateObject<Image>();
	m_guidTextImage->Init(TextureType::UI_GUIDTEXT);
	objPos = { 340, 300 };
	m_guidTextImage->SetPosition(objPos);

	VEC2 scaling = { 3, 3 };
	m_guidTextImage->SetScaling(scaling);

	BackGroundScaling(m_background);

	VEC2 backgroundScale(scaleX, scaleY);
	m_background->SetScaling(backgroundScale);

	VEC2 titleScale(2, 2);
	m_gameTitle->SetScaling(titleScale);

	return 0;
}

int SceneGameStart::Update(float deltaTime)
{
	g_gameManager.UpdateAll(deltaTime);

	const KEYCODE* pKeyboard = g2_GetKeyboard();

	if (pKeyboard[VK_SPACE])
	{
		g_app.SignChangeScene(SceneType::SCENEPLAY);
	}

	return 0;
}

int SceneGameStart::Render()
{
	//VEC2 startButtonScale(1, 1);
	//startButton->SetScaling(startButtonScale);

	g_gameManager.RenderAll();

	return 0;
}

int SceneGameStart::Destroy()
{
	g_gameManager.ClearAll();

	return 0;
}