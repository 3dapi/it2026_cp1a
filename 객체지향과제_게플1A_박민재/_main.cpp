
// include the 2d game header file
#include "glc2d.h"
#include <stdio.h>
#include "CApplication.h"

CApplication g_App; // app class 전역 선언

int main()
{
	
	g_App.Init(); // 초기화

	g2_Run(); // 실행

	g_App.Destroy(); // 해제
	

	return 0;
}