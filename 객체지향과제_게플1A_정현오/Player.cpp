#include "Player.h"

int Player::Init()
{
    m_txPlayer = g2_TextureLoad("resource/texture/tex_object/player.png");
    m_txDead = g2_TextureLoad("resource/texture/tex_object/playerDead.png");

    transform.position = { 99.5f, 542.5f };
    transform.scale = { 1.5f, 1.5f };
    transform.center = { 16, 16 };
    m_moveSpeed = 150.0f;
    boxCollider.size = { 32, 32 };
    isDead = false;

    return 0;
}

int Player::Update(float deltaTime)
{
    if (isDead)
    {
        return 0;
    }

    const KEYCODE* keyboard = g2_GetKeyboard();

    if (keyboard['A'])
    {
        m_direction = Direction::LEFT;
    }

    if (keyboard['D'])
    {
        m_direction = Direction::RIGHT;
    }

    if (keyboard['A'] == keyboard['D'])
    {
        return 0;
    }

    Move(m_direction, deltaTime);

    return 0;
}

int Player::Render()
{
    VEC2 renderCenter = GetCenter();
    float renderRotation = GetRotation();

    if (isDead)
    {
        g2_Draw2D(m_txDead, nullptr, &transform.position, &transform.scale, &renderCenter, renderRotation);
        return 0;
    }

    g2_Draw2D(m_txPlayer, nullptr, &transform.position, &transform.scale, &renderCenter, renderRotation);
    return 0;
}

int Player::Destroy()
{
    g2_TextureRelease(m_txPlayer);
    g2_TextureRelease(m_txDead);
    return 0;
}

void Player::SetDead()
{
    isDead = true;
}