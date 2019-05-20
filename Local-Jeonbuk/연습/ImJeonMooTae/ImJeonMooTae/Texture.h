#pragma once

#include "Graphics.h"

class CTexture
{
private:
	IDirect3DTexture9 *m_texture;
	int w, h;

public:
	CTexture(void);
	~CTexture(void);

	bool Create(CGraphics& graphics, const char *file);
	bool Create(CGraphics& graphics, D3DCOLOR color);
	void Destroy();

	int GetWidth() { return w; }
	int GetHeight() { return h; }

	void Draw(CGraphics& g, int x, int y, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(CGraphics& g, int x, int y, int w, int h, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(CGraphics& g, int x, int y, int cx, int cy, int w, int h, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));
};
