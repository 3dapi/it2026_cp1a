#pragma once
#include "glc2d.h"
#include <windows.h>
#include "GameTimer.h"
#include "Track.h"
#include "Player.h"
#include "Opponent.h"
#include <cmath>

class SceneGamePlay
{
public:
	int Init();
	int Update();
	int RenderWorld();
	int Render();
	int Destroy();

public:
	void ResetGame();
	int GetGameScore();

protected:
	bool CheckCollision(
		VEC2 playerPos, VEC2 opponentPos, 
		float playerAngle, float opponentAngle, bool& isNear
	);
	bool CheckFinishLine(VEC2 previousPos, VEC2 currentPos);

	// game texture
	int m_txBg				{ -1 };
	int m_txCrashEffect		{ -1 };
	bool m_showCrashEffect	{ false };
	VEC2 m_crashEffectPos	{ 0.f, 0.f };

	// game font
	int	m_fntMessage		{ -1 };
	int m_fntBonus			{ -1 };
	VEC2 m_bonusTextPos		{ 0.f, 0.f };
	float m_bonusTextTime	{ 0.f };
	bool m_showBonusText	{ false };

	// game sound 
	int m_startSound		{ -1 };
	int m_ScoreSound		{ -1 };	
	int m_gameOverSound		{ -1 };

	int m_gameScore			{ 0 };	
	int m_lapCount			{ 0 };

	bool m_nearMiss{ false };

	float m_speedStep		{ 40.0f };


	GameTimer m_gameTimer;
	Player m_player;
	Opponent m_opponent;
};

