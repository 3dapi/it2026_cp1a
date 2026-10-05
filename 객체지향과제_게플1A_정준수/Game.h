#pragma once
#include "Player.h"
#include "Target.h"
#include "Obstacle.h"
#include "SoundManager.h"

enum class GameState
{
    Start,
    Play,
    Result
};

class Game
{
public:
    void Init();
    void Update(float dt);
    void Render();
    void Release();

private:
    void StartGame();
    void FinishGame(bool clear);
    void UpdatePlay(float dt);
    void RenderStart();
    void RenderPlay();
    void RenderResult();
    void DrawNumber(int value, float x, float y, int minDigits = 1);
    bool IsHit(float ax, float ay, float aw, float ah,
               float bx, float by, float bw, float bh) const;

private:
    Player m_player;
    Target m_target;
    Obstacle m_obstacle;
    SoundManager m_sound;

    GameState m_state = GameState::Start;
    int m_score = 0;
    bool m_clear = false;
    bool m_startButtonDown = false;

    int m_backgroundTexture = -1;
    int m_playerTexture = -1;
    int m_targetTexture = -1;
    int m_targetAltTexture = -1;
    int m_obstacleTexture = -1;
    int m_obstacleAltTexture = -1;
    int m_titleTexture = -1;
    int m_startPromptTexture = -1;
    int m_hudTexture = -1;
    int m_clearTexture = -1;
    int m_failTexture = -1;
    int m_digitTextures[10] = {};

    const float m_gameTime = 45.0f;
    float m_remainingTime = 45.0f;
    float m_animTime = 0.0f;
};
