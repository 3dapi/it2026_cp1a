#pragma once

class CMap
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	int m_TxMap = -1;
};

