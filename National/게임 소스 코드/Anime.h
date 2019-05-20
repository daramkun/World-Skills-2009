#pragma once

#include <vector>
#include "Sprite.h"

using namespace std;

// �ִϸ��̼� Ŭ����
class CAnime
{
	// �׸� ���� Ŭ����
	vector<CSprite*> m_Sprites;
	int m_index;

	bool m_isPlay;
	bool m_isLoop;

	CDelay *m_delay;

public:
	// �׷��Ƚ� Ŭ����, �⺻ ���� ��, ó�� ��ȣ, ����ȣ, ������
	CAnime(CGraphics* g, wchar_t *file, int start, int end, int delay);
	~CAnime(void);

	// ���� ������� �׸�
	CSprite* Current() { return m_Sprites[m_index]; }
	
	void Play(bool loop);
	void Stop();

	bool Update(float dt);

	void Reset();
};
