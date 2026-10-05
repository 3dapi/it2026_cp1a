#include "SceneGamePlay.h"
#include "glc2d.h"
#include "CApplication.h"

extern CApplication g_app;

int SceneGamePlay::Init()
{
	this->m_txBall = g2_TextureLoad("resource/texture/play/Ball.png");							//공 이미지 위치
	this->m_txBar_width = g2_TextureLoad("resource/texture/play/Bar_width.png");				//가로 바 이미지 위치
	this->m_txBar_Length = g2_TextureLoad("resource/texture/play/Bar_Length.png");				//세로 바 이미지 위치
	this->m_txObstacle_square = g2_TextureLoad("resource/texture/play/Obstacles_square.png");	//장애물-정사각형
	this->m_txGoal = g2_TextureLoad("resource/texture/play/Goal.png");							//골 영역 이미지
	
	g2_SetClearColor(0xFF000000);																// 게임 화면 배경 검정색

	//장애물 위치 수정은 여기서																	//구조체 x, y, 가로, 세로
	m_obstacles[0] = { 240, 80, 100, 100 };
	m_obstacles[1] = { 480, 80, 100, 100 };
	m_obstacles[2] = { 786, 80, 100, 100 };
	m_obstacles[3] = { 1026, 80, 100, 100 };
	m_obstacles[4] = { 240, 240, 100, 100 };
	m_obstacles[5] = { 480, 240, 100, 100 };
	m_obstacles[6] = { 786, 240, 100, 100 };
	m_obstacles[7] = { 1026, 240, 100, 100 };
	m_obstacles[8] = { 240, 400, 100, 100 };
	m_obstacles[9] = { 480, 400, 100, 100 };
	m_obstacles[10] = { 786, 400, 100, 100 };
	m_obstacles[11] = { 1026, 400, 100, 100 };
	m_obstacles[12] = { 240, 560, 100, 100 };
	m_obstacles[13] = { 480, 560, 100, 100 };
	m_obstacles[14] = { 786, 560, 100, 100 };
	m_obstacles[15] = { 1026, 560, 100, 100 };

	//공 시작 위치																				
	m_ballCount = 5;																				
	m_balls[0] = { 420, 300,  0.035f,  0.035f, 30, true };
	m_balls[1] = { 900, 300, -0.035f,  0.035f, 30, true };
	m_balls[2] = { 420, 470,  0.035f, -0.035f, 30, true };
	m_balls[3] = { 900, 470, -0.035f, -0.035f, 30, true };
	m_balls[4] = { 683, 150,  0.035f,  0.035f, 30, true };

	return 0;
}


