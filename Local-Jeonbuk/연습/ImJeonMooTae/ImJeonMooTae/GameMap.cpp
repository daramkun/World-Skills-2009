#include "GameMap.h"
#include "Extern.h"

CGameMap::CGameMap(void)
{
}

CGameMap::~CGameMap(void)
{
}

void CGameMap::LoadMap(CGameState *gs, int index)
{
	switch(index)
	{
	case 0:
		m_mapData.Create(g_Game.GetG(), "Resource/Map/Map_01.png");

		gs->m_Mon[0].Initial(g_Game.GetG(), MON_BIYAM, 550, 340);
		gs->m_Mon[1].Initial(g_Game.GetG(), MON_BIYAM, 250, 340);
		gs->m_Mon[2].Initial(g_Game.GetG(), MON_TIGER, 1720, 280);
		gs->m_Mon[3].Initial(g_Game.GetG(), MON_TIGER, 1220, 280);
		gs->m_Mon[4].Initial(g_Game.GetG(), MON_BIYAM, 2020, 340);
		gs->m_MonLength = 5;

		gs->m_Item[0].Create(g_Game.GetG(), IT_SSANGHWATANG, 1000);
		gs->m_ItLength = 1;

		gs->m_Eq.Create(g_Game.GetG(), ET_SWORD, 500);

		m_bossClear = true;
		break;
	case 1:
		m_mapData.Create(g_Game.GetG(), "Resource/Map/Map_02.png");
		break;
	case 2:
		m_mapData.Create(g_Game.GetG(), "Resource/Map/Map_03.png");
		break;
	}

	m_currentX = 0;

	nowMapNumber = index;
}

void CGameMap::Update(double et)
{

}

void CGameMap::Draw()
{
	m_mapData.Draw(g_Game.GetG(), m_currentX, 0);
}