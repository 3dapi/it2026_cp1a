#include "Dice.h"
#include "glc2d.h"
#include <stdio.h>
#include <random>

bool Dice::Init()
{
    Destroy();
    for (int i = 0; i < 6; ++i)
    {
        char path[64];
        sprintf_s(path, "texture/dice_%d.png", i + 1);
        m_textures[i] = g2_TextureLoad(path);
        if (m_textures[i] < 0)
        {
            printf("Failed to load: %s\n", path);
            Destroy();
            return false;
        }
    }
    Roll();
    return true;
}

void Dice::Roll()
{
    for (int i = 0; i < Count; ++i) RollOne(i);
}

void Dice::RollOne(int index)
{
    if (index < 0 || index >= Count) return;
    static std::mt19937 generator(std::random_device{}());
    static std::uniform_int_distribution<int> distribution(1, 6);
    m_numbers[index] = distribution(generator);
}

void Dice::Update()
{
    const KEYCODE* keys = g2_GetKeyboard();
    if (!keys)
    {
        m_spacePressed = false;
        return;
    }
    const bool pressed = keys[VK_SPACE] != 0;
    if (pressed && !m_spacePressed)
        Roll();
    m_spacePressed = pressed;
}

void Dice::Render(float x, float y, float size)
{
    for (int i = 0; i < Count; ++i)
        RenderOne(i, x + (i % 3) * size * 1.2f,
                  y + (i / 3) * size * 1.2f, size);
}

void Dice::RenderOne(int index, float x, float y, float size)
{
    if (index < 0 || index >= Count || size <= 0.0f) return;
    const int texture = m_textures[m_numbers[index] - 1];
    if (texture < 0) return;
    const int width = g2_TextureWidth(texture);
    const int height = g2_TextureHeight(texture);
    if (width <= 0 || height <= 0) return;
    const float ratio = size / (width > height ? width : height);
    VEC2 position(x + (size - width * ratio) * 0.5f,
                  y + (size - height * ratio) * 0.5f);
    VEC2 scaling(ratio, ratio);
    g2_DrawAlphaOption(0);
    g2_Draw2D(texture, nullptr, &position, &scaling);
}

void Dice::Destroy()
{
    for (int i = 0; i < 6; ++i)
    {
        if (m_textures[i] >= 0)
            g2_TextureRelease(m_textures[i]);
        m_textures[i] = -1;
    }
    m_spacePressed = false;
}