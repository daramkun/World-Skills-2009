#include "Game.h"
#include "Graphics.h"
#include "StateManager.h"
#include "Input.h"

#include "resource.h"

#define WNDNAME "WorldSkills"

CGame g_Game;

CGame::CGame(void)
{
	myIndex = -1;
}

CGame::~CGame(void)
{
}

bool CGame::Create()
{
	WNDCLASS wndClass = {NULL, WndProc, NULL, NULL, GetModuleHandle(NULL), 
			LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_MYICON)),
			LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH), NULL, WNDNAME};
	RegisterClass(&wndClass);

	int x = GetSystemMetrics(SM_CXSCREEN) / 2, y = GetSystemMetrics(SM_CYSCREEN) / 2;
	RECT wndSize = {0, 0, 640, 480};
	AdjustWindowRect(&wndSize, WS_OVERLAPPEDWINDOW, FALSE);
	int w = wndSize.right - wndSize.left, h = wndSize.bottom - wndSize.top;
	x -= w / 2; y -= h / 2;

	m_hWnd = CreateWindow(WNDNAME, "ÀÓÀü¹«Åð", WS_OVERLAPPEDWINDOW, x, y, w, h, NULL, NULL, 
		GetModuleHandle(NULL), NULL);

	if(!m_hWnd) return false;

	if(!g_Graphics.Create(m_hWnd)) return false;
	if(!g_Input.Create(m_hWnd)) return false;

	if(!g_stateManager.Create()) return false;

	g_stateManager.SetIndex(1, &m_MenuState);
	g_stateManager.SetIndex(2, &m_GameState);
	myIndex = 1;

	return true;
}

void CGame::Destroy()
{
	g_stateManager.Destroy();
	g_Input.Destroy();
	g_Graphics.Destroy();
	DestroyWindow(m_hWnd);
	UnregisterClass(WNDNAME, GetModuleHandle(NULL));
}

void CGame::Run()
{
	ShowCursor(false);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	DWORD LastTick = GetTickCount(), dt = 0;

	MSG msg;
	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if(!GetMessage(&msg, NULL, 0, 0))
				break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			DWORD now = GetTickCount();
			
			dt = now - LastTick;

			g_stateManager.SetState(myIndex, dt / 10.0f);
			g_stateManager.Update(dt / 10.0f);
			g_stateManager.Draw();

			LastTick = now;

			Sleep(1);
		}
	}

	ShowCursor(true);
}

LRESULT CALLBACK CGame::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}