#include "Sprite.h"

CSprite::CSprite(CGraphics *g, wchar_t *filename)
{
	D3DXGetImageInfoFromFile(filename, &m_info);
	HRESULT h = D3DXCreateTextureFromFileEx(g->m_d3dDevice, filename, m_info.Width, m_info.Height,
		1, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, -1, -1, 0xffff00ff, &m_info, NULL, &m_d3dTexture);
	if(FAILED(h))
		m_d3dTexture = NULL;
}

CSprite::~CSprite(void)
{
	SafeRelease(m_d3dTexture);
}
