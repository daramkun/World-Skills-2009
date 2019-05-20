#include "Enermy.h"
#include "Lib.h"

CEnermy::CEnermy(void)
{
}

CEnermy::~CEnermy(void)
{
}

void CEnermy::Initial(EnermyType et, int x, bool isBoss)
{
	this->x = x;
	myType = et;
	ea_current = EA_WALK;

	switch(et)
	{
	case ET_Snake:
		m_ani[0].Create("Content/Enermy/Biyam/", 1, 4, 200);
		m_ani[1].Create("Content/Enermy/Biyam/공격/", 1, 3, 200);
		m_ani[2].Create("Content/Enermy/Biyam/피격/", 1, 2, 200);
		y = 250;
		hp = 10;
		m_attack.Set(700);
		break;
	case ET_WildBoar:
		m_ani[0].Create("Content/Enermy/Metdaegi/", 1, 4, 200);
		m_ani[1].Create("Content/Enermy/Metdaegi/돌진/", 1, 2, 200);
		m_ani[2].Create("Content/Enermy/Metdaegi/피격/", 1, 2, 200);
		m_metEffect.Create("Content/Enermy/Metdaegi/돌진/이펙.png");
		y = 250;
		hp = 20;
		m_attack.Set(700);
		break;
	case ET_Ninja:
		m_ani[0].Create("Content/Enermy/Niinja/", 1, 4, 200);
		m_ani[1].Create("Content/Enermy/Niinja/공격/", 1, 4, 200);
		m_ani[2].Create("Content/Enermy/Niinja/피격/", 1, 2, 200);
		y = 200;
		hp = 40;
		m_attack.Set(700);
		break;
	case ET_IMUGI:
		m_ani[0].Create("Content/Enermy/Buraqui/", 1, 1, 200);
		m_ani[1].Create("Content/Enermy/Buraqui/", 2, 2, 2000);
		m_ani[2].Create("Content/Enermy/Buraqui/피격/", 1, 1, 200);
		bungae[0].Create("Content/Enermy/Buraqui/At/1.png");
		bungae[1].Create("Content/Enermy/Buraqui/At/2.png");
		y = 0;
		hp = 200;
		m_attack.Set(1600);
		break;
	}

	this->isBoss = isBoss;
}

