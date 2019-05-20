#pragma once

#include "State.h"
#include "GameMap.h"
#include "Hero.h"
#include "Item.h"
#include "Monster.h"
#include "SpriteFont.h"
#include "Equip.h"

class CGameState :
	public CState
{
	friend class CGameMap;
private:
	CGameMap m_GameMap;
	CHero m_hero;
	CMonster m_Mon[40];
	int m_MonLength;
	CItem m_Item[10];
	int m_ItLength;
	CEquip m_Eq;
	CSpriteFont m_level;
	CSpriteFont m_help;

	CTexture m_interface[2];

	CTexture m_icon[4];

public:
	CGameState(void);
	~CGameState(void);

	void Initial();
	void Update(double et);
	void Draw();
	void Destroy();
};