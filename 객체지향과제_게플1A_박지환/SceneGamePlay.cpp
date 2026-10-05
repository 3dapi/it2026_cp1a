#include "SceneGamePlay.h"
#include "CApplication.h"

int SceneGamePlay::Init()
{
	// texture
	this->m_txBg = g2_TextureLoad("Resource/Texture/background.png", 0);
	this->m_txCrashEffect = g2_TextureLoad("Resource/Texture/crash_effect.png", 0);

	// sound
	this->m_startSound = g2_SoundLoad("Resource/Sound/game_start.mp3");
	this->m_ScoreSound = g2_SoundLoad("Resource/Sound/score.mp3");
	this->m_gameOverSound = g2_SoundLoad("Resource/Sound/car_crash.mp3");

	// font
	this->m_fntMessage = g2_FontCreate("NeoµÕ±Ù¸ð", 150);
	this->m_fntBonus = g2_FontCreate("NeoµÕ±Ù¸ð", 50);

	m_player.Init();
	m_opponent.Init();

	return 0;
}

int SceneGamePlay::Destroy()
{
	m_player.Destroy();
	m_opponent.Destroy();
	g2_TextureRelease(m_txBg);
	g2_TextureRelease(m_txCrashEffect);
	g2_SoundRelease(m_startSound);
	g2_SoundRelease(m_ScoreSound);
	g2_SoundRelease(m_gameOverSound);
	return 0;
}

void SceneGamePlay::ResetGame()
{
	m_gameTimer.Init();
	m_player.Reset();
	m_opponent.Reset();
	m_gameScore = 0;
	m_speedStep = 40.0f;
	m_showCrashEffect = false;
	m_lapCount = 0;
	m_nearMiss = false;
	m_showBonusText = false;
	m_bonusTextTime = 0.f;

	g2_SoundPlay(m_startSound);
}

int SceneGamePlay::GetGameScore()
{
	return m_gameScore;
}

bool SceneGamePlay::CheckCollision(	VEC2 playerPos, VEC2 opponentPos, 
	float playerAngle, float opponentAngle, bool& isNear)
{
	constexpr float CAR_COLLISION_RADIUS{ 15.5f };
	constexpr float OFFSET{ 20.0f };
	constexpr float NEAR_MARGIN{ 40.0f };
	
	isNear = false;

	float playerFwdX = -std::cos(playerAngle);
	float playerFwdY = std::sin(playerAngle);
	float opponentFwdX = std::cos(opponentAngle);
	float opponentFwdY = std::sin(opponentAngle);

	VEC2 playerFront
	{
		playerPos.x + playerFwdX * OFFSET,
		playerPos.y + playerFwdY * OFFSET
	};

	VEC2 playerBack
	{
		playerPos.x - playerFwdX * OFFSET,
		playerPos.y - playerFwdY * OFFSET
	};

	VEC2 opponentFront
	{
		opponentPos.x + opponentFwdX * OFFSET,
		opponentPos.y + opponentFwdY * OFFSET
	};

	VEC2 opponentBack
	{
		opponentPos.x - opponentFwdX * OFFSET,
		opponentPos.y - opponentFwdY * OFFSET
	};

	VEC2 playerCenters[3]
	{
		playerFront, playerPos, playerBack
	};

	VEC2 opponentCenters[3]
	{
		opponentFront, opponentPos, opponentBack
	};

	float collisionDistance = CAR_COLLISION_RADIUS * 2.f;
	float nearDistance = collisionDistance + NEAR_MARGIN;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float dx = playerCenters[i].x - opponentCenters[j].x;
			float dy = playerCenters[i].y - opponentCenters[j].y;

			if (dx * dx + dy * dy
				<= collisionDistance * collisionDistance)
			{
				return true;
			}

			if (dx * dx + dy * dy
				<= nearDistance * nearDistance)
			{
				isNear = true;
			}
		}
	}

	return false;
}

bool SceneGamePlay::CheckFinishLine(VEC2 previousPos, VEC2 currentPos)
{
	constexpr float FINISH_LINE{ 640.0f };

	return m_player.GetTrackSection() == TrackSection::BottomStraight
		&& previousPos.x > FINISH_LINE
		&& currentPos.x <= FINISH_LINE;
}

