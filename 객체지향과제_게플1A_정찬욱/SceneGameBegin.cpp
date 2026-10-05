#include "SceneGameBegin.h"
#include "glc2d.h"
#include <stdio.h>

// 이미지를 지정한 영역에 그립니다.
// keepRatio가 true면 원본 비율을 유지합니다.
static void DrawImage(
    int texture,
    float x, float y,
    float width, float height,
    bool keepRatio)
{
    if (texture < 0)
        return;

    int imageWidth = g2_TextureWidth(texture);
    int imageHeight = g2_TextureHeight(texture);

    if (imageWidth <= 0 || imageHeight <= 0)
        return;

    float scaleX = width / imageWidth;
    float scaleY = height / imageHeight;

    if (keepRatio)
    {
        float scale = scaleX < scaleY ? scaleX : scaleY;

        scaleX = scale;
        scaleY = scale;

        // 지정한 영역의 가운데에 배치
        x += (width - imageWidth * scale) / 2.0f;
        y += (height - imageHeight * scale) / 2.0f;
    }

    VEC2 position(x, y);
    VEC2 scaling(scaleX, scaleY);

    g2_Draw2D(texture, nullptr, &position, &scaling);
}

int SceneGameBegin::Init()
{
    g2_SetClearColor(0xFF263447);

    m_floor = g2_TextureLoad("texture/floor.png");
    m_basket = g2_TextureLoad("texture/basket.png");
    m_scoreboard = g2_TextureLoad("texture/scoreboard.png");

    if (m_floor < 0)
        printf("Failed to load texture/floor.png\n");

    if (m_basket < 0)
        printf("Failed to load texture/basket.png\n");

    if (m_scoreboard < 0)
        printf("Failed to load texture/scoreboard.png\n");

    if (!m_playSysteam.Init()) return -1;
    return 0;
}

int SceneGameBegin::Update()
{
    m_playSysteam.Update();
    return 0;
}

int SceneGameBegin::Render()
{

    // 바닥: 화면 아래에 가로로 펼치기
    DrawImage(m_floor, 0, 0, 1280, 720, false);

    // 바구니: 오른쪽, 원본 비율 유지
    DrawImage(m_basket, 330, 60, 800, 600, true);
    m_playSysteam.Render();

    // 점수판: 왼쪽, 원본 비율 유지
    DrawImage(m_scoreboard, 20, 60, 300, 600, false);
    m_playSysteam.RenderScoreboard();

    g2_DrawAlphaOption(0);

    return 0;
}

int SceneGameBegin::Destroy()
{
    m_playSysteam.Destroy();
    if (m_floor >= 0)
        g2_TextureRelease(m_floor);

    if (m_basket >= 0)
        g2_TextureRelease(m_basket);

    if (m_scoreboard >= 0)
        g2_TextureRelease(m_scoreboard);

    m_floor = -1;
    m_basket = -1;
    m_scoreboard = -1;

    return 0;
}