#include "Hero.h"
#include "Extern.h"

#define TIMES 0.07
#define MOVERANGE 7

CHero::CHero(void)
{
}

CHero::~CHero(void)
{
}

void CHero::Initialize()
{
	m_HeroBreath[0].Create(g_Game.GetG(), "Resource/OurHero/01.png");
	m_HeroBreath[1].Create(g_Game.GetG(), "Resource/OurHero/02.png");
	m_HeroBreath[2].Create(g_Game.GetG(), "Resource/OurHero/03.png");
	m_HeroBreath[3].Create(g_Game.GetG(), "Resource/OurHero/02.png");
	m_HeroWalk[0].Create(g_Game.GetG(), "Resource/OurHero/Walk/01.png");
	m_HeroWalk[1].Create(g_Game.GetG(), "Resource/OurHero/Walk/02.png");
	m_HeroWalk[2].Create(g_Game.GetG(), "Resource/OurHero/Walk/03.png");
	m_HeroWalk[3].Create(g_Game.GetG(), "Resource/OurHero/Walk/02.png");
	m_HeroPunch[0].Create(g_Game.GetG(), "Resource/OurHero/Punch/01.png");
	m_HeroPunch[1].Create(g_Game.GetG(), "Resource/OurHero/Punch/02.png");
	m_HeroPunch[2].Create(g_Game.GetG(), "Resource/OurHero/Punch/03.png");
	m_HeroPunch[3].Create(g_Game.GetG(), "Resource/OurHero/Punch/02.png");
	m_HeroSit.Create(g_Game.GetG(), "Resource/OurHero/Sit/01.png");
	m_HeroKick.Create(g_Game.GetG(), "Resource/OurHero/Kick/01.png");
	m_HeroDead.Create(g_Game.GetG(), "Resource/OurHero/YouAreDead.png");

	m_SwordBreath[0].Create(g_Game.GetG(), "Resource/OurHero/Sword/KB01.png");
	m_SwordBreath[1].Create(g_Game.GetG(), "Resource/OurHero/Sword/KB01.png");
	m_SwordBreath[2].Create(g_Game.GetG(), "Resource/OurHero/Sword/KB02.png");
	m_SwordBreath[3].Create(g_Game.GetG(), "Resource/OurHero/Sword/KB01.png");

	m_SwordWalk[0].Create(g_Game.GetG(), "Resource/OurHero/Sword/Walk/KW01.png");
	m_SwordWalk[1].Create(g_Game.GetG(), "Resource/OurHero/Sword/Walk/KW02.png");
	m_SwordWalk[2].Create(g_Game.GetG(), "Resource/OurHero/Sword/Walk/KW03.png");
	m_SwordWalk[3].Create(g_Game.GetG(), "Resource/OurHero/Sword/Walk/KW02.png");


	m_SwordCut[0].Create(g_Game.GetG(), "Resource/OurHero/Sword/Cut/01.png");
	m_SwordCut[1].Create(g_Game.GetG(), "Resource/OurHero/Sword/Cut/02.png");
	m_SwordCut[2].Create(g_Game.GetG(), "Resource/OurHero/Sword/Cut/03.png");

	m_SwordSit.Create(g_Game.GetG(), "Resource/OurHero/Sit/S01.png");
	m_SwordKick.Create(g_Game.GetG(), "Resource/OurHero/Kick/S01.png");

	aniDelay.Set(70);

	hp = 50;
	mapHp = 50;
	level = 1;
}

