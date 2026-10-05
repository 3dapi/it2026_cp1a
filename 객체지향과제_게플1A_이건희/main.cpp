
//#include <glc2d.h>
//#include <stdio.h>
//#include <windows.h>
//#include "CApplication.h"
//
//// link the 2d game library
//#if defined(_DEBUG)
//#if defined(_M_X64) // 64-bit ��Ű��ó
//#pragma comment(lib, "glc2d_x64_debug.lib")
//#elif defined(_M_IX86) // 32-bit ��Ű��ó
//#pragma comment(lib, "glc2d_win32_debug.lib")
//#endif
//#else
//#if defined(_M_X64)
//#pragma comment(lib, "glc2d_x64_release.lib")
//#elif defined(_M_IX86)
//#pragma comment(lib, "glc2d_win32_release.lib")
//#endif
//#endif
//
//#include "glc2d.h"
//
//int main(void)
//{
//	//SDK �ʱ�ȭ
//	g2_InitSdk();
//
//	printf("�׸� �ø���.......................\n\n");
//	
//	//������ ����
//	g2_CreateWin(100, 100, 800, 600, "My First Game Window");
//
//	//������ �ٲ۴�.
//	g2_SetClearColor(0xFF336699);
//
//	// ȭ�鿡 ����ϱ� ���ؼ� �Լ��� �����Ѵ�.
//	//g2_SetRender(Render);
//
//	// �׸��� ���α׷��� �ε�
//	//nTx = g2_TextureLoad("Texture/tst.png");
//
//
//	// ����
//	g2_Run();
//
//
//	// �ؽ�ó ����
//	//g2_TextureRelease(nTx);
//
//	// ������ ����
//	g2_DestroyWin();
//
//	return 0;
//}


#if defined(_DEBUG)
#if defined(_M_X64) // 64-bit ��Ű��ó
#pragma comment(lib, "glc2d_x64_debug.lib")
#elif defined(_M_IX86) // 32-bit ��Ű��ó
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
#include <windows.h>
#include "CApplication.h"

CApplication g_app;

int main()
{
	g_app.Init();
	g2_Run();
	g_app.Destroy();

	return 0;
}