#include "ImageFont.h"

CImageFont::CImageFont(CGraphics* g)
{
	m_grp = g;
	wchar_t temp[512] = {0, };
	for(int i = 0; i < 26; i++)
	{
		wsprintf(temp, L"..\\Content\\Font\\%c.png", 'A' + i);
		m_Font[i] = new CSprite(g, temp);
	}
	for(int i = 26; i < 36; i++)
	{
		wsprintf(temp, L"..\\Content\\Font\\%d.png", i - 26);
		m_Font[i] = new CSprite(g, temp);
	}
}

CImageFont::~CImageFont(void)
{
	for(int i = 0; i < 36; i++)
		delete m_Font[i];
}

void CImageFont::Draw(float x, float y, wchar_t* text)
{
	float pos = x;
	int len = (int)wcslen(text);
	for(int i = 0; i < len; i++)
	{
		int index = 0;
		if(text[i] >= 'A' && text[i] <= 'Z')
			index = text[i] - 'A';
		else if(text[i] >= '0' && text[i] <= '9')
			index = text[i] - '0' + 26;
		m_grp->Draw(m_Font[index], pos, y);
		pos += m_Font[index]->GetWidth();
	}
}

void CImageFont::Draw(float x, float y, int dat)
{
	wchar_t temp[512] = {0,};
	if(dat < 0) dat = 0;
	wsprintf(temp, L"%d", dat);
	Draw(x, y, temp);
}