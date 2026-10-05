#pragma once
class SceneGameResult
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

	// PLAY Scene에서 최종 점수를 전달받음
	void SetScore(int score);

protected:
	int m_score = 0;

	// 폰트 번호
	int m_fontTitle = -1;
	int m_fontMenu = -1;
};