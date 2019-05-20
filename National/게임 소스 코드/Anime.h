#pragma once

#include <vector>
#include "Sprite.h"

using namespace std;

// 애니메이션 클래스
class CAnime
{
	// 그림 관리 클래스
	vector<CSprite*> m_Sprites;
	int m_index;

	bool m_isPlay;
	bool m_isLoop;

	CDelay *m_delay;

public:
	// 그래픽스 클래스, 기본 파일 명, 처음 번호, 끝번호, 딜레이
	CAnime(CGraphics* g, wchar_t *file, int start, int end, int delay);
	~CAnime(void);

	// 현재 재생중인 그림
	CSprite* Current() { return m_Sprites[m_index]; }
	
	void Play(bool loop);
	void Stop();

	bool Update(float dt);

	void Reset();
};
