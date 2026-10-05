#include "Game.h"
#include "Ui.h"

#include <atomic>
#include <cstdio>
#include <exception>
#include <thread>

#include <glc2d.h> 

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

namespace
{
    constexpr int kScreenWidth = 1280;
    constexpr int kScreenHeight = 720;
    constexpr int kMenuCount = 3;

    enum class Screen
    {
        Title,
        HowToPlay,
        Playing
    };

    Screen g_screen = Screen::Title;
    int g_selectedMenu = 0;

 
    std::thread g_gameThread;
    std::atomic<bool> g_gameDone{true};

    bool IsKeyPressed(const KEYCODE* keys, int key)
    {
        return keys != nullptr && keys[key] == EINPUT_DOWN;
    }

    void RequestExit()
    {
        PostMessage(g2_GetHwnd(), WM_CLOSE, 0, 0);
    }

    void StartGame()
    {
        ui::resetSession();
        g_gameDone = false;
        g_gameThread = std::thread([]
        {
            try
            {
                Game game;
                game.run();
            }
            catch (const QuitRequested&)
            {
            }
            catch (const std::exception& error)
            {
                std::fprintf(stderr, "game error: %s\n", error.what());
            }
            g_gameDone = true;
        });
        g_screen = Screen::Playing;
    }

    void StopGame()
    {
        ui::requestQuit();
        if (g_gameThread.joinable())
        {
            g_gameThread.join();
        }
        g_gameDone = true;
    }

    void SelectMenuItem()
    {
        switch (g_selectedMenu)
        {
        case 0:
            StartGame();
            break;

        case 1:
            g_screen = Screen::HowToPlay;
            break;

        case 2:
            RequestExit();
            break;

        default:
            break;
        }
    }

    void UpdateTitle(const KEYCODE* keys)
    {
        if (IsKeyPressed(keys, VK_UP) || IsKeyPressed(keys, 'W'))
        {
            g_selectedMenu = (g_selectedMenu + kMenuCount - 1) % kMenuCount;
        }

        if (IsKeyPressed(keys, VK_DOWN) || IsKeyPressed(keys, 'S'))
        {
            g_selectedMenu = (g_selectedMenu + 1) % kMenuCount;
        }

        if (IsKeyPressed(keys, VK_RETURN))
        {
            SelectMenuItem();
        }

        if (IsKeyPressed(keys, VK_ESCAPE))
        {
            RequestExit();
        }
    }

    int FrameMove()
    {
        const KEYCODE* keys = g2_GetKeyboard();

        switch (g_screen)
        {
        case Screen::Title:
            UpdateTitle(keys);
            break;

        case Screen::HowToPlay:
            if (IsKeyPressed(keys, VK_RETURN) || IsKeyPressed(keys, VK_ESCAPE))
            {
                g_screen = Screen::Title;
            }
            break;

        case Screen::Playing:
            if (ui::updateTable())
            {
                ui::requestQuit();
            }
            if (g_gameDone)
            {
                StopGame();
                g_screen = Screen::Title;
            }
            break;
        }

        return 0;
    }

    int Render()
    {
        switch (g_screen)
        {
        case Screen::Title:
            ui::drawTitleScreen(g_selectedMenu);
            break;

        case Screen::HowToPlay:
            ui::drawHowToScreen();
            break;

        case Screen::Playing:
            ui::drawTable();
            break;
        }

        return 0;
    }
}

int main()
{
    const int initResult = g2_InitSdk();
    if (initResult != 0)
    {
        std::fprintf(stderr, "glc2d SDK initialization failed: %d\n", initResult);
        return 1;
    }

    g2_SetClearColor(0xFF101827);
    g2_SetStateShow(0);
    g2_SetCursorShow(0);
    g2_SetFrameMove(FrameMove);
    g2_SetRender(Render);

    const int createResult = g2_CreateWin(
        60,
        30,
        kScreenWidth,
        kScreenHeight,
        "TEXAS HOLD'EM DEEP STACK - glc2d",
        true);

    if (createResult != 0)
    {
        std::fprintf(stderr, "glc2d window creation failed: %d\n", createResult);
        g2_DestroyWin();
        return 1;
    }

    if (!ui::loadAssets())
    {
        std::fprintf(stderr, "Some textures or fonts failed to load. Run from the project folder (it needs Texture/).\n");
    }

    std::printf("Texas Hold'em Deep Stack started. Close the window or press Esc on the menu to exit.\n");
    const int runResult = g2_Run();

    StopGame();
    ui::releaseAssets();
    g2_DestroyWin();

    if (runResult != 0)
    {
        std::fprintf(stderr, "glc2d game loop failed: %d\n", runResult);
        return 1;
    }

    return 0;
}
