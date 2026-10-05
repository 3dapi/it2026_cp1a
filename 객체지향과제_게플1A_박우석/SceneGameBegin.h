#pragma once
class SceneGameBegin
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	
	int m_txbg = -1;
	int m_tx1 = -1;
	int m_tx2 = -1;
	int m_tx3 = -1;
	int m_tx4 = -1;
	int m_tx5 = -1;
	int m_tx6 = -1;

protected:
	int Ysound = -1;

protected:
	int Font1 = -1;
	int Font2 = -1;
	int Font3 = -1;

};

