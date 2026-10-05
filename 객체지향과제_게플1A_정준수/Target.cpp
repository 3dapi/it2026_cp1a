#include "Target.h"

Target::Target()
    : m_x(120.0f), m_y(390.0f), m_index(0)
{
}

void Target::Init()
{
    m_index = 0;
    m_x = 120.0f;
    m_y = 390.0f;
}

void Target::MoveNext()
{
    const float positions[5] = { 80.0f, 220.0f, 360.0f, 510.0f, 660.0f };

    ++m_index;
    if (m_index >= 5)
        m_index = 0;

    m_x = positions[m_index];
}
