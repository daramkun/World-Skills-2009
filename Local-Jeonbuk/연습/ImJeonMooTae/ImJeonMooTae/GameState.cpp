#include "GameState.h"
#include "Extern.h"

CGameState::CGameState(void)
{
}

CGameState::~CGameState(void)
{
}

void CGameState::Initial()
{
	m_GameMap.LoadMap(this, 0);
	m_hero.Initialize();

	if(!m_interface[0].Create(g_Game.GetG(), "Resource/Interface/01.png"))
		MessageBox(NULL, NULL, NULL, NULL);
	
	if(!m_interface[1].Create(g_Game.GetG(), "Resource/Interface/02.png"))
		MessageBox(NULL, NULL, NULL, NULL);

	m_icon[ET_SWORD].Create(g_Game.GetG(), "Resource/Item/sword.png");

	m_level.Create(g_Game.GetG(), "MS Gothic", 14);
	m_help.Create(g_Game.GetG(), "MS Gothic", 8);
}

void CGameState::Update(double et)
{
	m_GameMap.Update(et);
	if(m_hero.hp > 0)
		m_hero.Update(et, m_GameMap);

	for(int i = 0; i < m_MonLength; i++)
		m_Mon[i].Update(et, m_hero, m_GameMap);
	
	for(int i = 0; i < m_ItLength; i++)
		m_Item[i].Update(et, m_GameMap, m_hero);

	if(m_hero.x - m_GameMap.m_currentX >= m_GameMap.m_mapData.GetWidth() && m_GameMap.m_bossClear)
	{
		m_GameMap.LoadMap(this, ++m_GameMap.nowMapNumber);
		m_hero.x = 0;
		m_GameMap.m_bossClear = false;
		m_hero.m_myEquip = ET_NONE;
	}

	m_Eq.Update(et, m_hero, m_GameMap);
}

void CGameState::Draw()
{
	m_GameMap.Draw();
	m_hero.Draw();

	for(int i = 0; i < m_MonLength; i++)
		m_Mon[i].Draw(g_Game.GetG(), m_GameMap);
	
	for(int i = 0; i < m_ItLength; i++)
		m_Item[i].Draw(g_Game.GetG(), m_GameMap);

	m_Eq.Draw(g_Game.GetG(), m_GameMap);

	m_interface[0].Draw(g_Game.GetG(), 10, 10);
	m_interface[1].Draw(g_Game.GetG(), 86, 74, 0, 0, ((float)m_hero.hp / (float)m_hero.mapHp) * 278, 23);

	m_icon[m_hero.m_myEquip].Draw(g_Game.GetG(), 10, 80);
	
	char clevel[10] = {0, };
	wsprintf(clevel, "Lv. %d", m_hero.level);

	m_level.DrawShadow(g_Game.GetG(), 110, 45, D3DCOLOR_XRGB(255, 255, 255), clevel);
	m_help.DrawShadow(g_Game.GetG(), 110, 10, D3DCOLOR_XRGB(255, 255, 255), 
		"Left Move : ก็, Right Move : กๆ, Attack : Space, Jump : ก่, Sitdown : ก้");
}

void CGameState::Destroy()
{

}
