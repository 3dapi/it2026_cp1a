#pragma once
#include "glc2d.h"
#include <string>
#include "SceneGamePlay.h"

class SceneGameResult
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

public:
	void SetScore(int score);

private:
	// game font
	int	m_fntTitle	{ -1 };
	int m_fntScore	{ -1 };
	int m_fntRestart{ -1 };
	int m_fntExit	{ -1 };

	int m_gameScore	{ 0 };

	std::string m_gameTitle		{ "GAME OVER" };
	std::string m_restartText	{ "ENTER : 다시하기" };
	std::string m_exitText		{ "ESC : 종료" };

	static constexpr long long BLINK_INTERVAL{ 500 };
	bool m_isTextVisible{ true };
};

