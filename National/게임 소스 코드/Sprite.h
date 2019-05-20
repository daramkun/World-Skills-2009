#pragma once

#include "Graphics.h"

class CSprite
{
	friend class CGraphics;
private:
	IDirect3DTexture9 *m_d3dTexture;
	D3DXIMAGE_INFO m_info;

public:
	CSprite(CGraphics *g, wchar_t *filename);
	~CSprite(void);

	int GetWidth() { return m_info.Width; }
	int GetHeight() { return m_info.Height; }
};
