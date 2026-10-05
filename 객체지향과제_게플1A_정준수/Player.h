#pragma once

class Player
{
public:
    Player();

    void Init();
    void Update(float dt);
    void Damage();

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetWidth() const { return 64.0f; }
    float GetHeight() const { return 64.0f; }
    int GetLife() const { return m_life; }

private:
    float m_x;
    float m_y;
    float m_speed;
    int m_life;
};
