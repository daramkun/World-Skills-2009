#include "Graphics.h"

CGraphics::CGraphics(void)
{
	m_d3d = NULL;
	m_d3dDevice = NULL;
	m_d3dSprite = NULL;
}

CGraphics::~CGraphics(void)
{
	Destroy();
}

bool CGraphics::Create(HWND hWnd)
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(m_d3d == NULL) return false;

	D3DPRESENT_PARAMETERS pp; ZeroMemory(&pp, sizeof(pp));
	pp.BackBufferWidth = 640;
	pp.BackBufferHeight = 480;
	pp.hDeviceWindow = hWnd;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = true;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	pp.EnableAutoDepthStencil = false;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;

	HRESULT result = m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&pp, &m_d3dDevice);

	if(FAILED(result))
	{
		result = m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&pp, &m_d3dDevice);

		if(FAILED(result))
		{
			result = m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&pp, &m_d3dDevice);

			if(FAILED(result))
				return false;
		}
	}

	result = D3DXCreateSprite(m_d3dDevice, &m_d3dSprite);
	if(FAILED(result))
		return false;

	m_d3dDevice->ShowCursor(true);

	return true;
}

void CGraphics::Destroy()
{
	if(m_d3dSprite != NULL)
	{
		m_d3dSprite->Release();
		m_d3dSprite = NULL;
	}

	if(m_d3dDevice != NULL)
	{
		m_d3dDevice->Release();
		m_d3dDevice = NULL;
	}

	if(m_d3d != NULL)
	{
		m_d3d->Release();
		m_d3d = NULL;
	}
}

void CGraphics::Clear(D3DCOLOR color)
{
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, NULL);
}

void CGraphics::Present()
{
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CGraphics::Begin()
{
	m_d3dDevice->BeginScene();
}

void CGraphics::End()
{
	m_d3dDevice->EndScene();
}