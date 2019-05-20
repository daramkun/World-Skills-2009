#pragma once

#include <dinput.h>

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

class CInput
{
private:
	IDirectInput8 *m_input;
	IDirectInputDevice8 *m_key;

	BYTE diks[256];
	bool press[256];

public:
	CInput(void);
	~CInput(void);

	bool Create(HWND hWnd);
	void Destroy();

	void Update();

	bool KeyDown(DWORD key);
	bool KeyPress(DWORD key);
};

extern CInput g_Input;