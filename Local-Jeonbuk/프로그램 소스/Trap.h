#pragma once

#include "Img.h"
#include "Delay.h"

#include "Hero.h"

enum TrapType
{
	TT_Thorn = 0,
	TT_Pool,
};

//////////////////////////////////////////////////////////////////////////
// วิมค
//////////////////////////////////////////////////////////////////////////
class CTrap
{
private:
	CImg m_img;
	CImg m_broken;
	int x;

	bool isBroken;
	bool isEnd;

	CDelay delay;

	TrapType tType;

public:
	CTrap(void);
	~CTrap(void);

	void Initial(TrapType type, int x);
	void Update(CHero& hero, int cx);
	void Draw(int cx);
	void Destroy();
};
