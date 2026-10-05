#pragma once
#include "glc2d.h"

class CEnemy
{
public:
    int Init(int texture_right, int texture_left);
    int Update(float playerX, float playerY);
    int Render();
    int Destroy();

    void TakeDamage(int damage);
    bool IsDead();

    // 적 객체 위치 함수
    VEC2 GetPosition();
    void SetPosition(float x, float y);

    // Rect 범위 함수 (충돌)
    RECT GetCollisionRect();

    // Monster Pool
    void Activate(float x, float y);
    void Deactivate();
    bool IsActive();

private:
    float m_PosX = 800.0f;
    float m_PosY = 800.0f;

    VEC2 m_Draw_Pos;

    float m_Width{};
    float m_Height{};

    VEC2 m_Scale = { 0.3f, 0.3f };

    // 기본 스탯
    int m_MaxHp = 50;
    int m_CurHp = 50;

    int m_Damage = 10;
    float m_Speed = 0.02f;

    // 스폰 여부
    bool m_Active = false;

    bool m_IsLeft = false;

    int m_Boar_right_tx = -1;
    int m_Boar_left_tx = -1;
};

