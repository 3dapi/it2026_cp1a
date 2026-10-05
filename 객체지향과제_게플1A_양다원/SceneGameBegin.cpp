#include "SceneGameBegin.h"
#include "TexturePath.h"
#include "CApplication.h"

#include "stdio.h"

int SceneGameBegin::Init()
{
	texture.mainTexture = g2_TextureLoad(TX_MAIN);
	startButton = g2_FontCreate("굴림", 60, 0);
	exitButton = g2_FontCreate("굴림", 60, 0);
	texture.startSound = g2_SoundLoad(VFX_START);
	return 0;
}

int SceneGameBegin::Update(CApplication& cApp)
{
	// 마우스 입력 확인
	if (cApp.InputMouse(startPos) == TRUE)
	{
		g2_SoundPlay(texture.startSound);
		if (!g2_SoundIsPlaying(texture.startSound))
		{
			// 효과음 종료 후 씬 전환
			printf("%d\n", cApp.GetScene());
			cApp.ChangeScene(GAMEPLAY);
			printf("씬변경, %d\n", cApp.GetScene());
		}
		return 0;
	}
	else if (cApp.InputMouse(exitPos) == TRUE)
		cApp.Destroy();

	return 0;
}

int SceneGameBegin::Render()
{	
	g2_Draw2D(texture.mainTexture, nullptr);
		
	g2_FontDrawText(startButton, startPos, 0xFFFFFFFF, "Start");
	g2_FontDrawText(exitButton, exitPos, 0xFFFFFFFF, "Exit");

	return 0;
}

int SceneGameBegin::Destroy()
{
	g2_TextureRelease(texture.mainTexture);
	g2_SoundRelease(texture.startSound);

	return 0;
}
