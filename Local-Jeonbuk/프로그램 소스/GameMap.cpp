#include "GameMap.h"
#include "Game.h"

CGameMap::CGameMap(void)
{
}

CGameMap::~CGameMap(void)
{
}

void CGameMap::LoadMap(int index)
{
	bossIsDead = false;

	switch(index)
	{
	case 0:
		image.Create("Content/Map/1.png");
		m_items[0].Initial(IT_Sword, 1220);
		m_items[1].Initial(IT_Ssanghwatang, 1400);
		m_items[2].Initial(IT_Shield, 2800);
		maxItem = 3;
		m_enermies[0].Initial(ET_Snake, 320);
		m_enermies[1].Initial(ET_WildBoar, 500);
		m_enermies[2].Initial(ET_WildBoar, 780);
		m_enermies[3].Initial(ET_Snake, 1450);
		m_enermies[4].Initial(ET_Snake, 1680);
		m_enermies[5].Initial(ET_Snake, 1850);
		m_enermies[6].Initial(ET_WildBoar, 2280);
		m_enermies[7].Initial(ET_Snake, 2650);
		maxEnermy = 8;
		m_traps[0].Initial(TT_Pool, 630);
		m_traps[1].Initial(TT_Thorn, 1700);
		maxTrap = 2;
		bossIsDead = true;
		break;
	case 1:
		image.Create("Content/Map/2.png");
		m_items[0].Initial(IT_Ssanghwatang, 1020);
		m_items[1].Initial(IT_Bow, 1440);
		m_items[2].Initial(IT_Ssanghwatang, 2700);
		maxItem = 3;
		m_enermies[0].Initial(ET_Ninja, 240);
		m_enermies[1].Initial(ET_Ninja, 500);
		m_enermies[2].Initial(ET_Ninja, 680);
		m_enermies[3].Initial(ET_Ninja, 1060);
		m_enermies[4].Initial(ET_WildBoar, 1530);
		m_enermies[5].Initial(ET_WildBoar, 1730);
		m_enermies[6].Initial(ET_Snake, 2040);
		m_enermies[7].Initial(ET_Snake, 2210);
		m_enermies[8].Initial(ET_Snake, 2430);
		m_enermies[9].Initial(ET_Ninja, 3050);
		m_enermies[10].Initial(ET_Ninja, 3110);
		m_enermies[11].Initial(ET_Ninja, 3260);
		m_enermies[12].Initial(ET_Snake, 3300);
		m_enermies[13].Initial(ET_IMUGI, 4000 - 600);
		maxEnermy = 14;
		m_traps[0].Initial(TT_Thorn, 380);
		m_traps[2].Initial(TT_Thorn, 1220);
		m_traps[1].Initial(TT_Pool, 2010);
		m_traps[3].Initial(TT_Thorn, 2840);
		maxTrap = 4;
		break;
	default:
		g_Game.SetIndex(1);
		break;
	}

	bossIsRaise = false;
	myIndex = index;
	currentX = 0;
}

void CGameMap::Initial()
{
	m_hero.Initial();
}

void CGameMap::Update(double dt)
{
	m_hero.Update(dt, currentX, image.GetWidth());
	for(int i = 0; i < maxItem; i++)
		m_items[i].Update(m_hero, currentX);
	for(int i = 0; i < maxEnermy; i++)
		m_enermies[i].Update(dt, m_hero, currentX, bossIsDead, bossIsRaise);
	for(int i = 0; i < maxTrap; i++)
		m_traps[i].Update(m_hero, currentX);
}

void CGameMap::Draw()
{
	image.Draw(currentX, 0);
	for(int i = 0; i < maxItem; i++)
		m_items[i].Draw(currentX);
	for(int i = 0; i < maxTrap; i++)
		m_traps[i].Draw(currentX);
	m_hero.Draw();
	for(int i = 0; i < maxEnermy; i++)
		m_enermies[i].Draw(currentX);
}

void CGameMap::Destroy()
{
	image.Destroy();
}