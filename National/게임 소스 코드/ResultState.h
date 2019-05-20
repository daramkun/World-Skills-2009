#pragma once

#include "ImageFont.h"
#include "State.h"
#include "Delay.h"

#include "Inc.h"

#include "Sound.h"

class CResultState
	: public CState
{
private:
	CSprite *m_back;
	CImageFont *m_font;
	CSprite *m_edited;

	Ranking rank[3];

	int m_whensave;
	bool m_inputRanking;

	char m_initial[3];
	int m_input;

	CDelay *m_inputDelay;

	CSound *m_result;

public:
	CResultState(CGame *game);
	~CResultState(void);

	void Initial();
	void Update(float dt);
	void Draw(float dt);
	void Destroy();
};
