#pragma once

#include "Texture.h"
#include "GameMap.h"
#include "Delay.h"

enum EQUIPTYPE
{
	ET_NONE = 0,
	ET_SWORD,
	ET_BOW,
	ET_SPEAR,
};

enum ANITYPE
{
	ANI_BREATH = 0,
	ANI_WALK,
	ANI_JUMP,
	ANI_PUNCH,
	ANI_DOWN,
	ANI_DOWNKICK,
	ANI_SWORD,
	ANI_BOW,
	ANI_SPEAR,
	ANI_AK,
};

class CHero
{
	friend class CGameMap;
	friend class CGameState;
	friend class CItem;
	friend class CMonster;
	friend class CEquip;
private:
	CTexture m_HeroBreath[4];
	CTexture m_HeroWalk[4];
	CTexture m_HeroPunch[4];
	CTexture m_HeroSit;
	CTexture m_HeroKick;
	CTexture m_HeroDead;

	CTexture m_SwordBreath[4];
	CTexture m_SwordWalk[4];
	CTexture m_SwordCut[3];
	CTexture m_SwordSit;
	CTexture m_SwordKick;

	int x;
	float multiplyY;

	int mapHp;
	int hp;
	int level;
	int exp;

	ANITYPE m_aniType;
	int m_aniFrame;

	CDelay aniDelay;

	EQUIPTYPE m_myEquip;

public:
	CHero(void);
	~CHero(void);

	void Initialize();

	int GetX() { return x; }
	void SetX(int x) { this->x = x; }

	int GetY() { return (int)(220 - (sin(multiplyY) * 150)); }

	void Update(double et, CGameMap &map);
	void Draw();
};