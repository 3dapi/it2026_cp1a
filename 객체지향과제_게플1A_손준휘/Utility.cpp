#include "Utility.h"
#include <Windows.h>
void SetConsole()
{
    HWND hConsole = GetConsoleWindow();
    int consoleX{ 0 };
    int consoleY{ GetSystemMetrics(SM_CYSCREEN) / 2 };
    int consoleWidth{ GetSystemMetrics(SM_CXSCREEN) / 2 };
    int consoleHeight{ GetSystemMetrics(SM_CYSCREEN) / 2 };

    MoveWindow(hConsole, consoleX, consoleY, consoleWidth, consoleHeight, TRUE);
}
