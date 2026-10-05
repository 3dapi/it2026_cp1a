#include "Rock.h"

int Rock::Init()
{
    m_txRock = g2_TextureLoad("resource/texture/tex_object/rock.png");

    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    std::uniform_int_distribution<int> dist(0, 300);
    float posX = static_cast<float>(dist(gen));

    transform.position = { posX, -80.0f };
    transform.scale = { 3, 3 };
    transform.center = { 10, 10 };
    m_moveSpeed = 500.0f;
    boxCollider.size = { 16, 16 };

    return 0;
}

int Rock::Update(float deltaTime)
{
    Move(m_direction, deltaTime);
   
    return 0;
}

int Rock::Render()
{
    VEC2 renderCenter = GetCenter();
    float renderRotation = GetRotation();

    g2_Draw2D(m_txRock,
              nullptr,
              &transform.position,
              &transform.scale,
              &renderCenter,
              renderRotation);
    return 0;
}

int Rock::Destroy()
{
    g2_TextureRelease(m_txRock);
    return 0;
}