int SceneGamePlay::Update()
{
	//현재 마우스 위치 좌표
	int mouseX = g2_GetMouseX();
	int mouseY = g2_GetMouseY();

	//지정한 게임 화면 크기 가져오기
	int screen_width = g2_GetScnW();
	int screen_Length = g2_GetScnH();
	// 실제 득점 판정용 Goal 크기
	float goalCollisionWidth = 120.0f;
	float goalCollisionHeight = 60.0f;
	// 화면 중앙에 Goal 판정 영역 배치
	float goalX = (screen_width - goalCollisionWidth) / 2.0f;
	float goalY = (screen_Length - goalCollisionHeight) / 2.0f;

	//마우스와 벽의 거리 - 바 위치 정할때 사용
	int distance_top = mouseY;																		//위쪽 벽 길이 = 마우스 높이
	int distance_bottom = screen_Length - mouseY;													//아래 벽 길이 = 화면길이 - 마우스 높이
	int distance_left = mouseX;																		//왼쪽 벽 길이 = 마우스 길이
	int distance_right = screen_width - mouseX;														//오른 벽 길이 = 화면 길이 - 마우스 길이

	//마우스와 가장 가까운 벽 찾기
	{
		int closeDistance = distance_top;															//기준길이 - 탑까지의 거리
		m_barSide = BarSide::TOP;																	//위에 있는 상태

		if (distance_right < closeDistance)															//오른쪽이 더 가까우면
		{
			closeDistance = distance_right;
			m_barSide = BarSide::RIGHT;																//오른벽
		}
		if (distance_bottom < closeDistance)														//아래가 더 가까우면
		{
			closeDistance = distance_bottom;
			m_barSide = BarSide::BOTTOM;															//하단벽
		}
		if (distance_left < closeDistance)															//왼쪽이 더 가까우면
		{
			closeDistance = distance_left;
			m_barSide = BarSide::LEFT;																//왼쪽벽
		}
	}
	
	//마우스 커서에 따른 바 위치 제한
	{
		if (m_barSide == BarSide::TOP)																//위에 있는 상태
		{
			// bar의 중심이 마우스 X와 맞도록 위치 계산
			m_barX = mouseX - m_barLength / 2;
			m_barY = 0;

			// bar가 화면 밖으로 나가지 않게 제한
			if (m_barX < 0)
			{
				m_barX = 0;
			}
			if (m_barX + m_barLength > screen_width)
			{
				m_barX = screen_width - m_barLength;
			}
		}
		else if (m_barSide == BarSide::BOTTOM)
		{
			// BAR의 중심이 마우스 X와 맞도록 위치 계산
			m_barX = mouseX - m_barLength / 2;
			int barLength = g2_TextureHeight(m_txBar_width);
			m_barY = screen_Length - barLength;
			if (m_barX < 0)
			{
				m_barX = 0;
			}
			if (m_barX + m_barLength > screen_width)
			{
				m_barX = screen_width - m_barLength;
			}
		}
		else if (m_barSide == BarSide::LEFT)
		{
			// 왼쪽 벽에 붙이기
			m_barX = 0;

			// BAR의 중심이 마우스 Y와 맞도록 위치 계산
			m_barY = mouseY - m_barLength / 2;


			// BAR가 화면 위로 나가지 않게 제한
			if (m_barY < 0)
			{
				m_barY = 0;
			}
			// BAR가 화면 아래로 나가지 않게 제한
			if (m_barY + m_barLength > screen_Length)
			{
				m_barY = screen_Length - m_barLength;
			}
		}
		else if (m_barSide == BarSide::RIGHT)
		{
			int barWidth = g2_TextureWidth(m_txBar_Length);
			// 오른쪽 벽에 붙이기
			m_barX = screen_width - barWidth;
			// BAR의 중심이 마우스 Y와 맞도록 위치 계산
			m_barY = mouseY - m_barLength / 2;


			if (m_barY < 0)
			{
				m_barY = 0;
			}


			if (m_barY + m_barLength > screen_Length)
			{
				m_barY = screen_Length - m_barLength;
			}
		}
	}

	// X축 이동 후 장애물과 충돌했는지 검사
	for (int b = 0; b < m_ballCount; b++)
	{
		if (m_balls[b].active == false)
		{
			continue;
		}
		m_balls[b].x += m_balls[b].speedX;

		// X축 장애물 충돌
		for (int i = 0; i < m_obstacleCount; i++)
		{
			if (m_balls[b].x < m_obstacles[i].x + m_obstacles[i].width && m_balls[b].x + m_balls[b].size > m_obstacles[i].x && m_balls[b].y < m_obstacles[i].y + m_obstacles[i].Length && m_balls[b].y + m_balls[b].size > m_obstacles[i].y)
			{
				m_balls[b].speedX = -m_balls[b].speedX;
				m_balls[b].x += m_balls[b].speedX;

				break;
			}
		}
		m_balls[b].y += m_balls[b].speedY;
		// Y축 장애물 충돌
		for (int i = 0; i < m_obstacleCount; i++)
		{
			if (m_balls[b].x < m_obstacles[i].x + m_obstacles[i].width && m_balls[b].x + m_balls[b].size > m_obstacles[i].x && m_balls[b].y < m_obstacles[i].y + m_obstacles[i].Length && m_balls[b].y + m_balls[b].size > m_obstacles[i].y)
			{
				m_balls[b].speedY = -m_balls[b].speedY;
				m_balls[b].y += m_balls[b].speedY;

				break;
			}
		}
		//충돌 판정
		// 위/아래 bar
		if (m_barSide == BarSide::TOP ||
			m_barSide == BarSide::BOTTOM)
		{
			// 공과 가로 bar가 겹치는지 확인
			if (m_balls[b].x < m_barX + m_barLength &&
				m_balls[b].x + m_balls[b].size > m_barX &&
				m_balls[b].y < m_barY + m_barThickness &&
				m_balls[b].y + m_balls[b].size > m_barY)
			{
				g_app.PlayPaddleHit();

				// 위아래 방향 반전
				m_balls[b].speedY = -m_balls[b].speedY;


				// 공이 bar 안쪽에 끼지 않도록 위치 보정
				if (m_barSide == BarSide::TOP)
				{
					// TOP bar 아래쪽으로 밀어냄
					m_balls[b].y = m_barY + m_barThickness;
				}
				else
				{
					// BOTTOM bar 위쪽으로 밀어냄
					m_balls[b].y = m_barY - m_balls[b].size;
				}
			}
		}
		// 왼쪽/오른쪽 bar
		else
		{
			// 공과 세로 bar가 겹치는지 확인
			if (m_balls[b].x < m_barX + m_barThickness &&
				m_balls[b].x + m_balls[b].size > m_barX &&
				m_balls[b].y < m_barY + m_barLength &&
				m_balls[b].y + m_balls[b].size > m_barY)
			{
				g_app.PlayPaddleHit();

				//좌우 방향 반전
				m_balls[b].speedX = -m_balls[b].speedX;


				//공이 BAR 안쪽에 끼지 않도록 위치 보정
				if (m_barSide == BarSide::LEFT)
				{
					//LEFT bar 오른쪽으로 밀어냄
					m_balls[b].x = m_barX + m_barThickness;
				}
				else
				{
					//RIGHT bar 왼쪽으로 밀어냄
					m_balls[b].x = m_barX - m_balls[b].size;
				}
			}
		}
		// Goal 충돌 판정
		if (m_balls[b].x < goalX + goalCollisionWidth &&
			m_balls[b].x + m_balls[b].size > goalX &&
			m_balls[b].y < goalY + goalCollisionHeight &&
			m_balls[b].y + m_balls[b].size > goalY)
		{
			// Goal에 들어간 공 제거
			m_balls[b].active = false;

			// 점수 증가
			m_score++;

			// 이 공은 더 이상 Out 판정을 하지 않음
			continue;
		}
		//공 아웃되면 제거
		if (m_balls[b].x + m_balls[b].size < 0 ||
			m_balls[b].x > screen_width ||
			m_balls[b].y + m_balls[b].size < 0 ||
			m_balls[b].y > screen_Length)
		{
			m_balls[b].active = false;
		}
	}
	//게임 오버 규칙
	int activeBallCount = 0;

	for (int i = 0; i < m_ballCount; i++)
	{
		// 아직 살아있는 공이 있으면 개수 증가
		if (m_balls[i].active == true)
		{
			activeBallCount++;
		}
	}
	// 살아있는 공이 하나도 없으면 게임 종료
	if (activeBallCount == 0)
	{
		// 최종 점수를 넘기면서 RESULT 화면으로 이동
		g_app.ShowResult(m_score);
	}
	return 0;
}

