#include "Hero.h"
#include "Input.h"
#include "Lib.h"

#define JUMP_RANGE 0.04

CHero::CHero(void)
{
}

CHero::~CHero(void)
{
}

void CHero::Initial()
{
	m_ani[HA_BREATH].Create("Content/Hero/", 1, 4, 100);
	m_ani[HA_WALK].Create("Content/Hero/°È±â/", 1, 4, 100);
	m_ani[HA_SIT].Create("Content/Hero/¾É±â/", 2, 2);
	m_ani[HA_KICK].Create("Content/Hero/¾É±â/", 3, 4, 100);
	m_ani[HA_PUNCH].Create("Content/Hero/ÁÖ¸Ô/", 1, 3, 100);
	m_ani[HA_HIT].Create("Content/Hero/ÇÇ°Ý/", 1, 1);
	m_ani[HA_SWORD].Create("Content/Hero/Ä®°ø°Ý/", 1, 3, 100);
	m_ani[HA_BOW].Create("Content/Hero/È°°ø°Ý/", 1, 4, 100);
	m_ani[HA_DEAD].Create("Content/Hero/Á×À½/", 1, 1);

	m_eqSAni[HA_BREATH].Create("Content/Hero/Ä®/", 1, 4);
	m_eqSAni[HA_WALK].Create("Content/Hero/Ä®/°È±â/", 1, 4);
	m_eqSAni[HA_SIT].Create("Content/Hero/Ä®/¾É¾Æ°ø°Ý/", 2, 2);
	m_eqSAni[HA_HIT].Create("Content/Hero/Ä®/ÇÇ°Ý/", 1, 2);
	m_eqSAni[HA_KICK].Create("Content/Hero/Ä®/¾É¾Æ°ø°Ý/", 2, 2);

	m_eqBAni[HA_BREATH].Create("Content/Hero/È°/", 1, 4);
	m_eqBAni[HA_WALK].Create("Content/Hero/È°/°È±â/", 1, 4);
	m_eqBAni[HA_SIT].Create("Content/Hero/È°/¾É¾Æ°ø°Ý/", 2, 2);
	m_eqBAni[HA_HIT].Create("Content/Hero/È°/ÇÇ°Ý/", 1, 1);
	m_eqBAni[HA_KICK].Create("Content/Hero/È°/¾É¾Æ°ø°Ý/", 2, 2);

	m_Shield.Create("Content/Etc/½Çµå.png");
	
	x = 0;
	y = 210 - sin(0.0f) * 150;
	
	hp = 50;
	maxHp = 50;

	currentAni = HA_BREATH;
	haveSword = haveBow = false;
	haveSsanghwa = 0;

	level = 1;
	exp = 0;
	myEquip = HCE_FIST;

	attackPoint = 5;
	haveSsanghwa = 0;
}

