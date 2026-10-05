#include "Game.h"
#include <glc2d.h>
#include <Windows.h>
#include <cmath>
#include <cstdio>

void Game::Init()
{
    m_backgroundTexture = g2_TextureLoad("resource/image/background.png");
    m_playerTexture = g2_TextureLoad("resource/image/player.png");
    m_targetTexture = g2_TextureLoad("resource/image/goal.png");
    m_targetAltTexture = g2_TextureLoad("resource/image/goal_alt.png");
    m_obstacleTexture = g2_TextureLoad("resource/image/obstacle.png");
    m_obstacleAltTexture = g2_TextureLoad("resource/image/obstacle_alt.png");
    m_titleTexture = g2_TextureLoad("resource/image/title.png");
    m_startPromptTexture = g2_TextureLoad("resource/image/start_prompt.png");
    m_hudTexture = g2_TextureLoad("resource/image/hud_panel.png");
    m_clearTexture = g2_TextureLoad("resource/image/clear_panel.png");
    m_failTexture = g2_TextureLoad("resource/image/fail_panel.png");

    for (int i = 0; i < 10; ++i)
    {
        char path[128];
        sprintf_s(path, "resource/image/digit_%d.png", i);
        m_digitTextures[i] = g2_TextureLoad(path);
    }

    m_player.Init();
    m_target.Init();
    m_obstacle.Init();
    m_state = GameState::Start;
    m_score = 0;
    m_remainingTime = m_gameTime;
    m_animTime = 0.0f;
    m_startButtonDown = false;
}

void Game::StartGame()
{
    m_player.Init();
    m_target.Init();
    m_obstacle.Init();
    m_score = 0;
    m_clear = false;
    m_remainingTime = m_gameTime;
    m_animTime = 0.0f;
    m_state = GameState::Play;

    m_sound.PlayStart();
    m_sound.PlayBgm();
}

void Game::FinishGame(bool clear)
{
    m_clear = clear;
    m_state = GameState::Result;
    m_sound.StopBgm();

    if (clear)
        m_sound.PlayClear();
    else
        m_sound.PlayFail();
}

void Game::Update(float dt)
{
    const bool enterDown = (GetAsyncKeyState(VK_RETURN) & 0x8000) != 0;
    const bool spaceDown = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
    const bool mouseDown = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    const bool focused = GetForegroundWindow() == g2_GetHwnd();
    const bool startDown = focused && (enterDown || spaceDown || mouseDown);

    if (m_state == GameState::Start)
    {
        // Enter / Space / 마우스 클릭으로 시작한다.
        if (startDown && !m_startButtonDown)
            StartGame();
    }
    else if (m_state == GameState::Result)
    {
        if (startDown && !m_startButtonDown)
            StartGame();
    }

    m_startButtonDown = startDown;

    m_sound.Update();

    if (m_state == GameState::Play)
        UpdatePlay(dt);
}

void Game::UpdatePlay(float dt)
{
    m_animTime += dt;
    m_player.Update(dt);
    m_obstacle.Update(dt);

    if (IsHit(m_player.GetX(), m_player.GetY(), m_player.GetWidth(), m_player.GetHeight(),
              m_target.GetX(), m_target.GetY(), m_target.GetWidth(), m_target.GetHeight()))
    {
        m_score += 10;
        m_target.MoveNext();
        m_sound.PlayCollect();
    }

    if (IsHit(m_player.GetX(), m_player.GetY(), m_player.GetWidth(), m_player.GetHeight(),
              m_obstacle.GetX(), m_obstacle.GetY(), m_obstacle.GetWidth(), m_obstacle.GetHeight()))
    {
        m_player.Damage();
        m_obstacle.Reset();
        m_sound.PlayHit();
    }

    m_remainingTime -= dt;
    if (m_remainingTime < 0.0f)
        m_remainingTime = 0.0f;

    if (m_score >= 100)
        FinishGame(true);
    else if (m_player.GetLife() <= 0 || m_remainingTime <= 0.0f)
        FinishGame(false);
}

