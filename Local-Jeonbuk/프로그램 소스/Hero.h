#pragma once

#include "Ani.h"
#include "Arrow.h"

//////////////////////////////////////////////////////////////////////////
// 주인공 애니메이션 상태
//////////////////////////////////////////////////////////////////////////
enum HeroAnimation
{
	HA_BREATH = 0,
	HA_WALK = 1,
	HA_JUMP = 2,
	HA_SIT = 3,
	HA_HIT = 4,
	HA_KICK = 5,
	HA_PUNCH = 6,
	HA_SWORD = 7,
	HA_BOW = 8,
	HA_DEAD = 9,
};

//////////////////////////////////////////////////////////////////////////
// 주인공 착용 아이템
//////////////////////////////////////////////////////////////////////////
enum HeroCurrentEquip
{
	HCE_FIST,
	HCE_SWORD,
	HCE_BOW,
};

//////////////////////////////////////////////////////////////////////////
// 주인공
//////////////////////////////////////////////////////////////////////////
class CHero
{
	friend class CGameState;
	friend class CEnermy;
	friend class CItem;
	friend class CTrap;
private:
	CAni m_ani[10];
	int currentAni;

	CAni m_eqSAni[10];
	CAni m_eqBAni[10];
	CImg m_Shield;

	CArrow m_arrow;

	int x, y;

	double jumpRadian;

	int hp, maxHp;
	int level;
	int attackPoint;
	int exp;

	bool haveSword;
	bool haveBow;
	bool haveShield;

	HeroCurrentEquip myEquip;

	int haveSsanghwa;

public:
	CHero(void);
	~CHero(void);

	int GetHP() { return hp; }
	int GetMaxHP() { return maxHp; }

	int GetWidth() { return m_ani[currentAni].GetWidth(); }
	int GetHeight() { return m_ani[currentAni].GetHeight(); }

	void Initial();
	void Update(double dt, int &mapX, int );
	void Draw();
	void Destroy();
};