int SceneGamePlay::Render()
{
	//장애물 출력
	for (int i = 0; i < m_obstacleCount; i++)												//개수만큼 넣기
	{
		// 현재 장애물의 위치
		VEC2 position_Obstacle{(float)m_obstacles[i].x, (float)m_obstacles[i].y};			//장애물 위치
		float imageWidth = (float)g2_TextureWidth(m_txObstacle_square);
		float imageLength = (float)g2_TextureHeight(m_txObstacle_square);
		VEC2 scale_Obstacle{(float)m_obstacles[i].width / imageWidth, (float)m_obstacles[i].Length / imageLength};
		g2_Draw2D(m_txObstacle_square, nullptr, &position_Obstacle,&scale_Obstacle);				//출력
	}
	//골 출력 좌표 계산
	{
		// 화면 크기
		float screenWidth = (float)g2_GetScnW();
		float screenLength = (float)g2_GetScnH();
		// Goal 크기
		float goalScale = 0.12f;
		float goalWidth = g2_TextureWidth(m_txGoal) * goalScale;
		float goalLength = g2_TextureHeight(m_txGoal) * goalScale;

		VEC2 position_Goal{ (screenWidth - goalWidth) / 2.0f, (screenLength - goalLength) / 2.0f };// 화면 중앙 - Goal 크기의 절반
		VEC2 scale_Goal{goalScale, goalScale};

		g2_Draw2D(m_txGoal, nullptr, &position_Goal, &scale_Goal);
	}
	//플레이화면 공 출력
	for (int i = 0; i < m_ballCount; i++)
	{
		// 제거된 공은 그리지 않음
		if (m_balls[i].active == false)
		{
			continue;
		}
		// 현재 공의 위치
		VEC2 position_Ball{m_balls[i].x, m_balls[i].y};
		// 공 이미지 크기
		VEC2 scale_Ball{0.05f, 0.05f};

		// 공 출력
		g2_Draw2D(m_txBall, nullptr, &position_Ball, &scale_Ball);
	}
	// bar 출력
	{
		VEC2 position_Bar{ (float)m_barX, (float)m_barY };
		//플레이화면 가로바 출력
		if (m_barSide == BarSide::TOP || m_barSide == BarSide::BOTTOM)
		{
			VEC2 scale_UI(1.0f, 1.0f);														//가로바 크기
			g2_Draw2D(m_txBar_width, nullptr, &position_Bar, &scale_UI);					//출력
		}
		//플레이화면 세로바 출력
		else
		{
			VEC2 scale_UI(1.0f, 1.0f);														//세로바 크기
			g2_Draw2D(m_txBar_Length, nullptr, &position_Bar, &scale_UI);					//출력
		}
	}

	return 0;
}


int SceneGamePlay::Destroy()
{
	//이미지 그림 제거
	g2_TextureRelease(m_txBall);
	g2_TextureRelease(m_txBar_width);
	g2_TextureRelease(m_txBar_Length);
	g2_TextureRelease(m_txObstacle_square);
	g2_TextureRelease(m_txGoal);

	//이미지 번호 초기화
	m_txBall = -1;
	m_txBar_Length = -1;
	m_txBar_width = -1;
	m_txObstacle_square = -1;
	m_txGoal = -1;

	return 0;
}