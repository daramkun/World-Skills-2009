#include "Anime.h"

CAnime::CAnime(CGraphics* g, wchar_t *file, int start, int end, int delay)
{
	wchar_t temp[512] = {0,};
	for(int i = start; i <= end; i++)
	{
		ZeroMemory(temp, sizeof(temp));
		wsprintf(temp, L"%s%d.png", file, i);
		m_Sprites.push_back(new CSprite(g, temp));
	}

	m_index = 0;

	m_delay = new CDelay(delay);

	m_isPlay = true;
	m_isLoop = true;
}

CAnime::~CAnime(void)
{
	delete m_delay;

	while(m_Sprites.size() != 0)
	{
		delete m_Sprites.back();
		m_Sprites.pop_back();
	}
}

void CAnime::Play(bool loop)
{
	if(m_isPlay) return;
	m_isPlay = true;
	m_isLoop = loop;
	m_index = 0;
}

void CAnime::Stop()
{
	m_isPlay = m_isLoop = false;
}

bool CAnime::Update(float dt)
{
	if(!m_isPlay) return false;

	m_delay->Update(dt);
	if(m_delay->Check())
	{
		m_index++;
		if(m_index >= (int)m_Sprites.size())
		{
			if(m_isLoop)
				m_index = 0;
			else
			{
				m_index = m_Sprites.size() - 1;
				m_delay->Reset();
				return true;
			}
		}
		m_delay->Reset();
	}

	return false;
}

void CAnime::Reset()
{
	m_index = 0;
}