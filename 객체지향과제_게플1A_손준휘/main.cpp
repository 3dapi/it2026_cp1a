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
#include "glc2d.h"
#include <stdio.h>
//#include "Battle/Dice.h"
//#include "Battle/Character.h"
//#include "Battle/Battle.h"
#include <iostream>
#include <filesystem>
#include "Window.h"
#include "Utility.h"
#include "SceneBattle.h"

Window window{};
SceneBattle sceneBattle{};
//SoundEffectter testSound{};

int main()
{
    SetConsole();
    // 초기화
    window.Initialize();
    sceneBattle.Initialize();
    // 실행
    window.Run();
    // 폭*파
    window.Destroy();
    
    //std::cout << "window setup\n";
    //window.Setup();

    // 랜덤 설정.
    //Dice dice{};
    //dice.DiceSetup();
    //// 플레이어, 적 설정.
    //Character player{};
    //Character enemy{};
    //player.SetSetupStandard("Player", &dice, 3);
    //enemy.SetSetupStandard("Enemy", &dice, 3);

    //Battle battleMain{};
    //battleMain.Setup(&player, &enemy);
    //// image set
    //int imageDoro = window.SetImageNew(DORO);
    //int imageAtk = window.SetImageNew(ICON_ATK);
    //int imageDef = window.SetImageNew(ICON_DEF);
    //int imageAvoid = window.SetImageNew(ICON_AVOID);
    //window.SetImagePos(imageAtk, 0, window.GetHeight() - window.GetImageHeight(imageAtk));
    //window.SetImagePos(imageDef,window.GetImageX(imageAtk)+ window.GetImageWidth(imageDef),window.GetImageY(imageAtk));
    //window.SetImagePos(imageAvoid, window.GetImageX(imageDef) + window.GetImageWidth(imageAvoid), window.GetImageY(imageAtk));

    //// sound setting
    //testSound.SetIdx(SOUNDTEST);

    //std::cout << "window run\n";
    //window.Run();

    //std::cout << "window destroy\n";
    //window.Destroy();
}