int SceneGamePlay::Update()
{
	m_gameTimer.Update();
	float deltaTime = m_gameTimer.GetDeltaTime();
	VEC2 previousPlayerPos = m_player.GetPosition();

	bool wasNear = false;
	bool wasColliding = CheckCollision(
		previousPlayerPos,
		m_opponent.GetPosition(),
		m_player.GetRotationAngle(),
		m_opponent.GetRotationAngle(),
		wasNear
	);
	bool wasDangerouslyClose = wasNear && !wasColliding;
		
	m_player.Update(deltaTime);
	m_opponent.Update(deltaTime);

	VEC2 playerPos = m_player.GetPosition();
	VEC2 opponentPos = m_opponent.GetPosition();
	float playerAngle = m_player.GetRotationAngle();
	float opponentAngle = m_opponent.GetRotationAngle();

	bool isNear = false;

	bool isCollision = CheckCollision(
		playerPos, opponentPos, 
		playerAngle, opponentAngle, isNear
	);

	if (isCollision)
	{
		m_crashEffectPos = VEC2(
			(playerPos.x + opponentPos.x) * 0.5f,
			(playerPos.y + opponentPos.y) * 0.5f
		);

		m_showCrashEffect = true;

		g2_SoundPlay(m_gameOverSound);
		g_app.ChangeScene(Scene::Result);

		return 0;
	}
	
	bool didChangeLane = m_player.DidChangeLane();

	if (didChangeLane && wasDangerouslyClose)
	{
		m_nearMiss = true;
	}


	// check finish line
	bool isFinishLine = CheckFinishLine(previousPlayerPos, playerPos);
	if (isFinishLine)
	{
		++m_lapCount;
		++m_gameScore;
		m_player.IncreaseSpeed(m_speedStep);
		m_opponent.IncreaseSpeed(m_speedStep);
		g2_SoundPlay(m_ScoreSound);

		if (0 == m_lapCount % 4)
		{
			m_speedStep *= 2 / 3.f;
		}
	}

	if (m_nearMiss && !isNear)
	{
		m_nearMiss = false;
		++m_gameScore;
		g2_SoundPlay(m_ScoreSound);

		m_bonusTextPos = VEC2(
			(playerPos.x + opponentPos.x) * 0.5f,
			(playerPos.y + opponentPos.y) * 0.5f
		);

		m_bonusTextTime = 0.f;
		m_showBonusText = true;
	}

	if (m_showBonusText)
	{
		m_bonusTextTime += deltaTime;
		m_bonusTextPos.y -= 40.f * deltaTime;

		if (m_bonusTextTime >= 0.7f)
		{
			m_showBonusText = false;
		}
	}

	return 0;
}

int SceneGamePlay::RenderWorld()
{
	// background
	{
		auto winSize = g_app.GetWinSize();
		auto bgTexW = (float)g2_TextureWidth(m_txBg);
		auto bgTexH = (float)g2_TextureHeight(m_txBg);
		VEC2 bgScale{ winSize.cx / bgTexW, winSize.cy / bgTexH };
		g2_Draw2D(m_txBg, nullptr, nullptr, &bgScale);
	}

	m_player.Render();
	m_opponent.Render();

	// crash effect
	if (m_showCrashEffect)
	{
		VEC2 effectDrawPos
		{
			m_crashEffectPos.x - g2_TextureWidth(m_txCrashEffect) * 0.5f,
			m_crashEffectPos.y - g2_TextureHeight(m_txCrashEffect) * 0.5f
		};
		g2_Draw2D(m_txCrashEffect, nullptr, &effectDrawPos);
	}
	
	return 0;
}

int SceneGamePlay::Render()
{
	RECT rc{ 605, 293, 905, 453 };
	if (m_gameScore >= 10)
	{
		rc.left -= 38;
	}
	g2_FontDrawText(m_fntMessage, rc, 0xFF59432F, "%d", m_gameScore);

	
	if (m_showBonusText)
	{
		RECT rcNear 
		{ 
			(long)(m_bonusTextPos.x - 40.f), 
			(long)(m_bonusTextPos.y - 40.f), 
			(long)(m_bonusTextPos.x + 40.f), 
			(long)(m_bonusTextPos.y + 40.f) 
		};
		g2_FontDrawText(m_fntBonus, rcNear, 0xFFFF8060, "+1");
	}
	return 0;
}

