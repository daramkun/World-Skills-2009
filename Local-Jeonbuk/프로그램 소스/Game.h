#pragma once

#include <windows.h>

#include "MenuState.h"
#include "GameState.h"

class CGame
{
private:
	HWND m_hWnd;
	int myIndex;

	CMenuState m_MenuState;
	CGameState m_GameState;

public:
	CGame(void);
	~CGame(void);

	bool Create();
	void Destroy();

	void Run();

	void SetIndex(int index){ myIndex = index; }

	HWND GetHandle() { return m_hWnd; }
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};

extern CGame g_Game;