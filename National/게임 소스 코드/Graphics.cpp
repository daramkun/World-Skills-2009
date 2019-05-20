#include "Graphics.h"
#include "Sprite.h"

CGraphics::CGraphics(HWND hWnd)
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	ZeroMemory(&m_pp, sizeof(m_pp));
	m_pp.BackBufferWidth = 800;
	m_pp.BackBufferHeight = 600;
	m_pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_pp.Windowed = false;
	m_pp.BackBufferCount = 1;
	m_pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&m_pp, &m_d3dDevice);
	D3DXCreateSprite(m_d3dDevice, &m_d3dSprite);

	m_delay = new CDelay(50);
	m_quakeValue = 0;
}

CGraphics::~CGraphics(void)
{
	SafeRelease(m_d3dSprite);
	SafeRelease(m_d3dDevice);
	SafeRelease(m_d3d);
}

void CGraphics::Clear(D3DCOLOR color, float dt)
{
	m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, color, 1.0f, NULL);
	m_d3dDevice->BeginScene();

	if(m_quakeValue != 0)
	{
		m_delay->Update(dt);
		if(m_delay->Check())
		{
			m_quakeValue /= -2;
			m_delay->Reset();
			if((m_quakeValue < 0.01f && m_quakeValue > -0.01f))
				m_quakeValue = 0;
		}
	}
}

void CGraphics::Present()
{
	m_d3dDevice->EndScene();
	m_d3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CGraphics::Draw(CSprite* spr, float x, float y)
{
	Draw(spr, x, y, (float)spr->GetWidth(), (float)spr->GetHeight());
}

void CGraphics::Draw(CSprite* spr, float x, float y, float sw, float sh)
{
	Draw(spr, x, y, sw, sh, 0.0f);
}

void CGraphics::Draw(CSprite* spr, float x, float y, float sw, float sh, float angle, D3DCOLOR color)
{
	if(spr->m_d3dTexture == NULL) return;

	m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX oldMatrix, newMatrix;
	m_d3dSprite->GetTransform(&oldMatrix);

	D3DXMatrixTransformation2D(&newMatrix, &D3DXVECTOR2(0, 0), NULL, 
		&D3DXVECTOR2(sw / spr->GetWidth(), sh / spr->GetHeight()),
		&D3DXVECTOR2(spr->GetWidth() / 2.0f, spr->GetHeight() / 2.0f), angle, &D3DXVECTOR2(x + m_quakeValue, y));
	m_d3dSprite->SetTransform(&newMatrix);

	m_d3dSprite->Draw(spr->m_d3dTexture, NULL, NULL, NULL, color);

	m_d3dSprite->SetTransform(&oldMatrix);
	m_d3dSprite->End();
}

void CGraphics::DrawNoQuake(CSprite* spr, float x, float y, float sw, float sh, D3DCOLOR color)
{
	Draw(spr, x - m_quakeValue, y, sw, sh, 0.0f, color);
}

void CGraphics::DrawClip(CSprite* spr, float x, float y, float cx, float cy, float cw, float ch)
{
	if(spr->m_d3dTexture == NULL) return;

	m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rc = {(long)cx, (long)cy, (long)cw, (long)ch};
	m_d3dSprite->Draw(spr->m_d3dTexture, &rc, NULL, &D3DXVECTOR3(x, y, 1.0f), 0xffffffff);
	m_d3dSprite->End();
}

bool CGraphics::EarthQuake()
{
	if(m_quakeValue == 0)
	{
		m_quakeValue = 200;
		return false;
	}
	else
		return true;
}

void CGraphics::WeakQuake()
{
	m_quakeValue = 10;
}