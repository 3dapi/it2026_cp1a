// link the 2d game library
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

#include "packages/glc2d.0.1.0.7/build/native/include/glc2d.h"
#include "CApplication.h"

extern CApplication g_app;

int main()
{
    g_app.Init();
    g2_Run();
    g_app.Destroy();

    return 0;
}