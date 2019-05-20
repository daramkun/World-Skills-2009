#pragma once

#include "Ani.h"
#include "Delay.h"

#include "Hero.h"

//////////////////////////////////////////////////////////////////////////
// 적 타입
//////////////////////////////////////////////////////////////////////////
enum EnermyType
{
	ET_Snake = 0,
	ET_WildBoar,
	ET_Ninja,
	ET_IMUGI,
};

//////////////////////////////////////////////////////////////////////////
// 적 애니메이션 상황
//////////////////////////////////////////////////////////////////////////
enum EnermyAnimation
{
	EA_WALK = 0,
	EA_ATTACK,
	EA_HIT,
};

//////////////////////////////////////////////////////////////////////////
// 적
//////////////////////////////////////////////////////////////////////////
class CEnermy
{
	friend class CGameState;
private:
	EnermyType myType;

	CAni m_ani[3];
	CImg m_metEffect;
	int ea_current;
	CImg bungae[2];

	int x, y;

	int hp;

	CDelay m_attack;
	bool isBoss;

	int bungaeX;
	bool bungaeWait;
	bool bungaeUse;

public:
	CEnermy(void);
	~CEnermy(void);

	void Initial(EnermyType et, int x, bool isBoss = false);
	void Update(double dt, CHero& hero, int cx, bool& isBossDead, bool& bossIsRaise);
	void Draw(int cx);
	void Destroy();
};
