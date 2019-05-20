#include "Img.h"

CImg::CImg(void)
{
	m_tex = NULL;
}

CImg::~CImg(void)
{
}

bool CImg::Create(const char *filename)
{
	D3DXIMAGE_INFO info; ZeroMemory(&info, sizeof(info));
	HRESULT hResult = D3DXGetImageInfoFromFile(filename, &info);
	if(FAILED(hResult))
		return false;

	width = info.Width;
	height = info.Height;

	hResult = D3DXCreateTextureFromFileEx(g_Graphics.m_d3dDevice, filename,
		info.Width, info.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(255, 0, 255), &info, NULL, &m_tex);
	if(FAILED(hResult))
		return false;

	return true;
}

bool CImg::Create(D3DCOLOR color)
{
	HRESULT hResult = D3DXCreateTexture(g_Graphics.m_d3dDevice, 640, 480, 1, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, &m_tex);
	if(FAILED(hResult))
		return false;

	width = 640;
	height = 480;

	D3DLOCKED_RECT lrect;
	RECT rect = {0, 0, 640, 480};
	m_tex->LockRect(0, &lrect, &rect, NULL);
	D3DCOLOR* clr = (D3DCOLOR*)lrect.pBits;

	for(int i = 0; i < 640 * 480; i++)
		clr[i] = color;

	m_tex->UnlockRect(0);

	return true;
}

void CImg::Destroy()
{
	if(m_tex)
		m_tex->Release();
	m_tex = NULL;
}

void CImg::Draw(int x, int y, D3DCOLOR color)
{
	g_Graphics.m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	g_Graphics.m_d3dSprite->Draw(m_tex, NULL, NULL, &D3DXVECTOR3(x, y, 1.0f), color);
	g_Graphics.m_d3dSprite->End();
}

void CImg::Draw(int x, int y, int sx, int sy, int sw, int sh, D3DCOLOR color)
{
	g_Graphics.m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	RECT srcRect = {sx, sy, sw, sh};
	g_Graphics.m_d3dSprite->Draw(m_tex, &srcRect, NULL, &D3DXVECTOR3(x, y, 1.0f), color);
	g_Graphics.m_d3dSprite->End();
}