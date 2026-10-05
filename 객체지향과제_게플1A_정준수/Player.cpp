#include "Player.h"
#include <Windows.h>

Player::Player()
    : m_x(360.0f), m_y(405.0f), m_speed(260.0f), m_life(3)
{
}

void Player::Init()
{
    m_x = 360.0f;
    m_y = 405.0f;
    m_life = 3;
}

void Player::Update(float dt)
{
    if ((GetAsyncKeyState('A') & 0x8000) ||
        (GetAsyncKeyState(VK_LEFT) & 0x8000))
        m_x -= m_speed * dt;

    if ((GetAsyncKeyState('D') & 0x8000) ||
        (GetAsyncKeyState(VK_RIGHT) & 0x8000))
        m_x += m_speed * dt;

    if (m_x < 0.0f) m_x = 0.0f;
    if (m_x > 736.0f) m_x = 736.0f;
}

void Player::Damage()
{
    if (m_life > 0)
        --m_life;
}
