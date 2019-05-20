#pragma once

#include "Hero.h"
#include "GameMap.h"
#include "Texture.h"
#include "Delay.h"

enum MONSTERTYPE
{
	MON_BIYAM = 0,
	MON_TIGER,
	MON_NINJA,
};

enum MONANI
{
	MANI_BREATH = 0,
	MANI_ATTACK,
};

class CMonster
{
private:
	CTexture m_monBreath[4];
	int breathMax;
	CTexture m_monAttack[2];
	int x, y;

	MONSTERTYPE m_MonsterType;
	MONANI m_MonsterAni;
	bool isDead;

	int m_frame;

	CDelay m_delay;
	CDelay m_attackDelay;

public:
	CMonster();
	virtual ~CMonster();

	virtual void Initial(CGraphics &g, MONSTERTYPE type, int x, int y);
	virtual void Update(double et, CHero& hero, CGameMap &map);
	virtual void Draw(CGraphics &g, CGameMap &map);
	virtual void Destroy();
};