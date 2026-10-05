#include "CApplication.h"
#include "glc2d.h"

#include "stdio.h"

TextureList texture;
extern CApplication g_app;

int AppUpdate()
{
	return g_app.Update();
}

int AppRender()
{
	return g_app.Render();
}

int CApplication::Init()
{
	g2_InitSdk();

	g2_SetFrameMove(AppUpdate);
	g2_SetRender(AppRender);

	g2_CreateWin(100, 25, screenWidth, screenHeight, "STRIKE");
	g2_SetClearColor(0xFF000000);

	sceneBegin.Init();

	return 0;
}

int CApplication::Update()
{
	ChangeUpdate();

	return 0;
}

int CApplication::Render()
{
	ChangeRender();

	return 0;
}

int CApplication::Destroy()
{
	sceneResult.Destroy();
	g2_DestroyWin();
	return 0;
}

void CApplication::ChangeScene(ScreenState nextScene)
{
	if (currentScene == nextScene)
		return;

	currentScene = nextScene;

	switch (currentScene)
	{
		case(MAINMENU):
		{
			sceneBegin.Init();
			sceneBegin.Update(*this);
		}break;

		case(GAMEPLAY):
		{
			scenePlay.Init();
			scenePlay.Update(*this);
		}break;

		case(GAMEOVER):
		{
			sceneResult.Init();
			sceneResult.Update(*this);
		}break;
	}
}

void CApplication::ChangeUpdate()
{
	switch (currentScene)
	{
	case(MAINMENU):
		sceneBegin.Update(*this);
		break;
	case(GAMEPLAY):
		if (texture.mainTexture != NULL)
			sceneBegin.Destroy();
		scenePlay.Update(*this);
		break;
	case(GAMEOVER):
		if (texture.cursorTexture != NULL || texture.backgroundTexture != NULL)
			scenePlay.Destroy();
		sceneResult.Update(*this);
		break;
	}
}
void CApplication::ChangeRender()
{
	switch (currentScene)
	{
	case(MAINMENU):
		sceneBegin.Render();
		break;
	case(GAMEPLAY):
		scenePlay.Render();
		break;
	case(GAMEOVER):
		sceneResult.Render();
		break;
	}
}

ScreenState CApplication::GetScene() const
{
	return currentScene;
}

void CApplication::Outcome(bool rel, float time)
{
	sceneResult.SetOutcome(rel, time);
	return;
}
bool CApplication::InputMouse(RECT button)
{
	if (g2_GetMouseEvent(0) == EINPUT_DOWN)
	{
		int mouseX = g2_GetMouseX();
		int mouseY = g2_GetMouseY();

		if (mouseX >= button.left && mouseX <= button.right && mouseY >= button.top && mouseY <= button.bottom)
		{
			return TRUE;
		}
	}
	return FALSE;
}