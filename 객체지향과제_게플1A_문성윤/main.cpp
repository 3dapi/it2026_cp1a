// link the 2d game library
#if defined(_DEBUG)
#if defined(_M_X64) // 64-bit 아키텍처
#pragma comment(lib, "glc2d_x64_debug.lib")
#elif defined(_M_IX86) // 32-bit 아키텍처
#pragma comment(lib, "glc2d_win32_debug.lib")
#endif
#else
#if defined(_M_X64)
#pragma comment(lib, "glc2d_x64_release.lib")
#elif defined(_M_IX86)
#pragma comment(lib, "glc2d_win32_release.lib")
#endif
#endif

// include the 2d game header file
#include "CApplication.h"
#include <filesystem>
#include <glc2d.h>

CApplication g_app;

int main()
{
    wchar_t executable[32768]{};
    GetModuleFileNameW(nullptr, executable, 32768);
    std::filesystem::current_path(std::filesystem::path(executable).parent_path());
    if (g_app.Init() < 0)
    {
        g_app.Destroy();
        return 1;
    }
    g2_Run();
    g_app.Destroy();

    return 0;
}
