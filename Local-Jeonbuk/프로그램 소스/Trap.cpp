#include "Trap.h"
#include "Lib.h"

CTrap::CTrap(void)
{
}

CTrap::~CTrap(void)
{
}

void CTrap::Initial(TrapType type, int x)
{
	tType = type;
	switch(type)
	{
	case TT_Thorn:
		m_img.Create("Content/Trap/1.png");
		m_broken.Create("Content/Trap/2.png");
		break;
	case TT_Pool:
		m_img.Create("Content/Trap/3.png");
		m_broken.Create("Content/Trap/4.png");
		break;
	}
	this->x = x;
	isBroken = false;
	isEnd = false;
}

void CTrap::Update(CHero& hero, int cx)
{
	if(isBroken) return;
	if(!CLib::Crash(x + cx, 400, m_img.GetWidth(), m_img.GetHeight(),
		0, 0, 640, 480)) return;

	if(hero.currentAni != HA_HIT)
	{
		if(CLib::Crash(x, 450, 75, 25, hero.x - cx + 20, hero.y, 130 - 40, hero.GetHeight()))
		{
			if(tType == TT_Thorn)
			{
				hero.hp -= 5;
				hero.x -= 50;
			}
			else if(tType == TT_Pool)
			{
				hero.hp -= 15;
			}
			hero.currentAni = HA_HIT;
			isBroken = true;
		}
	}
}

void CTrap::Draw(int cx)
{
	if(!isBroken)
		m_img.Draw(x + cx, 400);
	else
		m_broken.Draw(x + cx, 400);
}

void CTrap::Destroy()
{
	m_img.Destroy();
}
