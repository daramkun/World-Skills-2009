#include "Monster.h"

CMonster::CMonster()
{

}

CMonster::~CMonster()
{

}

void CMonster::Initial(CGraphics &g, MONSTERTYPE type, int x, int y)
{
	m_MonsterType = type;
	this->x = x;
	this->y = y;

	switch(type)
	{
	case MON_BIYAM:
		m_monBreath[0].Create(g, "Resource/Enermies/Snake/S01.png");
		m_monBreath[1].Create(g, "Resource/Enermies/Snake/S02.png");
		m_monBreath[2].Create(g, "Resource/Enermies/Snake/S03.png");
		m_monBreath[3].Create(g, "Resource/Enermies/Snake/S04.png");
		m_monAttack[0].Create(g, "Resource/Enermies/Snake/Attack/SA01.png");
		m_monAttack[1].Create(g, "Resource/Enermies/Snake/Attack/SA02.png");
		breathMax = 4;
		m_delay.Set(400);
		break;
	case MON_TIGER:
		m_monBreath[0].Create(g, "Resource/Enermies/Tiger/t01.png");
		m_monBreath[1].Create(g, "Resource/Enermies/Tiger/t02.png");
		m_monBreath[2].Create(g, "Resource/Enermies/Tiger/t03.png");
		m_monBreath[3].Create(g, "Resource/Enermies/Tiger/t04.png");
		breathMax = 4;
		m_delay.Set(300);
		break;
	}

	m_attackDelay.Set(1000);

	isDead = false;
}

void CMonster::Update(double et, CHero& hero, CGameMap &map)
{
	if(isDead) return;

	if(m_attackDelay.Check())
	{
		if(m_MonsterAni != MANI_ATTACK)
		{
			if(hero.x - map.m_currentX - 100 <= x + m_monBreath[0].GetWidth() &&
				x <= hero.x - map.m_currentX + 
				((hero.m_aniType == ANI_DOWNKICK) ? hero.m_HeroKick.GetWidth() : hero.m_HeroBreath[0].GetWidth()) + 100
				&& hero.GetY() <= y + m_monBreath[0].GetHeight() && y <= hero.GetY() + 250)
			{
				m_MonsterAni = MANI_ATTACK;
				m_frame = 0;
			}

			m_attackDelay.Reset();
		}
	}

	int hwidth = ((hero.m_aniType == ANI_DOWNKICK) ? hero.m_HeroKick.GetWidth() : ((hero.m_aniType == ANI_SWORD)
		? hero.m_SwordCut[0].GetWidth() : hero.m_HeroBreath[0].GetWidth()));

	if(hero.x - map.m_currentX + 10 <= x + m_monBreath[0].GetWidth() &&
		x 
		<= 
		hero.x - 
		map.m_currentX +
		hwidth - 20
		&& hero.GetY() <= y + m_monBreath[0].GetHeight() && y <= hero.GetY() + 250)
	{
		switch(m_MonsterType)
		{
		case MON_BIYAM:
			{
				if(hero.m_aniType == ANI_DOWNKICK)
				{
					hero.exp += 10;
					isDead = true;
				}
			}
			break;
		case MON_TIGER:
			{
				if(hero.m_aniType == ANI_DOWNKICK || hero.m_aniType == ANI_PUNCH
					 || hero.m_aniType == ANI_SWORD)
				{
					hero.exp += 10;
					isDead = true;
				}
			}
			break;
		}

		if(m_MonsterAni == MANI_ATTACK)
		{
			hero.hp -= 1;
		}
	}

	if(m_delay.Check())
	{
		m_frame++;
		if(m_MonsterAni == MANI_ATTACK)
		{
			if(m_frame >= 2)
			{
				m_frame = 0;
				m_MonsterAni = MANI_BREATH;
			}
		}
		else
		{
			if(m_frame >= breathMax)
			{
				m_frame = 0;
			}
		}

		x -= 1 * et;

		m_delay.Reset();
	}
}

void CMonster::Draw(CGraphics &g, CGameMap &map)
{
	if(isDead) return;
	switch(m_MonsterAni)
	{
	case MANI_BREATH:
		m_monBreath[m_frame].Draw(g, x + map.m_currentX, y);
		break;
	case MANI_ATTACK:
		m_monAttack[m_frame].Draw(g, x + map.m_currentX, y - 70);
		break;
	}
}

void CMonster::Destroy()
{

}