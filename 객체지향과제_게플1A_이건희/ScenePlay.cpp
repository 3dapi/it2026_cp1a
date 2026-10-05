#include "ScenePlay.h"
#include "SceneBegin.h"
#include "SceneScore.h"
#include "glc2d.h"
#include "CApplication.h"

extern CApplication g_app;
int ScenePlay::score = 0;

int ScenePlay::Init()
{
	ScenePlay::score = 0;
	
	this->player = g2_TextureLoad("Resources/player.png");
	this->apple = g2_TextureLoad("Resources/apple.png");

	this->hit = g2_SoundLoad("Resources/hit.mp3");
	return 0;
}

int ScenePlay::Update()
{
	// 플레이어 이동
	const KEYCODE* pKey = g2_GetKeyboard();
	if (pKey[VK_LEFT] || pKey['A'])
	{
		playerPos.x -= playerSpeed;
	}
	if (pKey[VK_RIGHT] || pKey['D'])
	{
		playerPos.x += playerSpeed;
	}

	if (playerPos.x < minX)
	{
		playerPos.x = minX;
	}
	if (playerPos.x > maxX)
	{
		playerPos.x = maxX;
	}

	// 사과 이동
	spawnCounter++;
	if (spawnCounter >= spawnCooldown)
	{
		spawnCounter = 0; // 쿨타임 타이머 초기화

		// X: randomX Y: -50 에서 스폰
		float randomX = (float)(rand() % 700 + 50);
		VEC2 newApplePos = { randomX, -50.0f };

		applePositions.push_back(newApplePos);
	}
	for (int i = (int)applePositions.size() - 1; i >= 0; i--)
	{
		// 사과 떨어짐
		applePositions[i].y += appleSpeed;

		// 충돌 감지
		// 플레이어 충돌체
		RECT playerRect =
		{
			playerPos.x - playerWidth,
			playerPos.y,
			playerPos.x + playerWidth - 40,
			playerPos.y + playerHeight,
		};
		// 사과 충돌체
		RECT appleRect =
		{
			applePositions[i].x,
			applePositions[i].y + appleWidth,
			applePositions[i].x,
			applePositions[i].y + appleHeight,
		};
		// 충돌 여부
		bool isCollideX = (playerRect.left < appleRect.right) && (playerRect.right > appleRect.left);
		bool isCollideY = (playerRect.top < appleRect.bottom) && (playerRect.bottom > appleRect.top);

		// 충돌한 사과 지우고 결과 화면으로 이동
		if (isCollideX && isCollideY)
		{
			printf("충돌");
			g2_SoundPlay(hit);
			applePositions.erase(applePositions.begin() + i);

			g_app.ChangeScene(Scenes::SCENESCORE);
		}

		// 떨어진 사과 지움
		if (applePositions[i].y > 650.0f)
		{
			score++;
			spawnCooldown--;
			applePositions.erase(applePositions.begin() + i);
		}
	}

	return 0;
}

int ScenePlay::Render()
{
	//배경
	g2_SetClearColor(0xB9E0FDFF);

	// 플레이어 캐릭터 그리기
	g2_Draw2D(player, nullptr, &playerPos, &playerScale);
	
	// 사과 그리기
	for (int i = 0; i < applePositions.size(); i++)
	{
		g2_Draw2D(apple, nullptr, &applePositions[i], &appleScale);
	}

	return 0;
}

int ScenePlay::Destroy()
{
	g2_TextureRelease(player);
	g2_TextureRelease(apple);
	return 0;
}