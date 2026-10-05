#include "CApplication.h"
#include <algorithm>
#include <cstdio>

namespace
{
    int UpdateAPP() { return g_app.Update(); }
    int RenderAPP() { return g_app.Render(); }
}

int CApplication::Init()
{
    g2_InitSdk();
    // glc2d forwards this flag to g2_ChangeWindow: true means windowed.
    g2_CreateWin(100, 100, 1280, 720, "Zombie Keyboard Defense", true);
    g2_SetFrameMove(UpdateAPP);
    g2_SetRender(RenderAPP);
    g2_SetClearColor(0xFF101923);
    g2_SetStateShow(false);
    const char* images[ImageCount] = {
        "rsc/imgs/Title.png", "rsc/imgs/zombie_street_bg.png",
        "rsc/imgs/Zombie_Idle.png", "rsc/imgs/Zombie_Hit.png",
        "rsc/imgs/Heart_Full.png", "rsc/imgs/Heart_Empty.png"
    };
    for (int i = 0; i < ImageCount; ++i)
    {
        m_images[i] = g2_TextureLoad(images[i], 0);
        if (g2_TextureWidth(m_images[i]) <= 0)
            std::fprintf(stderr, "Cannot load image: %s\n", images[i]);
    }
    const char* sounds[SoundCount] = {
        "rsc/audio/BGM.mp3", "rsc/audio/SFX/Correct.mp3",
        "rsc/audio/SFX/Wrong.mp3", "rsc/audio/SFX/GameOver.mp3"
    };
    for (int i = 0; i < SoundCount; ++i)
        m_sounds[i] = g2_SoundLoad(sounds[i]);
    m_font = g2_FontCreate("Arial", 28);
    m_largeFont = g2_FontCreate("Arial", 56);
    m_keyFont = g2_FontCreate("Arial", 100);
    m_lastTime = std::chrono::steady_clock::now();
    return 0;
}

int CApplication::Update()
{
    const auto now = std::chrono::steady_clock::now();
    const float deltaTime = (std::min)(0.1f, std::chrono::duration<float>(now - m_lastTime).count());
    m_lastTime = now;
    const bool focused = GetForegroundWindow() == g2_GetHwnd();
    for (int i = 0; i < 256; ++i)
    {
        const bool down = (GetAsyncKeyState(i) & 0x8000) != 0;
        m_pressedKeys[i] = focused && down && !m_previousKeys[i];
        m_previousKeys[i] = down;
    }
    if (!focused) return 0;
    if (Pressed(VK_ESCAPE))
    {
        PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
        return 0;
    }
    switch (m_screen)
    {
    case Screen::Title: m_sceneBegin.Update(); break;
    case Screen::Play: m_scenePlay.Update(deltaTime); break;
    case Screen::Result: m_sceneResult.Update(); break;
    }
    return 0;
}

int CApplication::Render()
{
    switch (m_screen)
    {
    case Screen::Title: m_sceneBegin.Render(); break;
    case Screen::Play: m_scenePlay.Render(); break;
    case Screen::Result: m_sceneResult.Render(); break;
    }
    return 0;
}

void CApplication::StartGame()
{
    m_screen = Screen::Play;
    m_scenePlay.Init();
    PlaySound(Music, true);
}

void CApplication::FinishGame()
{
    m_screen = Screen::Result;
    g2_SoundStop(m_sounds[Music]);
    PlaySound(GameOverSound);
}

void CApplication::DrawImage(ImageId image, float x, float y, float width, float height, DWORD color)
{
    const int texture = m_images[image];
    const int w = g2_TextureWidth(texture), h = g2_TextureHeight(texture);
    if (w <= 0 || h <= 0) return;
    const VEC2 pos{ x, y }, scale{ width / w, height / h };
    g2_Draw2D(texture, nullptr, &pos, &scale, nullptr, 0, color);
}

void CApplication::PlaySound(SoundId sound, bool loop)
{
    if (m_sounds[sound] < 0) return;
    g2_SoundStop(m_sounds[sound]);
    g2_SoundReset(m_sounds[sound]);
    g2_SoundPlay(m_sounds[sound], loop);
}

int CApplication::Destroy()
{
    for (int sound : m_sounds) if (sound >= 0) g2_SoundRelease(sound);
    for (int texture : m_images) if (texture >= 0) g2_TextureRelease(texture);
    g2_DestroyWin();
    return 0;
}
