// include the 2d game header file
#include "glc2d.h"
#include <cstring>
#include "CApplication.h"

CApplication g_app;

int main()
{
    // Resources are copied beside the executable when building.
    char executable[MAX_PATH]{};
    GetModuleFileNameA(nullptr, executable, MAX_PATH);
    char* slash = strrchr(executable, '\\');
    if (slash)
    {
        *slash = '\0';
        SetCurrentDirectoryA(executable);
    }
	g_app.Init();	

	g2_Run();

	g_app.Destroy();

	return 0;
}
