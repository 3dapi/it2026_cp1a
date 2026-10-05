#include "ScenePlay.h"
#include "SceneResult.h"
#include "CApplication.h"

extern CApplication g_App;

int ScenePlay::Init()
{
	m_Gen.seed(m_Rd());
	m_SideDist = std::uniform_int_distribution<int>(0, 3);
	m_Width = std::uniform_int_distribution<int>(0, g2_GetScnW() - 1);
	m_Height = std::uniform_int_distribution<int>(0, g2_GetScnH() - 1);

	m_Map.Init();
	m_Player.Init();

	m_Boar_right_tx = g2_TextureLoad("Texture/boar_right.png");
	m_Boar_left_tx = g2_TextureLoad("Texture/boar_left.png");
	m_Attack_Sound = g2_SoundLoad("Sound/swing.mp3");
	m_Hurt_Sound = g2_SoundLoad("Sound/hurt.mp3");

	

	m_EnemyKillCount = 0;

	for (int i = 0; i < Max_Enemy_Count; i++) // Max_Enemy_Count = 50
	{
		CEnemy enemy; // 적 객체 생성
		enemy.Init(m_Boar_right_tx, m_Boar_left_tx); // 객체 데이터 초기화
		m_Enemies.push_back(enemy); // Monster Pool 삽입
	}

	m_GameStartTime = g2_TimeGetTime();
	m_SpawnTimer = g2_TimeGetTime(); // 스폰 타이머 생성
	m_CurHp = m_Player.GetCurHp();

	return 0;
}

int ScenePlay::Update()
{
	// 게임 종료 시점 이동용
	const KEYCODE* keyboard = g2_GetKeyboard();
	if (keyboard[VK_ESCAPE] != EINPUT_NONE)
	{
		g_App.ChangeScene(new SceneResult(true, m_remainSecond, m_EnemyKillCount, m_CurHp));
		return 0;
	}

	long long currentTime = g2_TimeGetTime(); // 현재 시간

	long long elapsedTime = currentTime - m_GameStartTime;
	long long remainTime = m_SurvivalTime - elapsedTime;

	if (remainTime < 0)
		remainTime = 0;

	m_remainSecond = static_cast<int>(remainTime / 1000);

	if (elapsedTime >= m_SurvivalTime) // 제한 시간 동안 생존 성공 시
	{
		g_App.ChangeScene(new SceneResult(true, m_remainSecond, m_EnemyKillCount, m_CurHp)); 
		return 0;
	}

	m_Map.Update();
	m_Player.Update();

	if (currentTime - m_SpawnTimer >= m_SpawnInterval) // 생성으로부터 현재까지의 시간차 계산 -> 생성 간격보다 클 경우
	{
		SpawnEnemy(); // 적 스폰
		SpawnEnemy();

		m_SpawnTimer = currentTime; // 초기화
	}

	// 적 데이터 업데이트
	VEC2 playerPos = m_Player.GetPosition();

	for (CEnemy& enemy : m_Enemies) // Monster Pool 전체 검사
	{
		if (!enemy.IsActive()) // 비활성 적 패스
			continue;

		enemy.Update(playerPos.x, playerPos.y); // 활성화된 적만 업데이트
	}

	CheckPlayerEnemyCollision(); // 플레이어-적 충돌 확인
	CheckEnemyEnemyCollision(); // 적-적 충돌 확인
	CheckPlayerAttack(); // 플레이어 공격 히트 확인

	// 플레이어 사망 확인 시 결과창 전환
	if (m_Player.IsDead())
	{
		g_App.ChangeScene(new SceneResult(false, m_remainSecond, m_EnemyKillCount, m_CurHp));
		return 0;
	}
	
	return 0;
}

int ScenePlay::Render(CApplication& application)
{
	const GameResource& Resource = application.GetResource();

	m_Map.Render();
	m_Player.Render();

	char timeText[32];
	char killCount[32];
	char curHp[32];

	sprintf_s(timeText, "남은 시간 : %d", m_remainSecond);
	sprintf_s(curHp, "남은 체력 : %d", m_CurHp);
	sprintf_s(killCount, "처리한 적 : %d", m_EnemyKillCount);
	
	g2_FontDrawText(
		Resource.fontNormal,
		{ 20, 20, 400, 60 },
		0xffffffff,
		timeText
	);

	g2_FontDrawText(
		Resource.fontNormal,
		{ 20, 80, 400, 120 },
		0xffffffff,
		curHp
	);

	g2_FontDrawText(
		Resource.fontNormal,
		{ 20, 140, 400, 180 },
		0xffffffff,
		killCount
	);

	for (CEnemy& enemy : m_Enemies) // 활성화 적만 렌더링
	{
		if (!enemy.IsActive())
			continue;

		enemy.Render();
	}
	

	return 0;
}

int ScenePlay::Destroy()
{
	m_Map.Destroy();
	m_Player.Destroy();
	for (CEnemy& enemy : m_Enemies) // Monster Pool 내부 객체 제거
		enemy.Destroy();

	m_Enemies.clear(); // vector 제거

	g2_TextureRelease(m_Boar_right_tx);
	g2_TextureRelease(m_Boar_left_tx);

	g2_SoundRelease(m_Hurt_Sound); 
	g2_SoundRelease(m_Attack_Sound);

	return 0;
}

