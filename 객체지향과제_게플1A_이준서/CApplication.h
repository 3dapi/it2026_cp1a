#pragma once
#include <chrono>
#include "glc2d.h"
#include "SceneGameBegin.h"
#include "SceneGamePlay.h"
#include "SceneGameResult.h"

enum class Screen { Title, Play, Result };
enum ImageId { TitleImage, BackgroundImage, ZombieIdle, ZombieHit, HeartFull, HeartEmpty, ImageCount };
enum SoundId { Music, CorrectSound, WrongSound, GameOverSound, SoundCount };

class CApplication
{
public:
    int Init();
    int Render();
    int Update();
    int Destroy();
    void StartGame();
    void FinishGame();
    bool Pressed(int key) const { return m_pressedKeys[key]; }
    void DrawImage(ImageId image, float x, float y, float width, float height, DWORD color = 0xFFFFFFFF);
    void PlaySound(SoundId sound, bool loop = false);
    int m_font = -1;
    int m_largeFont = -1;
    int m_keyFont = -1;
    Screen m_screen = Screen::Title;
    SceneGameBegin m_sceneBegin;
    SceneGamePlay m_scenePlay;
    SceneGameResult m_sceneResult;
private:
    int m_images[ImageCount]{};
    int m_sounds[SoundCount]{};
    bool m_previousKeys[256]{};
    bool m_pressedKeys[256]{};
    std::chrono::steady_clock::time_point m_lastTime;
};
extern CApplication g_app;
