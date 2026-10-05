#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include "glc2d.h"
#include "CApplication.h"

CApplication g_app;

int main()
{
    g_app.Init();
    g2_Run();
    g_app.Destroy();
}