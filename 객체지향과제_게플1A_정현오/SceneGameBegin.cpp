#include "SceneGameBegin.h"

int StartGame();
int ExitGame();

int SceneGameBegin::Init()
{
	m_txBg = g2_TextureLoad("resource/texture/tex_ui/background.png");
	m_txTitle = g2_TextureLoad("resource/texture/tex_ui/titleLogo.png");
	m_startButton.Init("resource/texture/tex_ui/start.png");
	m_exitButton.Init("resource/texture/tex_ui/exit.png");

	if (m_font == -1)
	{
		m_font = g2_FontCreate("¸¼Àº °íµñ", 24);
	}

	m_startButton.transform.position = { 59.5f, 299.5f };
	m_exitButton.transform.position = { 59.5f, 399.5f };

	m_startButton.SetAction(StartGame);
	m_exitButton.SetAction(ExitGame);

	buttons = { &m_startButton , &m_exitButton };

	m_selectedIndex = 0;
	SelectButton(buttons[m_selectedIndex]);

	return 0;
}

int SceneGameBegin::Destroy()
{
	g2_TextureRelease(m_txBg);
	g2_TextureRelease(m_txTitle);
	m_selectedButton = nullptr;
	for (auto& button : buttons)
	{
		button->Destroy();
	}
	buttons.clear();

	return 0;
}

int SceneGameBegin::Update(float deltaTime)
{
	if (m_selectedButton->CanAction())
	{
		return m_selectedButton->Press();
	}

	const KEYCODE* keyboard = g2_GetKeyboard();
	if(EINPUT_DOWN == keyboard['W'])
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

int SceneGameBegin::Render()
{
	g2_Draw2D(m_txBg, nullptr);

	VEC2 titlePosition{ 15.0f, 160.0f };
	g2_Draw2D(m_txTitle, nullptr, &titlePosition);

	m_startButton.Render();
	m_exitButton.Render();

	g2_FontDrawText(m_font, { 130, 530, 250, 580 }, 0xFFFFFFFF, "w / s : ¼±ÅÃ");
	g2_FontDrawText(m_font, { 115, 560, 265, 590 }, 0xFFFFFFFF, "space : »óÈ£ÀÛ¿ë");

	return 0;
}

void SceneGameBegin::SelectButton(Button* button)
{
	if(nullptr == button || m_selectedButton == button)
	{
		return;
	}

	if(nullptr != m_selectedButton)
	{
		m_selectedButton->SetSelected(false);
	}

	m_selectedButton = button;
	m_selectedButton->SetSelected(true);
}

int StartGame()
{
	return SCENE_PLAY;
}

int ExitGame()
{
	return SCENE_QUIT;
}
