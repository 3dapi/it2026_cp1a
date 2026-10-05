#include <glc2d.h>
#include <chrono>
#include "Game.h"

#if defined(_DEBUG)
    #if defined(_M_X64)
        #pragma comment(lib, "glc2d_x64_debug.lib")
    #elif defined(_M_IX86)
        #pragma comment(lib, "glc2d_win32_debug.lib")
    #endif
#else
    #if defined(_M_X64)
        #pragma comment(lib, "glc2d_x64_release.lib")
    #elif defined(_M_IX86)
        #pragma comment(lib, "glc2d_win32_release.lib")
    #endif
#endif

Game g_game;
static std::chrono::steady_clock::time_point g_prevTime;

int AppUpdate()
{
    const auto now = std::chrono::steady_clock::now();
    float dt = std::chrono::duration<float>(now - g_prevTime).count();
    g_prevTime = now;

    if (dt < 0.0f)
        dt = 0.0f;
    if (dt > 0.05f)
        dt = 0.05f;

    g_game.Update(dt);
    return 0;
}

int AppRender()
{
    g_game.Render();
    return 0;
}

int main()
{
    const int sdkResult = g2_InitSdk();
    if (sdkResult < 0) return 1;
    g2_SetClearColor(0xFF111827);

    g2_SetFrameMove(AppUpdate);
    g2_SetRender(AppRender);
    const int windowResult = g2_CreateWin(100, 100, 800, 600, "Target Catch - Final", true);
    if (windowResult < 0) return 1;

    g_game.Init();
    g_prevTime = std::chrono::steady_clock::now();

    g2_Run();

    g_game.Release();
    g2_DestroyWin();
    return 0;
}
