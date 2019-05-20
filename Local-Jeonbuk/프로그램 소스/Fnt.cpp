#include "Fnt.h"

CFnt::CFnt(void)
{
	m_font = NULL;
}

CFnt::~CFnt(void)
{
	Destroy();
}

bool CFnt::Create(char *fontname, int size)
{
	D3DXFONT_DESC desc; ZeroMemory(&desc, sizeof(desc));
	desc.CharSet = DEFAULT_CHARSET;
	strcpy(desc.FaceName, fontname);
	desc.Width = (int)(size / 1.4);
	desc.Height = (int)(size * 1.4);
	HRESULT hResult = D3DXCreateFontIndirect(g_Graphics.m_d3dDevice, &desc, &m_font);

	if(FAILED(hResult))
		return false;

	return true;
}

void CFnt::Destroy()
{
	if(m_font)
		m_font->Release();
	m_font = NULL;
}

void CFnt::Draw(char *text, int x, int y, D3DCOLOR color)
{
	g_Graphics.m_d3dSprite->Begin(D3DXSPRITE_ALPHABLEND);
	RECT show = {x, y, 640, 480};
	m_font->DrawText(g_Graphics.m_d3dSprite, text, strlen(text), &show, DT_NOCLIP, color);
	g_Graphics.m_d3dSprite->End();
}

void CFnt::DrawShadow(char *text, int x, int y, D3DCOLOR color)
{
	Draw(text, x - 1, y - 1, D3DCOLOR_XRGB(0, 0, 0));
	Draw(text, x + 1, y - 1, D3DCOLOR_XRGB(0, 0, 0));
	Draw(text, x - 1, y + 1, D3DCOLOR_XRGB(0, 0, 0));
	Draw(text, x + 1, y + 1, D3DCOLOR_XRGB(0, 0, 0));
	Draw(text, x, y, color);
}