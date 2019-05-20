#pragma once

#include "Graphics.h"

class CImg
{
private:
	IDirect3DTexture9 *m_tex;
	int width, height;

public:
	CImg(void);
	~CImg(void);

	bool Create(const char *filename);
	bool Create(D3DCOLOR color);
	void Destroy();

	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void Draw(int x, int y, D3DCOLOR color = 0xffffffff);
	void Draw(int x, int y, int sx, int sy, int sw, int sh, D3DCOLOR color = 0xffffffff);
};
