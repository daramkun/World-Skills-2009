#pragma once

#include "Graphics.h"

class CFnt
{
private:
	ID3DXFont *m_font;

public:
	CFnt(void);
	~CFnt(void);

	bool Create(char *fontname, int size);
	void Destroy();

	void Draw(char *text, int x, int y, D3DCOLOR color = 0xffffffff);
	void DrawShadow(char *text, int x, int y, D3DCOLOR color = 0xffffffff);
};
