#include "IScene.h"

void IScene::SetWindow(bool setWinPos)
{
	HWND hwnd = GetActiveWindow();

	if (hwnd != nullptr)
	{
		int x = _winPos.x; int y = _winPos.y;

		if (!setWinPos)
		{
			RECT rect;
			GetWindowRect(hwnd, &rect);
			x = rect.left;
			y = rect.top;
		}

		SetWindowLong
		(
			hwnd,
			GWL_STYLE,
			WS_OVERLAPPEDWINDOW
		);

		SetWindowPos
		(
			hwnd,
			nullptr,
			x,
			y,
			_winSize.cx,
			_winSize.cy,
			SWP_FRAMECHANGED | SWP_SHOWWINDOW
		);
	}

	g2_SetWindowTitle(_winName.c_str());
	g2_SetClearColor(_winColor);

	return;
}

void IScene::SetWindowColor(unsigned int col)
{
	_winColor = col;
	g2_SetClearColor(_winColor);
}

void IScene::SetFullScreen()
{
	HWND hwnd = GetActiveWindow();

	if (hwnd == nullptr)
		return;

	// 현재 모니터
	HMONITOR hMonitor = MonitorFromWindow
	(
		hwnd,
		MONITOR_DEFAULTTONEAREST
	);

	MONITORINFO mi = {};
	mi.cbSize = sizeof(MONITORINFO);

	GetMonitorInfo(hMonitor, &mi);

	// 창 테두리 제거
	SetWindowLong
	(
		hwnd,
		GWL_STYLE,
		WS_POPUP
	);

	SetWindowPos
	(
		hwnd,
		HWND_TOP,
		mi.rcMonitor.left,
		mi.rcMonitor.top,
		mi.rcMonitor.right - mi.rcMonitor.left,
		mi.rcMonitor.bottom - mi.rcMonitor.top,
		SWP_FRAMECHANGED | SWP_SHOWWINDOW
	);

	g2_SetWindowTitle(_winName.c_str());
	g2_SetClearColor(_winColor);
}



bool IScene::CheckAndProcess(E_SceneType curType)
{
	if (_sceneType != curType)
	{
		std::cout << "현재 씬 != this 씬 -> Destroy" << std::endl;
		Destroy();
		return false;
	}
	return true;
}

void IScene::Init()
{
	SetWindow();

	return;
}

void IScene::InitSDK()
{
	return;
}

//Life-Cycle
void IScene::Update()
{
	return ;
}
void IScene::Render()
{
	return ;
}

void IScene::Destroy()
{
	return ;
}