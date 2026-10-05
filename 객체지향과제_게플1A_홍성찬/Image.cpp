#include "Image.h"

Image::Image()
{
}

Image::~Image()
{
}

int Image::Update(float deltaTime)
{
	return 0;
}

int Image::Render()
{
	g2_Draw2D(m_image.texture, NULL, &m_pos, &m_image.scaling);

	return 0;
}