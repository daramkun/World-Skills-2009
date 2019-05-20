#include "Input.h"

CInput::CInput(void)
{
}

CInput::~CInput(void)
{
	Destroy();
}

bool CInput::Create(HWND hWnd)
{
	HRESULT result = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_input, NULL);
	if(FAILED(result))
		return false;

	result = m_input->CreateDevice(GUID_SysKeyboard, &m_inDevice, NULL);
	if(FAILED(result))
		return false;

	result = m_inDevice->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if(FAILED(result))
		return false;

	result = m_inDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result))
		return false;

	m_inDevice->Acquire();

	return true;
}

void CInput::Destroy()
{
	if(m_inDevice != NULL)
	{
		m_inDevice->Unacquire();
		m_inDevice->Release();
		m_inDevice = NULL;
	}

	if(m_input != NULL)
	{
		m_input->Release();
		m_input = NULL;
	}
}

void CInput::Update()
{
	if(m_inDevice != NULL)
		m_inDevice->GetDeviceState(sizeof(m_dik), &m_dik);
}

bool CInput::KeyDown(DWORD key)
{
	if(m_dik[key] & 0x80)
	{
		if(!m_pressed[key])
		{
			m_pressed[key] = true;
			return true;
		}
		else
			return false;
	}
	else
	{
		m_pressed[key] = false;
		return false;
	}
}

bool CInput::KeyPress(DWORD key)
{
	if(m_dik[key] & 0x80)
	{
		m_pressed[key] = true;
		return true;
	}
	else
	{
		m_pressed[key] = false;
		return false;
	}
}

bool CInput::KeyUp(DWORD key)
{
	if(!(m_dik[key] & 0x80))
	{
		if(m_pressed[key])
		{
			m_pressed[key] = false;
			return true;
		}
		else
			return false;
	}
	else
	{
		m_pressed[key] = true;
		return false;
	}
}