void CEnermy::Update(double dt, CHero& hero, int cx, bool& isBossDead, bool& bossIsRaise)
{
	if(hp <= 0) return;
	if(!CLib::Crash(x + cx, y, m_ani[ea_current].GetWidth(), m_ani[ea_current].GetHeight(),
		0, 0, 640, 480)) return;

	if(myType == ET_Snake)
	{
		if(CLib::Crash(x + 20, y, m_ani[ea_current].GetWidth(), m_ani[ea_current].GetHeight(),
			hero.x - cx, hero.y, ((hero.currentAni == HA_KICK || hero.currentAni == HA_SWORD) ? hero.GetWidth() : 130), hero.GetHeight()))
		{
			if(hero.currentAni == HA_KICK || hero.currentAni == HA_SWORD)
			{
				if(ea_current != EA_HIT)
				{
					hp -= hero.attackPoint;
					if(hp <= 0)
						hero.exp += 5;
					ea_current = EA_HIT;
					x += 10;
					m_ani[ea_current].currentFrame = 0;
				}
			}
			else
			{
				if(ea_current != EA_ATTACK && hero.currentAni != HA_HIT && 
					hero.jumpRadian <= 0.14 && hero.currentAni != HA_DEAD &&
					ea_current != EA_HIT)
				{
					if(m_attack.Check())
					{
						ea_current = EA_ATTACK;
						m_ani[ea_current].currentFrame = 0;
						if(hero.haveShield && hero.currentAni == HA_SIT)
						{
							hero.hp -= 2;
						}
						else
						{
							hero.hp -= 4;
							hero.currentAni = HA_HIT;
						}

						hero.x -= 5;

						CLib::SoundPlay("Content/Sound/SnAttack.wav");

						m_attack.Reset();
					}
				}
			}
		}
	}
	else if(myType == ET_WildBoar)
	{
		if(CLib::Crash(x, y, m_ani[ea_current].GetWidth(), m_ani[ea_current].GetHeight(),
			hero.x - cx, hero.y, hero.GetWidth(), hero.GetHeight()))
		{
			if(hero.currentAni == HA_KICK || hero.currentAni == HA_PUNCH ||
				hero.currentAni == HA_SWORD)
			{
				hp -= hero.attackPoint;
				if(hp <= 0)
					hero.exp += 10;
				ea_current = EA_HIT;
				m_ani[ea_current].currentFrame = 0;
				x += 20;
			}

		}

		if(CLib::Crash(x, y, m_ani[ea_current].GetWidth(), m_ani[ea_current].GetHeight(),
			hero.x - cx + 320, hero.y, 130, hero.GetHeight()))
		{
			if(m_attack.Check())
			{
				if(ea_current != EA_ATTACK && hero.currentAni != HA_HIT && 
					hero.jumpRadian <= 0.14 && hero.currentAni != HA_DEAD &&
					ea_current != EA_HIT)
				{
					ea_current = EA_ATTACK;
					m_ani[ea_current].currentFrame = 0;
				}
			}
		}

		if(ea_current == EA_ATTACK)
		{
			x -= 5 * dt;

			if(CLib::Crash(x, y, m_ani[ea_current].GetWidth(), m_ani[ea_current].GetHeight(),
				hero.x - cx, hero.y, 130, hero.GetHeight()))
			{
				if(hero.haveShield && hero.currentAni == HA_SIT)
				{
					hero.hp -= 4;
				}
				else
				{
					hero.hp -= 8;
					hero.currentAni = HA_HIT;
				}
				hero.x -= 30;
				ea_current = EA_WALK;
				CLib::SoundPlay("Content/Sound/MetAttack.wav");

				m_attack.Reset();
			}
		}
	}
	else if(myType == ET_Ninja)
	{
		if(CLib::Crash(x + 20, y, m_ani[ea_current].GetWidth(), m_ani[ea_current].GetHeight(),
			hero.x - cx, hero.y, ((hero.currentAni == HA_KICK || hero.currentAni == HA_SWORD || 
			hero.currentAni == HA_PUNCH) ? hero.GetWidth() : 130), hero.GetHeight()))
		{
			if(hero.currentAni == HA_KICK || hero.currentAni == HA_SWORD || 
				hero.currentAni == HA_PUNCH)
			{
				if(ea_current != EA_HIT)
				{
					hp -= hero.attackPoint;
					if(hp <= 0)
						hero.exp += 20;
					ea_current = EA_HIT;
					x += 10;
					m_ani[ea_current].currentFrame = 0;
				}
			}
			else
			{
				if(ea_current != EA_ATTACK && hero.currentAni != HA_HIT && 
					hero.jumpRadian <= 0.14 && hero.currentAni != HA_DEAD &&
					ea_current != EA_HIT)
				{
					if(m_attack.Check())
					{
						ea_current = EA_ATTACK;
						m_ani[ea_current].currentFrame = 0;

						if(hero.haveShield && hero.currentAni == HA_SIT)
						{
							hero.hp -= 5;
						}
						else
						{
							hero.hp -= 10;
							hero.currentAni = HA_HIT;
						}
						hero.x -= 40;
						CLib::SoundPlay("Content/Sound/NinAttack.wav");

						m_attack.Reset();
					}
				}
			}
		}
	}
	else if(myType == ET_IMUGI)
	{
		bossIsRaise = true;
		//if(CLib::Crash(x - 300, y, m_ani[ea_current].GetWidth() + 600, m_ani[ea_current].GetHeight(),
		//	hero.x - cx, hero.y, 130, hero.GetHeight()))
		//{
			if(m_attack.Check())
			{
				if(bungaeWait)
				{
					bungaeWait = false;
					bungaeUse = true;
					CLib::SoundPlay("Content/Sound/Thunder.wav");
				}
				else if(bungaeUse)
				{
					bungaeUse = false;
					ea_current = EA_WALK;
				}
				else
				{
					bungaeX = hero.x - 10 - cx;
					bungaeWait = true;
					ea_current = EA_ATTACK;
				}
				m_attack.Reset();
			}
		//}
		
		if(CLib::Crash(x + 206, y, m_ani[ea_current].GetWidth() - 206, m_ani[ea_current].GetHeight(),
			hero.x - cx, hero.y, hero.GetWidth(), hero.GetHeight()))
		{
			if(hero.currentAni == HA_KICK || hero.currentAni == HA_SWORD || 
				hero.currentAni == HA_PUNCH)
			{
				if(ea_current != EA_HIT)
				{
					hp -= hero.attackPoint;
					if(hp <= 0)
					{
						isBossDead = true;
					}
					ea_current = EA_HIT;
					bungaeWait = false;
					x += 5;
					m_ani[ea_current].currentFrame = 0;
				}
			}
		}
	}

	if(hero.m_arrow.isShow)
	{
		if(myType == ET_IMUGI)
		{
			if(CLib::Crash(x + 206, y, m_ani[ea_current].GetWidth() - 206, m_ani[ea_current].GetHeight(),
				hero.m_arrow.x - cx, hero.m_arrow.y, hero.m_arrow.m_img.GetWidth(), hero.m_arrow.m_img.GetHeight()))
			{
				hp -= 4;
				ea_current = EA_HIT;
				if(hp <= 0)
				{
					hero.exp += 3;
					isBossDead = true;
				}
				x += 10;
				m_ani[ea_current].currentFrame = 0;
				hero.m_arrow.isShow = false;
			}
		}
		else
		{
			if(CLib::Crash(x, y, m_ani[ea_current].GetWidth(), m_ani[ea_current].GetHeight(),
				hero.m_arrow.x - cx, hero.m_arrow.y, hero.m_arrow.m_img.GetWidth(), hero.m_arrow.m_img.GetHeight()))
			{
				hp -= 8;
				ea_current = EA_HIT;
				if(hp <= 0)
				{
					hero.exp += 3;
				}
				x += 10;
				m_ani[ea_current].currentFrame = 0;
				hero.m_arrow.isShow = false;
			}
		}
	}

	if(myType == ET_IMUGI && bungaeUse && hero.currentAni != HA_HIT)
	{
		if(CLib::Crash(bungaeX, 0, bungae[1].GetWidth(), 480,
			hero.x - cx, hero.y, 130, hero.GetHeight()))
		{
			hero.hp -= 14;
			hero.currentAni = HA_HIT;
			hero.x -= 80;
			bungaeUse = false;
			ea_current = EA_WALK;
		}
	}

	if(!m_ani[ea_current].Update())
	{
		if(!(myType == ET_WildBoar && ea_current == EA_ATTACK))
			if(!(myType == ET_IMUGI && ea_current == EA_ATTACK))
				ea_current = EA_WALK;
	}

	if(myType == ET_Snake && ea_current == EA_WALK)
		x -= (int)(1.2 * dt);
	if(myType == ET_Ninja && ea_current == EA_WALK)
		x -= (int)(2.0 * dt);
}

void CEnermy::Draw(int cx)
{
	if(hp <= 0) return;
	m_ani[ea_current].Draw(x + cx, y);
	if(myType == ET_WildBoar && ea_current == EA_ATTACK)
		m_metEffect.Draw(x + cx + 50, y);

	if(bungaeWait)
		bungae[0].Draw(bungaeX + cx, 0);
	if(bungaeUse)
		bungae[1].Draw(bungaeX + cx, 0);
}

void CEnermy::Destroy()
{

}