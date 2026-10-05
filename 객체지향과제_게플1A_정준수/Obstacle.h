#pragma once

class Obstacle
{
public:
    Obstacle();

    void Init();
    void Update(float dt);
    void Reset();

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetWidth() const { return 54.0f; }
    float GetHeight() const { return 54.0f; }

private:
    float m_x;
    float m_y;
    float m_speed;
    int m_index;
};
