#include "Equip.h"

CEquip::CEquip(void)
{
}

CEquip::~CEquip(void)
{
}

void CEquip::Create(CGraphics& g, EQUIPTYPE et, int x)
{
	switch(et)
	{
	case ET_SWORD:
		m_equipImage.Create(g, "Resource/OurHero/Sword/Kal.png");
		m_x = x;
		break;
	}

	m_equipType = et;
}

void CEquip::Update(double et, CHero& hero, CGameMap &map)
{
	if(isWearing) return;

	if(hero.x - map.m_currentX <= m_x + 100 &&
		m_x <= hero.x - map.m_currentX +
		((hero.m_aniType == ANI_DOWNKICK) ? hero.m_HeroKick.GetWidth() : hero.m_HeroBreath[0].GetWidth())
		&& hero.GetY() <= 380 + 100 && 380 <= hero.GetY() + 250)
	{
		isWearing = true;
		hero.m_myEquip = m_equipType;
	}
}

void CEquip::Draw(CGraphics& g, CGameMap &map)
{
	if(isWearing) return;

	m_equipImage.Draw(g, m_x + map.m_currentX, 380);
}

void CEquip::Destroy()
{

}