#include <iostream>
#include <Windows.h>
#include "glc2d.h"
#include "SceneGameResult.h"
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

int SceneGameResult::Init()
{
	m_scoreFont = g2_FontCreate("Arial", 30, 0);

	return 0;
}

int SceneGameResult::Update(float deltaTime)
{
	g_gameManager.UpdateAll(deltaTime);

	m_gameoverTitle = g_gameManager.CreateObject<Image>();
	m_gameoverTitle->Init(TextureType::UI_TITLE_GAMEOVER);
	VEC2 objPos = { 274, 10 };
	m_gameoverTitle->SetPosition(objPos);

	VEC2 scaling = { 10, 10 };
	m_gameoverTitle->SetScaling(scaling);

	m_scoreText = g_gameManager.CreateObject<Image>();
	m_scoreText->Init(TextureType::UI_TEXT_SCORE);
	objPos = { 200, 200 };
	m_scoreText->SetPosition(objPos);

	scaling = { 10, 10 };
	m_scoreText->SetScaling(scaling);

	m_guidTextImage = g_gameManager.CreateObject<Image>();
	m_guidTextImage->Init(TextureType::UI_GUIDTEXT);
	objPos = { 340, 300 };
	m_guidTextImage->SetPosition(objPos);

	scaling = { 3, 3 };
	m_guidTextImage->SetScaling(scaling);

	const KEYCODE* pKeyboard = g2_GetKeyboard();

	if (pKeyboard[VK_SPACE])
	{
		g_app.SignChangeScene(SceneType::SCENEPLAY);
	}

	return 0;
}

int SceneGameResult::Render()
{
	g_gameManager.RenderAll();

	RECT scoreRect = { 600, 200, 800, 300 };
	g2_FontDrawText(m_scoreFont, scoreRect, 0xFF000000, "%d", g_gameManager.m_score);

	return 0;
}

int SceneGameResult::Destroy()
{
	g_gameManager.ClearAll();

	return 0;
}