bool Game::IsHit(float ax, float ay, float aw, float ah,
                 float bx, float by, float bw, float bh) const
{
    return ax < bx + bw && ax + aw > bx &&
           ay < by + bh && ay + ah > by;
}

void Game::Render()
{
    VEC2 backgroundPos(0.0f, 0.0f);
    g2_Draw2D(m_backgroundTexture, {}, &backgroundPos);

    if (m_state == GameState::Start)
        RenderStart();
    else if (m_state == GameState::Play)
        RenderPlay();
    else
        RenderResult();
}

void Game::RenderStart()
{
    VEC2 titlePos(140.0f, 130.0f);
    VEC2 promptPos(235.0f, 315.0f);
    VEC2 playerPos(165.0f, 405.0f);
    VEC2 targetPos(585.0f, 392.0f);

    g2_Draw2D(m_titleTexture, {}, &titlePos);
    g2_Draw2D(m_startPromptTexture, {}, &promptPos);
    g2_Draw2D(m_playerTexture, {}, &playerPos);
    g2_Draw2D(m_targetTexture, {}, &targetPos);
}

void Game::RenderPlay()
{
    VEC2 hudPos(20.0f, 18.0f);
    VEC2 obstaclePos(m_obstacle.GetX(), m_obstacle.GetY());
    VEC2 playerPos(m_player.GetX(), m_player.GetY());

    g2_Draw2D(m_hudTexture, {}, &hudPos);

    VEC2 targetPos(m_target.GetX(), m_target.GetY());
    int targetFrame = ((int)(m_animTime * 5.0f) % 2 == 0) ? m_targetTexture : m_targetAltTexture;
    g2_Draw2D(targetFrame, {}, &targetPos);

    int obstacleFrame = ((int)(m_animTime * 8.0f) % 2 == 0) ? m_obstacleTexture : m_obstacleAltTexture;
    g2_Draw2D(obstacleFrame, {}, &obstaclePos);
    g2_Draw2D(m_playerTexture, {}, &playerPos);

    DrawNumber(m_score, 95.0f, 28.0f, 3);
    DrawNumber(m_player.GetLife(), 195.0f, 28.0f, 1);
    DrawNumber((int)std::ceil(m_remainingTime), 300.0f, 28.0f, 2);
}

void Game::RenderResult()
{
    VEC2 panelPos(205.0f, 210.0f);

    if (m_clear)
        g2_Draw2D(m_clearTexture, {}, &panelPos);
    else
        g2_Draw2D(m_failTexture, {}, &panelPos);

    DrawNumber(m_score, 365.0f, 350.0f, 3);
}

void Game::DrawNumber(int value, float x, float y, int minDigits)
{
    if (value < 0)
        value = 0;

    char text[16];
    sprintf_s(text, "%0*d", minDigits, value);

    for (int i = 0; text[i] != '\0'; ++i)
    {
        int digit = text[i] - '0';
        if (digit >= 0 && digit <= 9)
        {
            VEC2 pos(x + i * 25.0f, y);
            g2_Draw2D(m_digitTextures[digit], {}, &pos);
        }
    }
}

void Game::Release()
{
    m_sound.Stop();

    g2_TextureRelease(m_backgroundTexture);
    g2_TextureRelease(m_playerTexture);
    g2_TextureRelease(m_targetTexture);
    g2_TextureRelease(m_targetAltTexture);
    g2_TextureRelease(m_obstacleTexture);
    g2_TextureRelease(m_obstacleAltTexture);
    g2_TextureRelease(m_titleTexture);
    g2_TextureRelease(m_startPromptTexture);
    g2_TextureRelease(m_hudTexture);
    g2_TextureRelease(m_clearTexture);
    g2_TextureRelease(m_failTexture);

    for (int i = 0; i < 10; ++i)
        g2_TextureRelease(m_digitTextures[i]);
}
