#pragma once
#include "glc2d.h"
#include <string>

class SceneGameBegin
{
public:
	int Init();
	int Update();
	int Render();
	int Destroy();

protected:
	// game texture
	int m_txTitle		{ -1 };


	// game font
	int	m_fntMessage	{ -1 };

	std::string m_startText{ "Enter 키를 눌러 시작" };

	// text blink
	static constexpr long long BLINK_INTERVAL{ 500 };
	bool m_isTextVisible{ true };
	

	// game position
	VEC2 m_titlePos		{ 360, 215 };


};

