#pragma once

class Target
{
public:
    Target();

    void Init();
    void MoveNext();

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
    float GetWidth() const { return 54.0f; }
    float GetHeight() const { return 54.0f; }

private:
    float m_x;
    float m_y;
    int m_index;
};
