#pragma once

class Dice
{
public:
    static constexpr int Count = 5;
    bool Init();
    void Update();
    void Roll();
    void RollOne(int index);
    void RenderOne(int index, float x, float y, float size);
    void Render(float x, float y, float size = 100.0f);
    void Destroy();
    int GetNumber(int index = 0) const
    { return index >= 0 && index < Count ? m_numbers[index] : -1; }

private:
    // 1부터 6까지의 주사위 이미지 번호
    int m_textures[6] = { -1, -1, -1, -1, -1, -1 };


    // 화면에 있는 주사위 다섯 개의 현재 숫자
    int m_numbers[Count] = { 1, 1, 1, 1, 1 };
    bool m_spacePressed = false;
};