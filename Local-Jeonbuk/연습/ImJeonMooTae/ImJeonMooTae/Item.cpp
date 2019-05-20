#include "Item.h"

#define ITEMY 400

CItem::CItem(void)
{
}

CItem::~CItem(void)
{
}

void CItem::Create(CGraphics &g, ITEMTYPE type, int item_x)
{
	switch(type)
	{
	case IT_SSANGHWATANG:
		m_item.Create(g, "Resource/Item/Ssanghwatang.png");
		break;
	}

	x = item_x;
}

void CItem::Update(double et, CGameMap &map, CHero &hero)
{
	if(isDead) return;

	if(hero.x - map.m_currentX + 10 <= x + m_item.GetWidth() &&
		x <= hero.x - map.m_currentX + 130 - 20 &&
		hero.GetY() <= ITEMY + m_item.GetHeight() &&
		ITEMY <= hero.GetY() + 250)
	{
		hero.hp = hero.mapHp;
		isDead = true;
	}
}

void CItem::Draw(CGraphics &g, CGameMap &map)
{
	if(isDead) return;
	m_item.Draw(g, x + map.m_currentX, ITEMY); 
}