void CHero::Update(double dt, int &mapX, int mapMax)
{
	bool Changed = false;

	if(exp >= 40)
	{
		maxHp += 30;
		attackPoint += 2;
		level++;
		exp = 0;
		CLib::SoundPlay("Content/Sound/LevelUp.wav");
	}

	if(g_Input.KeyDown(DIK_X))
	{
		if(haveSsanghwa >= 1)
		{
			hp = maxHp;
			haveSsanghwa--;
		}
		CLib::SoundPlay("Content/Sound/EatSS.wav");
	}

	if(g_Input.KeyDown(DIK_Z))
	{
		switch(myEquip)
		{
		case HCE_FIST:
			if(haveSword)
				myEquip = HCE_SWORD;
			else if(haveBow)
				myEquip = HCE_BOW;
			else
				myEquip = HCE_FIST;
			break;
		case HCE_SWORD:
			if(haveBow)
				myEquip = HCE_BOW;
			else
				myEquip = HCE_FIST;
			break;
		case HCE_BOW:
			myEquip = HCE_FIST;
			break;
		default:
			myEquip = HCE_FIST;
			break;
		}
		CLib::SoundPlay("Content/Sound/SetEquip.wav");
	}

	if(g_Input.KeyPress(DIK_LEFT) && (currentAni == HA_BREATH || currentAni == HA_WALK
		 || currentAni == HA_JUMP))
	{
		if(x > 0)
			x -= 2 * dt;

		currentAni = HA_WALK;
		Changed = true;
	}

	if(g_Input.KeyPress(DIK_RIGHT) && (currentAni == HA_BREATH || currentAni == HA_WALK
		|| currentAni == HA_JUMP))
	{
		if(x > 640 / 2 - m_ani[currentAni].GetWidth() / 2 && -mapX <= mapMax - 640)
		{
			mapX -= 5 * dt;
		}
		else
		{
			if(x < 640 - m_ani[currentAni].GetWidth())
				x += 5 * dt;
		}

		currentAni = HA_WALK;
		Changed = true;
	}

	if(g_Input.KeyPress(DIK_UP) && (currentAni != HA_DEAD))
	{
		if(jumpRadian == 0)
		{
			CLib::SoundPlay("Content/Sound/Jump.wav");
			jumpRadian += JUMP_RANGE * dt;
		}
		Changed = true;
	}

	if(jumpRadian > 0)
	{
		jumpRadian += JUMP_RANGE * dt;
		if(y > 210 - sin(0.0f) * 150)
			jumpRadian = 0;

		y = 210 - sin(jumpRadian) * 150;
	}

	if(g_Input.KeyPress(DIK_DOWN) && (currentAni == HA_BREATH || currentAni == HA_WALK || 
		currentAni == HA_SIT || currentAni == HA_KICK))
	{
		if(jumpRadian == 0)
		{
			if(currentAni != HA_KICK)
				currentAni = HA_SIT;
			Changed = true;
		}
	}

	if(g_Input.KeyDown(DIK_SPACE))
	{
		if(currentAni == HA_SIT)
		{
			currentAni = HA_KICK;
			CLib::SoundPlay("Content/Sound/Kick.wav");
		}
		else if(currentAni == HA_BREATH)
		{
			switch(myEquip)
			{
			case HCE_FIST:
				currentAni = HA_PUNCH;
				CLib::SoundPlay("Content/Sound/Punch.wav");
				break;
			case HCE_SWORD:
				currentAni = HA_SWORD;
				CLib::SoundPlay("Content/Sound/Sword.wav");
				break;
			case HCE_BOW:
				currentAni = HA_BOW;
				break;
			}
		}

		Changed = true;
	}

	m_arrow.Update(dt);

	if(hp <= 0)
		currentAni = HA_DEAD;

	if(!m_ani[currentAni].Update())
	{
		if((currentAni == HA_PUNCH || currentAni == HA_SWORD || currentAni == HA_BOW
			 || currentAni == HA_HIT))
		{
			if(currentAni == HA_BOW && !m_arrow.isShow)
			{
				m_arrow.Create(x + 130, y + 100);
				CLib::SoundPlay("Content/Sound/Bow.wav");
			}
			currentAni = HA_BREATH;
		}
		else if(currentAni == HA_KICK)
		{
			currentAni = HA_SIT;
		}
	}
	//else
	//	Changed = true;

	if(!Changed && !(currentAni == HA_PUNCH || currentAni == HA_SWORD || currentAni == HA_BOW
		|| currentAni == HA_HIT || currentAni == HA_DEAD || currentAni == HA_KICK))
	{
		currentAni = HA_BREATH;
	}
}

void CHero::Draw()
{
	m_ani[currentAni].Draw(x, y);
	if(myEquip == HCE_SWORD)
	{
		m_eqSAni[currentAni].currentFrame = m_ani[currentAni].currentFrame;
		m_eqSAni[currentAni].Draw(x, y);
	}
	else if(myEquip == HCE_BOW)
	{
		m_eqBAni[currentAni].currentFrame = m_ani[currentAni].currentFrame;
		m_eqBAni[currentAni].Draw(x, y);
	}
	if(haveShield && currentAni == HA_SIT)
		m_Shield.Draw(x, y, D3DCOLOR_ARGB(140, 255, 255, 255));

	m_arrow.Draw();
}

void CHero::Destroy()
{

}