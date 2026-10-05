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
#include "CApplication.h"

//init = 실행전 준비 render = 불러오기 update = 갱신 destroy = 할당 해제
//생성(Create) - 소멸(Destroy) - 초기화(Init) - 갱신(Update) - 랜더링(Render) 순서로
//2d game = Texture, font, Audio, Input
CApplication g_app;

int main()
{
	g_app.Init();
	// 실행
	g2_Run();
	g_app.Destroy();

	return 0;
}
/* 
	//이미지 인덱스 
int nTx;
nTx = g2_TextureLoad("Texture/tst.png"); 
g2_Draw2D(nTx, NULL, &g_vcPos); 
	//폰트 인덱스 
int nFont; 
nFont = g2_FontCreate("굴림", 20, false); 
RECT rc{0, 10, 500, 40}; g2_FontDrawText(nFonts, {}
	//마우스 위치 읽기 
auto mouseX = g2_GetMouseX(); 
auto mouseY = g2_GetMouseX(); 
auto mouseZ = g2_GetMouseX(); 
auto pKeyboard = g2_GetKeyboard();
*/