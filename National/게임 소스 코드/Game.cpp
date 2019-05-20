#include "Game.h"
#include "State.h"

#include "resource.h"

bool g_keyDowned[256];
bool g_keyPressed[256];

CGame::CGame(void)
{
	m_hInstance = GetModuleHandle(NULL);
	WNDCLASS wndClass; ZeroMemory(&wndClass, sizeof(wndClass));
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_MAIN));
	wndClass.hInstance = m_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = WINDOW_CLASS_NAME;
	RegisterClass(&wndClass);

	// 창 크기 및 위치를 800 * 600에 가운데로 지정한다
	// 개발을 위한 것으로, 본 게임에서는 전체화면을 사용하므로 크게 상관 없음
	RECT wndSize = {0, 0, 800, 600}; AdjustWindowRect(&wndSize, WINDOW_STYLE, FALSE);
	int w = wndSize.right - wndSize.left, h = wndSize.bottom - wndSize.top;
	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2, y = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2;

	m_hWnd = CreateWindowEx(NULL, WINDOW_CLASS_NAME, L"Nano Doctor", WINDOW_STYLE, x, y, w, h,
		NULL, NULL, m_hInstance, NULL);

	// 그래픽스 관리자 생성
	m_grp = new CGraphics(m_hWnd);

	m_stateIndex = -1;
}

CGame::~CGame(void)
{
	delete m_grp;
	DestroyWindow(m_hWnd);
	UnregisterClass(WINDOW_CLASS_NAME, m_hInstance);
}

void CGame::Run()
{
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	DWORD lastTickCount = timeGetTime();
	float dt = 0;

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
			// 일랩시드 시간을 잰다
			dt = (timeGetTime() - lastTickCount) / 100.0f;
			lastTickCount = timeGetTime();
			if(m_stateIndex != -1)
				// 상태데이터 업데이트
				m_State[m_stateIndex]->Update(dt);
			m_grp->Clear(0xffffffff, dt);
			if(m_stateIndex != -1)
				// 상태데이터 렌더링
				m_State[m_stateIndex]->Draw(dt);
			m_grp->Present();
			Sleep(1);
		}
	}
}

void CGame::AddState(CState *state, int index)
{
	m_State[index] = state;
}

void CGame::SetState(int index)
{
	// 상태를 변경한다
	if(m_stateIndex != -1)
		m_State[m_stateIndex]->Destroy();
	m_stateIndex = index;
	m_State[m_stateIndex]->Initial();
}

bool CGame::KeyPress(int key)
{
	return g_keyPressed[key];
}

LRESULT CALLBACK CGame::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_KEYDOWN:
		// 해당 키가 눌렸다
		g_keyPressed[wParam] = true;
		break;
	case WM_KEYUP:
		// 해당 키가 떼어졌다
		g_keyPressed[wParam] = false;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}