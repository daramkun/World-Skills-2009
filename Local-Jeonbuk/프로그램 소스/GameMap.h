#pragma once

#include "Img.h"

#include "Hero.h"
#include "Enermy.h"
#include "Item.h"
#include "Trap.h"

//////////////////////////////////////////////////////////////////////////
// ∞‘¿” ∏ 
//////////////////////////////////////////////////////////////////////////
class CGameMap
{
	friend class CGameState;
private:
	int myIndex;
	CImg image;
	int currentX;

	CHero m_hero;
	CItem m_items[4];
	int maxItem;
	CEnermy m_enermies[20];
	int maxEnermy;
	CTrap m_traps[10];
	int maxTrap;

	bool bossIsDead;

	bool bossIsRaise;

public:
	CGameMap(void);
	~CGameMap(void);

	void LoadMap(int index);

	CHero& GetHero() { return m_hero; }

	void Initial();
	void Update(double dt);
	void Draw();
	void Destroy();
};
