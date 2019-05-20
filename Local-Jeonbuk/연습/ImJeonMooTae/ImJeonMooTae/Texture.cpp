#include "Texture.h"

CTexture::CTexture(void)
{
	m_texture = NULL;
}

CTexture::~CTexture(void)
{
	Destroy();
}

bool CTexture::Create(CGraphics& graphics, const char *file)
{
	D3DXIMAGE_INFO info; ZeroMemory(&info, sizeof(info));
	D3DXGetImageInfoFromFile(file, &info);

	w = info.Width;
	h = info.Height;

	HRESULT result = D3DXCreateTextureFromFileEx(graphics.m_d3dDevice, file, info.Width, info.Height, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED,
		D3DX_DEFAULT, D3DX_DEFAULT, D3DCOLOR_XRGB(255, 0, 255), &info, NULL, &m_texture);

	if(FAILED(result))
		return false;

	return true;
}

bool CTexture::Create(CGraphics& graphics, D3DCOLOR color)
{
	HRESULT result = D3DXCreateTexture(graphics.m_d3dDevice, 4, 4, 1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &m_texture);
	if(FAILED(result))
		return false;
	D3DLOCKED_RECT lrect; ZeroMemory(&lrect, sizeof(lrect));
	RECT rect = {0 ,0, 4, 4};
	m_texture->LockRect(0, &lrect, &rect, D3DLOCK_DISCARD);
	D3DCOLOR* temp = (D3DCOLOR*)lrect.pBits;
	for(int i = 0; i < 4 * 4; i++)
	{
		temp[i] = color;
	}
	w = 4;
	h = 4;

	return true;
}

void CTexture::Destroy()
{
	if(m_texture != NULL)
	{
		m_texture->Release();
		m_texture = NULL;
	}
}

void CTexture::Draw(CGraphics& g, int x, int y, D3DCOLOR color)
{
	D3DXVECTOR3 position((float)x, (float)y, 1.0f);
	g.m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	g.m_d3dSprite->Draw(m_texture, NULL, NULL, &position, color);
	g.m_d3dSprite->End();
}

void CTexture::Draw(CGraphics& g, int x, int y, int w, int h, D3DCOLOR color)
{
	D3DXVECTOR2 xy((float)x, (float)y);
	D3DXVECTOR2 scale((float)w, (float)h);
	D3DXMATRIX oldMatrix, newMatrix;
	D3DXMatrixTransformation2D(&newMatrix, NULL, NULL, &scale, NULL, NULL, &xy);

	g.m_d3dSprite->GetTransform(&oldMatrix);
	g.m_d3dSprite->SetTransform(&newMatrix);

	g.m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	g.m_d3dSprite->Draw(m_texture, NULL, NULL, &D3DXVECTOR3(xy.x, xy.y, 1.0f), color);
	g.m_d3dSprite->End();

	g.m_d3dSprite->SetTransform(&oldMatrix);
}

void CTexture::Draw(CGraphics& g, int x, int y, int cx, int cy, int w, int h, D3DCOLOR color)
{
	D3DXVECTOR3 position((float)x, (float)y, 1.0f);
	RECT clip = {cx, cy, w, h};
	D3DXVECTOR3 center(0, 0, 0);
	g.m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	g.m_d3dSprite->Draw(m_texture, &clip, &center, &position, color);
	g.m_d3dSprite->End();
}