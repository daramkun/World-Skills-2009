#pragma once

#include "Graphics.h"

class CSpriteFont
{
private:
	ID3DXFont* m_font;
	D3DXFONT_DESC fdesc;

public:
	CSpriteFont(void);
	~CSpriteFont(void);

	bool Create(CGraphics& g, const char *fontname, int size);
	void Destroy();

	void Draw(CGraphics& g, int x, int y, D3DCOLOR color, const char *text);
	void DrawShadow(CGraphics& g, int x, int y, D3DCOLOR color, const char *text);
};
