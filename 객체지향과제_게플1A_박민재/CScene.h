#pragma once

class CApplication;

class CScene
{
public:
	virtual int Init();
	virtual int Update();
	virtual int Render(CApplication& application) = 0;
	virtual int Destroy();

	virtual ~CScene() = default; // 가상 소멸자 추가

protected:
	int sceneNum = -1;
};

