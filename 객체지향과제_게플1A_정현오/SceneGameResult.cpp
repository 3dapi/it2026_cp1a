#include "SceneGameResult.h"

int RetryGame();
int ReturnLobby();

int SceneGameResult::Init()
{
	m_txBg = g2_TextureLoad("resource/texture/tex_ui/background.png");
	m_txResultBg = g2_TextureLoad("resource/texture/tex_ui/resultBoard.png");
	if (m_gameOverFont == -1)
	{
		m_gameOverFont = g2_FontCreate("¸¼Àº °íµñ", 50);
	}

	if (m_scoreFont == -1)
	{
		m_scoreFont = g2_FontCreate("¸¼Àº °íµñ", 40);
	}

	m_retryButton.Init("resource/texture/tex_ui/retry.png");
	m_returnButton.Init("resource/texture/tex_ui/return.png");

	m_retryButton.transform.position = { 59.5f, 339.5f };
	m_returnButton.transform.position = { 59.5f, 419.5f };

	m_retryButton.SetAction(RetryGame);
	m_returnButton.SetAction(ReturnLobby);

	buttons = { &m_retryButton , &m_returnButton };
	
	m_selectedIndex = 0;
	SelectButton(buttons[m_selectedIndex]);

	string scoreText = std::to_string(score);

	LONG digitWidth = 19;
	LONG textWidth = static_cast<LONG>(scoreText.length()) * digitWidth;
	startX = 180 - textWidth / 2;

	return 0;
}

int SceneGameResult::Update(float deltaTime)
{
	if (m_selectedButton->CanAction())
	{
		return m_selectedButton->Press();
	}

	const KEYCODE* keyboard = g2_GetKeyboard();
	if (EINPUT_DOWN == keyboard['W'])
	{
		if (0 < m_selectedIndex)
		{
			--m_selectedIndex;
		}
		SelectButton(buttons[m_selectedIndex]);
	}
	else if (EINPUT_DOWN == keyboard['S'])
	{
		if (buttons.size() > m_selectedIndex + 1)
		{
			++m_selectedIndex;
		}
		SelectButton(buttons[m_selectedIndex]);
	}

	if (EINPUT_DOWN == keyboard[VK_SPACE])
	{
		m_selectedButton->SetPressed(true);
	}

	return SCENE_KEEP;
}

int SceneGameResult::Render()
{
	g2_Draw2D(m_txBg, nullptr, nullptr, nullptr, nullptr, 0.0f, 0xFFC0C0C0);

	VEC2 resultBgPosition{ 8, 70 };
	g2_Draw2D(m_txResultBg, nullptr, &resultBgPosition);

	g2_FontDrawText(m_gameOverFont, { 76, 140, 300, 300 }, 0xFFFFFFFF, "Game Over!");
	g2_FontDrawText(m_scoreFont, { 120, 220, 300, 300 }, 0xFFFFFFFF, "ÃÖÁ¾ Á¡¼ö");
	g2_FontDrawText(m_scoreFont, { startX, 270, 300, 350 }, 0xFFFFFFFF, "%d", score);
	m_retryButton.Render();
	m_returnButton.Render();

	return 0;
}

int SceneGameResult::Destroy()
{
	g2_TextureRelease(m_txBg);
	g2_TextureRelease(m_txResultBg);
	m_selectedButton = nullptr;
	for (auto& button : buttons)
	{
		button->Destroy();
	}
	buttons.clear();

	return 0;
}

void SceneGameResult::SetScore(int value)
{
	score = value;
}

void SceneGameResult::SelectButton(Button* button)
{
	if (nullptr == button || m_selectedButton == button)
	{
		return;
	}

	if (nullptr != m_selectedButton)
	{
		m_selectedButton->SetSelected(false);
	}

	m_selectedButton = button;
	m_selectedButton->SetSelected(true);
}

int RetryGame()
{
	return SCENE_PLAY;
}

int ReturnLobby()
{
	return SCENE_BEGIN;
}