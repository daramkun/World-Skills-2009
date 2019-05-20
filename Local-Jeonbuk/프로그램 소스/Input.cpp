#include "Input.h"

CInput g_Input;

CInput::CInput(void)
{
	m_key = NULL;
}

CInput::~CInput(void)
{
	Destroy();
}

bool CInput::Create(HWND hWnd)
{
	HRESULT hResult = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&m_input, NULL);
	if(FAILED(hResult)) return false;

	hResult = m_input->CreateDevice(GUID_SysKeyboard, &m_key, NULL);
	if(FAILED(hResult)) return false;

	hResult = m_key->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hResult)) return false;

	hResult = m_key->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(hResult)) return false;

	if(FAILED(m_key->Acquire())) return false;

	return true;
}

void CInput::Destroy()
{
	if(m_key)
	{
		m_key->Unacquire();
		m_key->Release();
	}

	if(m_input)
		m_input->Release();

	m_key = NULL;
	m_input = NULL;
}

void CInput::Update()
{
	m_key->GetDeviceState(sizeof(diks), diks);
}

bool CInput::KeyDown(DWORD key)
{
	if(diks[key] & 0x80)
	{
		if(press[key])
			return false;
		else
		{
			press[key] = true;
			return true;
		}
	}
	else
	{
		press[key] = false;
		return false;
	}
}

bool CInput::KeyPress(DWORD key)
{
	if(diks[key] & 0x80)
	{
		press[key] = true;
		return true;
	}
	else
	{
		press[key] = false;
		return false;
	}
}