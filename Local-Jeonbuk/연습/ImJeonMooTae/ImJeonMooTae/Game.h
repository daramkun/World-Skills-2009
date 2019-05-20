#pragma once

#include <Windows.h>

#include "Graphics.h"
#include "StateManage.h"
#include "Input.h"
#include "SpriteFont.h"

#include "MenuState.h"
#include "GameState.h"

class CGame
{
private:
	HWND m_hWnd;
	CGraphics m_Graphics;
	CInput m_Input;
	CStateManage m_stateManager;

	DWORD lastTick;
	DWORD frameTime;
	int frameCount;
	int fps;

	int myState;

	CMenuState m_MenuState;
	CGameState m_GameState;

	CSpriteFont m_fpsShow;

public:
	CGame(void);
	~CGame(void);

	bool Create();
	void Destroy();

	void Run();

	HWND GetHandle(){return m_hWnd;}
	CGraphics& GetG() {return m_Graphics;}
	CInput& GetI() {return m_Input;}
	CStateManage& GetS() {return m_stateManager;}
	int GetFPS(){return fps;}

	void SetState(int index){myState = index;}

	void Update(double et);
	void Draw();

private:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};
