#include "SceneGamePlay.h"
#include "glc2d.h"

int SceneGamePlay::Init()
{
	m_txBg = g2_TextureLoad("resource/texture/tex_ui/background.png");
	m_bgm = g2_SoundLoad("resource/audio/playBGM.mp3");
	m_hitSound = g2_SoundLoad("resource/audio/rockHit.mp3");

	if (m_scoreFont == -1)
	{
		m_scoreFont = g2_FontCreate("¸¼Àº °íµñ", 30);
	}

	if (m_font == -1)
	{
		m_font = g2_FontCreate("¸¼Àº °íµñ", 24);
	}

	g2_SoundReset(m_bgm);
	g2_SoundPlay(m_bgm, true);

	player.Init();
	rockSpawnTimer = 0.0f;
	timer = 0.0f;
	score = 0;
	isGameOver = false;
	gameOverTimer = 0.0f;

	return 0;
}

int SceneGamePlay::Update(float deltaTime)
{
	if (isGameOver)
	{
		gameOverTimer += deltaTime;

		if (gameOverTimer >= 1.5f)
		{
			return SCENE_RESULT;
		}

		return SCENE_KEEP;
	}

	timer += deltaTime;
	if (timer >= 1)
	{
		score += 10;
		timer -= 1;
	}

	player.Update(deltaTime);
	RECT pCollider = player.GetCollider();

	if (pCollider.left < 0)
	{
		player.transform.position.x -= pCollider.left;
	}
	else if (pCollider.right > 360)
	{
		player.transform.position.x -= pCollider.right - 360;
	}

	rockSpawnTimer += deltaTime;
	if (rockSpawnTimer >= 0.6f)
	{
		SpawnRock();
	}

	RECT overlap{};
	pCollider = player.GetCollider();
	
	for (int i = 0; i < static_cast<int>(rocks.size()); ++i)
	{
		Rock* rock = rocks[i];
		rock->Update(deltaTime);
		const RECT rCollider = rock->GetCollider();
		
		if (rCollider.bottom > 592)
		{
			rock->Destroy();
			delete rock;
			rocks.erase(rocks.begin() + i);
			--i;
			continue;
		}

		if (IntersectRect(&overlap, &pCollider, &rCollider))
		{
			player.SetDead();
			g2_SoundPlay(m_hitSound, false);
			isGameOver = true;
			break;
		}
	}
	return SCENE_KEEP;
}

int SceneGamePlay::Render()
{
	g2_Draw2D(m_txBg, nullptr);
	player.Render();
	g2_FontDrawText(m_scoreFont, { 50, 20, 240, 200 }, 0xFFFFFFFF, "%d", score);
	g2_FontDrawText(m_font, { 130, 608, 250, 640 }, 0xFFFFFFFF, "a / d : ÀÌµ¿");

	if (isGameOver)
	{
		return 0;
	}

	for (const auto& rock : rocks)
	{
		rock->Render();
	}
	return 0;
}

int SceneGamePlay::Destroy()
{
	g2_TextureRelease(m_txBg);
	g2_SoundStop(m_bgm);
	g2_SoundRelease(m_bgm);
	g2_SoundRelease(m_hitSound);
	
	player.Destroy();

	for (auto& rock : rocks)
	{
		rock->Destroy();
		delete rock;
	}
	rocks.clear();

	return 0;
}

void SceneGamePlay::SpawnRock()
{
	Rock* rock = new Rock;

	rocks.push_back(rock);
	rock->Init();
	
	rockSpawnTimer -= 0.6f;
}

int SceneGamePlay::GetScore() const
{
	return score;
}
