#pragma once
#include "SceneGameBegin.h"
#include "SceneGamePlay.h"
#include "SceneGameResult.h"

enum ScreenState
{
	MAINMENU,
	GAMEPLAY,
	GAMEOVER
};

struct TextureList
{
	int mainTexture = -1;
	int backgroundTexture = -1;
	int gaugeTexture = -1;
	int cursorTexture = -1;
	int escwindowTexture = -1;

	int slimeTexture = -1;
	int goblinTexture = -1;
	int orcTexture = -1;
	int dragonTexture = -1;

	int attackSound = -1;
	int battleSound = -1;
	int damageSound = -1;
	int loseSound = -1;
	int winSound = -1;
	int startSound = -1;
};
extern TextureList texture;

class CApplication
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

	void ChangeScene(ScreenState nextScene);
	void ChangeUpdate();
	void ChangeRender();

	ScreenState GetScene() const;
	void Outcome(bool rel, float time);
	bool InputMouse(RECT button);

protected:
	static constexpr int screenWidth = 1280;
	static constexpr int screenHeight = 720;

	SceneGameBegin  sceneBegin;
	SceneGamePlay   scenePlay;
	SceneGameResult sceneResult;

private:
	ScreenState currentScene = MAINMENU;
	

};

