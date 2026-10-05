#include "SceneGameResult.h"
#include "CApplication.h"
#include "TexturePath.h"
#include <stdio.h>

int SceneGameResult::Init()
{
	resultText = g2_FontCreate("±¼¸²", 70, 0);
	gameText = g2_FontCreate("±¼¸²", 50, 0);

	texture.loseSound = g2_SoundLoad(VFX_LOSE);
	texture.winSound = g2_SoundLoad(VFX_WIN);
	texture.startSound = g2_SoundLoad(VFX_START);
	_isPlayed = false;
	return 0;
}

int SceneGameResult::Update(CApplication& cApp)
{
	if (!_isPlayed)
	{
		if (_isWin)
			g2_SoundPlay(texture.winSound);
		else
			g2_SoundPlay(texture.loseSound);
		_isPlayed = true;
	}

	if (cApp.InputMouse(exitPos) == TRUE)
	{
		cApp.Destroy();
	}
	else if (cApp.InputMouse(replayPos) == TRUE)
	{
		g2_SoundPlay(texture.startSound);
		if (!g2_SoundIsPlaying(texture.startSound))
		{
			// È¿°úÀ½ Á¾·á ÈÄ ¾À ÀüÈ¯
			printf("%d\n", cApp.GetScene());
			cApp.ChangeScene(GAMEPLAY);
			printf("¾Àº¯°æ, %d\n", cApp.GetScene());
		}
	}

	return 0;
}

int SceneGameResult::Render()
{
	
	g2_FontDrawText(resultText, resultPos, 0xFFFFFFFF, _isWin ? "WIN" : "LOSE");
	g2_FontDrawText(gameText, exitPos, 0xFFFFFFFF, "EXIT");
	g2_FontDrawText(gameText, replayPos, 0xFFFFFFFF, "REPLAY");
	g2_FontDrawText(gameText, timePos, 0xFFFFFFFF, "PLAY TIME : %.4f", _time);

	return 0;
}

int SceneGameResult::Destroy()
{
	g2_TextureRelease(texture.winSound);
	g2_TextureRelease(texture.loseSound);
	g2_TextureRelease(texture.startSound);
	return 0;
}

void SceneGameResult::SetOutcome(bool outcome, float playtime)
{
	_isWin = outcome;
	_time = playtime;
	return;
}

