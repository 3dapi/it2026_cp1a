#include "ScenePlay.h"
#include "SceneBegin.h"
#include "SceneScore.h"
#include "glc2d.h"
#include "CApplication.h"

extern CApplication g_app;

int SceneBegin::Init()
{
	g2_SetWindowTitle("사과 피하기");

	//
	{
		this->background01 = g2_TextureLoad("Resources/background01.png");
		this->playButton01 = g2_TextureLoad("Resources/playButton01.png");
		this->playButton02 = g2_TextureLoad("Resources/playButton02.png");
	}

	//
	{
		this->sound01 = g2_SoundLoad("Resources/sound01.wav");
	}

	//
	{
		nFont1 = g2_FontCreate("굴림", 50, 1);
		nFont2 = g2_FontCreate("Arial", 20, 1);
		nFont3 = g2_FontCreate("궁서", 20, 1);
	}

	return 0;
}

int SceneBegin::Update()
{
	//마우스 위치
	int mouseX = g2_GetMouseX();
	int mouseY = g2_GetMouseY();

	RECT playButtonRect =
	{
		playButtonPos.x + 30,
		playButtonPos.y + 70,
		playButtonPos.x + 225,
		playButtonPos.y + 70 * 2
	};

	//마우스 입력
	onPlayButton = (mouseX >= playButtonRect.left && mouseX <= playButtonRect.right
		&& mouseY >= playButtonRect.top && mouseY <= playButtonRect.bottom);
	if (onPlayButton && g2_GetMouseEvent(0))
	{
		if (!g2_SoundIsPlaying(sound01))
		{
			g2_SoundPlay(sound01);
		}
		g_app.ChangeScene(Scenes::SCENEPLAY);
	}

	////키보드 입력
	//const KEYCODE* pKey = g2_GetKeyboard();

	//if (pKey[VK_SPACE])
	//{
	//	printf("Space");
	//	if (!g2_SoundIsPlaying(sound01))
	//	{
	//		g2_SoundPlay(sound01);
	//	}
	//}

	return 0;
}

int SceneBegin::Render()
{
	//
	{
		//배경
		g2_SetClearColor(0xFFFFFFFF);
		g2_Draw2D(background01, nullptr, &bgPos, &bgScale);

		//플레이버튼
		//g2_Draw2D(playButton01, nullptr, &playButtonPos, &playButtonScale); // 버튼 크기: x 195, y 70

		if (onPlayButton)
		{
			g2_Draw2D(playButton02, nullptr, &playButtonPos, &playButtonScale);
		}
		else
		{
			g2_Draw2D(playButton01, nullptr, &playButtonPos, &playButtonScale);
		}
	}

	//
	{
		g2_FontDrawText(nFont1, { 260, 100, 540, 150 }, 0xFFFFFFFF, "사과 피하기");
		g2_FontDrawText(nFont2, { 440, 160, 560, 210 }, 0xFFFFFFFF, "Lee Gunhee");
	}

	return 0;
}

int SceneBegin::Destroy()
{
	g2_TextureRelease(background01);
	g2_TextureRelease(playButton01);
	g2_TextureRelease(playButton02);

	g2_SoundRelease(sound01);

	g2_TextureRelease(nFont1);
	g2_TextureRelease(nFont2);
	g2_TextureRelease(nFont3);

	return 0;
}
