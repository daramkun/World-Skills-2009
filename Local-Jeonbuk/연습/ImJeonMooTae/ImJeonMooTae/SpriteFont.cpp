#include "SpriteFont.h"
#include <cstring>

CSpriteFont::CSpriteFont(void)
{
	m_font = NULL;
}

CSpriteFont::~CSpriteFont(void)
{
	Destroy();
}

bool CSpriteFont::Create(CGraphics& g, const char *fontname, int size)
{
	ZeroMemory(&fdesc, sizeof(fdesc));
	fdesc.Width = (int)(size * 0.75f);
	fdesc.Height = (int)(size * 1.5f);
	fdesc.CharSet = DEFAULT_CHARSET;
	strcpy(fdesc.FaceName, fontname);

	if(FAILED(D3DXCreateFontIndirect(g.m_d3dDevice, &fdesc, &m_font)))
		return false;

	return true;
}

void CSpriteFont::Destroy()
{
	if(m_font != NULL)
	{
		m_font->Release();
		m_font = NULL;
	}
}

void CSpriteFont::Draw(CGraphics& g, int x, int y, D3DCOLOR color, const char *text)
{
	g.m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	RECT rect = {x, y, fdesc.Width * strlen(text), fdesc.Height};
	m_font->DrawText(g.m_d3dSprite, text, (int)strlen(text), &rect, DT_NOCLIP, color);
	g.m_d3dSprite->End();
}

void CSpriteFont::DrawShadow(CGraphics& g, int x, int y, D3DCOLOR color, const char *text)
{
	Draw(g, x - 1, y - 1, D3DCOLOR_XRGB(0, 0, 0), text);
	Draw(g, x + 1, y - 1, D3DCOLOR_XRGB(0, 0, 0), text);
	Draw(g, x - 1, y + 1, D3DCOLOR_XRGB(0, 0, 0), text);
	Draw(g, x + 1, y + 1, D3DCOLOR_XRGB(0, 0, 0), text);
	Draw(g, x, y, color, text);
}