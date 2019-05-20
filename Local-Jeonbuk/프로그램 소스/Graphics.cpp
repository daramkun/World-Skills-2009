#include "Graphics.h"

CGraphics g_Graphics;

CGraphics::CGraphics(void)
{
}

CGraphics::~CGraphics(void)
{
	Destroy();
}

bool CGraphics::Create(HWND hWnd)
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS pp; ZeroMemory(&pp, sizeof(pp));
	pp.BackBufferCount = 1;
	pp.BackBufferHeight = 480;
	pp.BackBufferWidth = 640;
	pp.hDeviceWindow = hWnd;
	pp.EnableAutoDepthStencil = false;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = false;

	HRESULT hResult = m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &pp, &m_d3dDevice);

	if(FAILED(hResult))
	{
		hResult = m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &m_d3dDevice);
		if(FAILED(hResult))
			return false;
	}

	hResult = D3DXCreateSprite(m_d3dDevice, &m_d3dSprite);
	if(FAILED(hResult))
		return false;

	return true;
}

void CGraphics::Destroy()
{
	if(m_d3dSprite)
		m_d3dSprite->Release();
	if(m_d3dDevice)
		m_d3dDevice->Release();
	if(m_d3d)
		m_d3d->Release();

	m_d3dSprite = NULL;
	m_d3dDevice = NULL;
	m_d3d = NULL;
}

void CGraphics::Clear(D3DCOLOR color)
{
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, NULL);
}

void CGraphics::Begin()
{
	m_d3dDevice->BeginScene();
}

void CGraphics::End()
{
	m_d3dDevice->EndScene();
}

void CGraphics::Rendering()
{
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}