void CHero::Update(double et, CGameMap &map)
{
	if(m_aniType == ANI_BREATH || m_aniType == ANI_WALK || m_aniType == ANI_JUMP || m_aniType == ANI_DOWN)
	{
		bool hasChange = false;

		if(g_Game.GetI().KeyPress(DIK_LEFT) && m_aniType != ANI_DOWN)
		{
			if(x - map.m_currentX > 0)
			{
				if((x - (MOVERANGE - 3) * et) < 640 / 2 - 130 / 2)
					if(map.m_currentX + (MOVERANGE - 3) * et > 0)
						x -= (MOVERANGE - 3) * et;
					else
						map.m_currentX += (MOVERANGE - 3) * et;
				else
					x -= (MOVERANGE - 3) * et;
			}

			m_aniType = ANI_WALK;
			hasChange = true;
		}
		else if(g_Game.GetI().KeyPress(DIK_RIGHT) && m_aniType != ANI_DOWN)
		{
			if((x - map.m_currentX) > -(map.m_mapData.GetWidth() - 640 - 130))
			{
				if((x + MOVERANGE * et) > 640 / 2 - 130 / 2)
					if(map.m_currentX - MOVERANGE * et < -(map.m_mapData.GetWidth() - 640))
						x += MOVERANGE * et;
					else
						map.m_currentX -= MOVERANGE * et;
				else
					x += MOVERANGE * et;
			}

			m_aniType = ANI_WALK;
			hasChange = true;
		}

		if(g_Game.GetI().KeyPress(DIK_UP) && m_aniType != ANI_DOWN)
		{
			if(multiplyY == 0)
			{
				multiplyY = TIMES;
				hasChange = true;
				sndPlaySound("Resource/Sound/Jump.wav", SND_ASYNC);
			}
		}


		if(g_Game.GetI().KeyPress(DIK_DOWN))
		{
			if(multiplyY == 0)
			{
				m_aniType = ANI_DOWN;
				hasChange = true;
			}
		}

		if(g_Game.GetI().KeyDown(DIK_SPACE))
		{
			if(multiplyY == 0)
			{
				if(m_aniType == ANI_DOWN)
				{
					m_aniType = ANI_DOWNKICK;
					hasChange = true;
					sndPlaySound("Resource/Sound/Kick.wav", SND_ASYNC);
				}
				else
				{
					switch(m_myEquip)
					{
					case ET_NONE:
						m_aniType = ANI_PUNCH;
						hasChange = true;
						m_aniFrame = 0;
						sndPlaySound("Resource/Sound/Punch.wav", SND_ASYNC);
						break;
					case ET_SWORD:
						m_aniType = ANI_SWORD;
						hasChange = true;
						m_aniFrame = 0;
						sndPlaySound("Resource/Sound/Sword.wav", SND_ASYNC);
						break;
					}
				}
			}
		}

		if(multiplyY > 0)
		{
			multiplyY += TIMES * et;
			if(220 - (sin(multiplyY) * 150) > 220 - (sin(0.0f) * 150))
				multiplyY = 0;
		}

		if(!hasChange)
		{
			m_aniType = ANI_BREATH;
		}
	}

	if(aniDelay.Check())
	{
		m_aniFrame++;
		if(m_aniType == ANI_SWORD)
			if(m_aniFrame > 2)
			{
				m_aniFrame = 0;
				if(m_aniType != ANI_BREATH && m_aniType != ANI_WALK/* && m_aniType != ANI_DOWN*/)
				{
					if(m_aniType != ANI_DOWN && m_aniType != ANI_DOWNKICK)
						m_aniType = ANI_BREATH;
				}
			}
			if(m_aniFrame > 3)
			{
				m_aniFrame = 0;
				if(m_aniType != ANI_BREATH && m_aniType != ANI_WALK/* && m_aniType != ANI_DOWN*/)
				{
					if(m_aniType != ANI_DOWN && m_aniType != ANI_DOWNKICK)
						m_aniType = ANI_BREATH;
				}
			}


			if(m_aniType == ANI_DOWNKICK)
				m_aniType = ANI_DOWN;

			aniDelay.Reset();
	}
}

void CHero::Draw()
{
	if(hp <= 0)
	{
		m_HeroDead.Draw(g_Game.GetG(), x - 30, 120 + 220);
	}
	else
	{
		switch(m_aniType)
		{
		case ANI_BREATH:
			m_HeroBreath[m_aniFrame].Draw(g_Game.GetG(), x, 220 - (sin(multiplyY) * 150));
			switch(m_myEquip)
			{
			case ET_SWORD:
				m_SwordBreath[m_aniFrame].Draw(g_Game.GetG(), x, 220 - (sin(multiplyY) * 150));
				break;
			}
			break;
			break;
		case ANI_WALK:
			m_HeroWalk[m_aniFrame].Draw(g_Game.GetG(), x, 220 - (sin(multiplyY) * 150));
			switch(m_myEquip)
			{
			case ET_SWORD:
				m_SwordWalk[m_aniFrame].Draw(g_Game.GetG(), x, 220 - (sin(multiplyY) * 150));
				break;
			}
			break;
		case ANI_PUNCH:
			m_HeroPunch[m_aniFrame].Draw(g_Game.GetG(), x + 10, 220 - (sin(multiplyY) * 150));
			break;
		case ANI_DOWN:
			m_HeroSit.Draw(g_Game.GetG(), x + 10, 220 - (sin(multiplyY) * 150));
			switch(m_myEquip)
			{
			case ET_SWORD:
				m_SwordSit.Draw(g_Game.GetG(), x + 10, 220 - (sin(multiplyY) * 150));
				break;
			}
			break;
		case ANI_DOWNKICK:
			m_HeroKick.Draw(g_Game.GetG(), x + 10, 220 - (sin(multiplyY) * 150));
			switch(m_myEquip)
			{
			case ET_SWORD:
				m_SwordKick.Draw(g_Game.GetG(), x + 10, 220 - (sin(multiplyY) * 150));
				break;
			}
			break;
		case ANI_SWORD:
			m_SwordCut[m_aniFrame].Draw(g_Game.GetG(), x + 10, 220 - (sin(multiplyY) * 150));
			break;
		}
	}
}