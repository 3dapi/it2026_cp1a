#include "Obstacle.h"

Obstacle::Obstacle()
{

}

Obstacle::~Obstacle()
{
}

int Obstacle::Update(float deltaTime)
{
	if (m_tag != Tag::Obstacle)
		return 0;
	m_pos.x -= m_moveSpeed * deltaTime;

	if (GetLeft() <= -m_collider.width - 5)
		m_isActive = false;

	return 0;
}

int Obstacle::Render()
{
	g2_Draw2D(m_image.texture, NULL, &m_pos, &m_image.scaling);

	return 0;
}