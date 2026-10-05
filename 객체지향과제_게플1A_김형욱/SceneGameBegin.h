#pragma once

class SceneGameBegin
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	//이미지 사용 변수 선언
	int m_txBG = -1;
	int m_txUI_start = -1;
	int m_txUI_exit = -1;
};	