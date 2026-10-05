#pragma once
	
enum class BarSide											//바의 위치 나타내는 상수
{
	TOP,
	RIGHT,
	BOTTOM,
	LEFT
};
struct Obstacle												//장애물 정보 구조체
{
	int x;													// 장애물의 x좌표		
	int y;													// 장애물의 y좌표
	int width;												// 장애물의 가로 크기
	int Length;												// 장애물의 세로 크기
};
struct Ball													//공 정보 구조체
{
	float x;												//공 x좌표
	float y;												//공 y좌표

	float speedX;											//공 x방향 속도
	float speedY;											//공 y방향 속도

	int size;												//공 충돌 크기
	bool active;											//현재 살아있는 공인지
};

class SceneGamePlay
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	//이미지 사용 변수 선언
	int m_txBall = -1;
	int m_txBar_width = -1;
	int m_txBar_Length = -1;
	int m_txObstacle_square = -1;
	int m_txGoal = -1;

protected:
	// bar의 화면 좌표
	int m_barX = 0;
	int m_barY = 0;

	// bar의 길이와 두께
	int m_barLength = 180;			//길이
	int m_barThickness = 25;		//두꼐

	//bar가 현재 어느 벽에 있는지 저장
	BarSide m_barSide = BarSide::BOTTOM;

protected:
	int m_ballCount = 5;						//공 개수
	Ball m_balls[5];							//공 배열

protected:
	//장애물 개수
	int m_obstacleCount = 16;
	Obstacle m_obstacles[16];

protected:
	int m_score = 0;							//점수
};