void ScenePlay::SpawnEnemy() // 앞서 만들어진 Monster Pool에서 비활성화 객체만 스폰
{
	for (CEnemy& enemy : m_Enemies)
	{
		if (!enemy.IsActive())
		{
			VEC2 spawnPos = GetEnemySpawnPosition();

			enemy.Activate(spawnPos.x, spawnPos.y);
			return;
		}
	}
}

VEC2 ScenePlay::GetEnemySpawnPosition()
{
	VEC2 playerPos = m_Player.GetPosition();

	VEC2 spawnPos{};

	while (true)
	{
		int side = m_SideDist(m_Gen); // 스폰 위치 (상하좌우)
		float spawnX = (float)m_Width(m_Gen); // 생성 범위 지정 넓이
		float spawnY = (float)m_Height(m_Gen); // 생성 범위 지정 높이

		switch (side)
		{
		case TOP:
			spawnPos.x = spawnX;
			spawnPos.y = -50.0f; // 생성 시 테두리 바깥에서 보이도록
			break;
		case BOTTOM:
			spawnPos.x = spawnX;
			spawnPos.y = g2_GetScnH() + 50.0f;
			break;
		case LEFT:
			spawnPos.x = -50.0f;
			spawnPos.y = spawnY;
			break;
		case RIGHT:
			spawnPos.x = g2_GetScnW() + 50.0f;
			spawnPos.y = spawnY;
			break;
		} 

		float dx = spawnPos.x - playerPos.x;
		float dy = spawnPos.y - playerPos.y;

		float distance = sqrt(dx * dx + dy * dy);

		if (distance >= m_MinSpawnDistance)
		{
			break;
		}
	}
	return spawnPos;
}

bool ScenePlay::CheckCollision(const RECT& rc1, const RECT& rc2)
{
	RECT result{};

	return IntersectRect(&result, &rc1, &rc2);
}

void ScenePlay::CheckPlayerEnemyCollision()
{
	RECT playerRect = m_Player.GetCollisionRect();

	for (CEnemy& enemy : m_Enemies)
	{
		if (!enemy.IsActive())
			continue;

		RECT enemyRect = enemy.GetCollisionRect();

		if (CheckCollision(playerRect, enemyRect))
		{
			if (!m_Player.IsInvincible()) // 무적 여부 확인
			{
				m_Player.TakeDamage(10); // 무적이 아닐 시 피해
				g2_SoundPlay(m_Hurt_Sound);
				m_CurHp = m_Player.GetCurHp();
				m_Player.StartInvincible(); // 무적 타임 시작
			}
		}
	}
}

void ScenePlay::CheckEnemyEnemyCollision()
{
	for (int i = 0; i < m_Enemies.size(); ++i)
	{
		if (!m_Enemies[i].IsActive())
			continue;

		for (int j = i + 1; j < m_Enemies.size(); ++j)
		{
			if (!m_Enemies[j].IsActive())
				continue;

			RECT enemyRect1 = m_Enemies[i].GetCollisionRect();
			RECT enemyRect2 = m_Enemies[j].GetCollisionRect();

			VEC2 pos1 = m_Enemies[i].GetPosition();
			VEC2 pos2 = m_Enemies[j].GetPosition();

			float dx = pos2.x - pos1.x;
			float dy = pos2.y - pos1.y;

			auto distanceSquared = dx * dx + dy * dy;

			const float EnemyCheckDistance = 100.0f;

			// 거리가 먼 적은 패스
			if (distanceSquared > EnemyCheckDistance * EnemyCheckDistance)
				continue;

			// 충돌 확인
			if (!CheckCollision(enemyRect1, enemyRect2))
				continue;

			// X축으로 겹친 정도
			float overlapX =
				(min(enemyRect1.right, enemyRect2.right) -
					max(enemyRect1.left, enemyRect2.left));

			// Y축으로 겹친 정도
			float overlapY =
				(min(enemyRect1.bottom, enemyRect2.bottom) -
					max(enemyRect1.top, enemyRect2.top));

			// X축으로 더 적게 겹쳤다면 X축으로 밀어냄
			if (overlapX < overlapY)
			{
				float push = overlapX / 2.0f;

				if (dx > 0.0f)
				{
					pos1.x -= push;
					pos2.x += push;
				}
				else
				{
					pos1.x += push;
					pos2.x -= push;
				}
			}
			// Y축으로 더 적게 겹쳤다면 Y축으로 밀어냄
			else
			{
				float push = overlapY / 2.0f;

				if (dy > 0.0f)
				{
					pos1.y -= push;
					pos2.y += push;
				}
				else
				{
					pos1.y += push;
					pos2.y -= push;
				}
			}

			// 수정된 위치 적용
			m_Enemies[i].SetPosition(pos1.x, pos1.y);
			m_Enemies[j].SetPosition(pos2.x, pos2.y);
		}
	}
}

void ScenePlay::CheckPlayerAttack()
{
	if (!m_Player.IsAttack())
		return;

	g2_SoundPlay(m_Attack_Sound);
	RECT attackRect = m_Player.GetAttackRect();

	for (CEnemy& enemy : m_Enemies)
	{
		if (!enemy.IsActive())
			continue;

		if (CheckCollision(attackRect, enemy.GetCollisionRect()))
		{
			enemy.TakeDamage(m_Player.GetAttackPoint());

			if (enemy.IsDead())
			{
				m_EnemyKillCount++;
				enemy.Deactivate();
			}
		}
	}
}

int ScenePlay::GetKillCount()
{
	return m_EnemyKillCount;
}
