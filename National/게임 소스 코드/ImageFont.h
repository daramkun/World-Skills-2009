#pragma once

#include "Sprite.h"

class CImageFont
{
private:
	CGraphics *m_grp;
	CSprite* m_Font[36];

public:
	CImageFont(CGraphics* g);
	~CImageFont(void);

	void Draw(float x, float y, wchar_t* text);
	void Draw(float x, float y, int dat);
};
