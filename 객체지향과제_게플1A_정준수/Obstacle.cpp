#include "Obstacle.h"

Obstacle::Obstacle()
    : m_x(520.0f), m_y(130.0f), m_speed(150.0f), m_index(0)
{
}

void Obstacle::Init()
{
    m_index = 0;
    m_x = 520.0f;
    m_y = 130.0f;
}

void Obstacle::Update(float dt)
{
    m_y += m_speed * dt;

    if (m_y > 520.0f)
        Reset();
}

void Obstacle::Reset()
{
    const float positions[4] = { 130.0f, 320.0f, 520.0f, 680.0f };

    ++m_index;
    if (m_index >= 4)
        m_index = 0;

    m_x = positions[m_index];
    m_y = 125.0f;
}
