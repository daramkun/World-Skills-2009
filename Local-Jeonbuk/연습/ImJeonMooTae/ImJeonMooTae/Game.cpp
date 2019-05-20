#include "Game.h"
#include "resource.h"

CGame::CGame(void)
{
}

CGame::~CGame(void)
{
}

bool CGame::Create()
{
	myState = -1;

	WNDCLASS wndClass = {NULL, WndProc, NULL, NULL, GetModuleHandle(NULL), 
		LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_WINDOW)),
		LoadCursor(NULL, IDC_ARROW), (HBRUSH)GetStockObject(WHITE_BRUSH), NULL, "IJMT"};
	RegisterClass(&wndClass);

	RECT adjust = {NULL, NULL, 640, 480};
	AdjustWindowRect(&adjust, WS_OVERLAPPEDWINDOW, FALSE);

	int X = GetSystemMetrics(SM_CXSCREEN) / 2, Y = GetSystemMetrics(SM_CYSCREEN) / 2;
	int Width = (adjust.right - adjust.left), Height = (adjust.bottom - adjust.top);
	X -= Width /  2; Y -= Height / 2;

	m_hWnd = CreateWindowEx(NULL, "IJMT", "ÀÓÀü¹«Åð", WS_OVERLAPPEDWINDOW, X, Y, Width, Height, NULL, NULL, GetModuleHandle(NULL), NULL);

	if(m_hWnd == NULL)
		return FALSE;

	if(!m_Graphics.Create(m_hWnd))
		return false;

	if(!m_Input.Create(m_hWnd))
		return false;

	if(!m_fpsShow.Create(m_Graphics, "MS Gothic", 14))
		return false;

	m_stateManager.Create(m_Graphics);
	m_stateManager.SetStateClass(1, &m_MenuState);
	m_stateManager.SetStateClass(2, &m_GameState);
	myState = 1;

	return TRUE;
}

void CGame::Destroy()
{
	m_Input.Destroy();
	m_Graphics.Destroy();

	DestroyWindow(m_hWnd);
	UnregisterClass("IJMT", GetModuleHandle(NULL));
}

void CGame::Run()
{
	ShowCursor(FALSE);

	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	MSG msg; ZeroMemory(&msg, sizeof(msg));
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
			DWORD frame = GetTickCount();
			double dt = (frame - lastTick);
			frameTime += dt;

			if(frameTime >= 1000)
			{
				fps = frameCount;
				frameCount = NULL;
				frameTime = NULL;
			}

			frameCount++;

			m_Input.Update();
			Update(dt / 10.0f);
			Draw();

			lastTick = frame;

			Sleep(1);
		}
	}

	ShowCursor(TRUE);
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

void CGame::Update(double et)
{
	m_stateManager.SetState(myState, et);
	m_stateManager.Update(et);
}

void CGame::Draw()
{
	m_Graphics.Clear(D3DCOLOR_XRGB(0, 0, 0));
	m_Graphics.Begin();
	m_stateManager.Draw(m_Graphics);
	char fps[120] = {0,};
	wsprintf(fps, "FPS : %d", this->fps);
	m_fpsShow.DrawShadow(m_Graphics, 10, 10, D3DCOLOR_XRGB(255, 255, 255), fps);
	m_Graphics.End();
	m_Graphics.Present();
}