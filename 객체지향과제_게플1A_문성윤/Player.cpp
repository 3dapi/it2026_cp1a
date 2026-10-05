#include "Player.h"

void Player::Init()
{
    m_hp = 100;
    m_life = 3;
    m_score = 0;
}

void Player::TakeDamage(int damage)
{
    if (damage <= 0 || m_hp == 0)
        return;

    m_hp = damage >= m_hp ? 0 : m_hp - damage;
    if (m_hp == 0)
        --m_life;
}

void Player::Heal(int amount)
{
    if (amount <= 0 || m_hp == 0)
        return;

    m_hp = amount >= 100 - m_hp ? 100 : m_hp + amount;
}

void Player::AddScore(int amount)
{
    if (amount <= 0 || m_hp == 0)
        return;

    m_score = amount >= 120 - m_score ? 120 : m_score + amount;
}

void Player::Retry()
{
    if (m_hp == 0 && m_life > 0)
        m_hp = 100;
}
