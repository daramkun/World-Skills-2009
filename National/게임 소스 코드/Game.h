#pragma once

#include <Windows.h>

#include "Graphics.h"

#pragma comment (lib, "winmm.lib")

#define WINDOW_CLASS_NAME L"NanoDoctorGame"
#define WINDOW_STYLE (WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU)

class CState;

enum STATES
{
	STATE_LOGO = 0,
	STATE_MENU = 1,
	STATE_GAME,
	STATE_RESULT,
};

class CGame
{
private:
	HWND m_hWnd;
	HINSTANCE m_hInstance;

	CGraphics *m_grp;

	CState *m_State[4];
	int m_stateIndex;

public:
	CGame(void);
	~CGame(void);

	void Run();

	CGraphics* Graphics() { return m_grp; }

	void AddState(CState *state, int index);
	void SetState(int index);

	bool KeyPress(int key);

	CState* GetStates(int index) { return m_State[index]; }

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};
