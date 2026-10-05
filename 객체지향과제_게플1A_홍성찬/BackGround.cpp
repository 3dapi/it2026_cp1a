#include "BackGround.h"

Background::Background()
{
}

Background::~Background()
{
}

int Background::Update(float deltaTime)
{
	return 0;
}

int Background::Render()
{
	//g2_DrawAlphaOption(m_image.alphaOption);
	g2_Draw2D(m_image.texture, NULL, &m_pos, &m_image.scaling);

	return 0;
}