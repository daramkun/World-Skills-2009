#include "GameState.h"
#include "Game.h"
#include "Input.h"

#include "Lib.h"

CGameState::CGameState(void)
{
}

CGameState::~CGameState(void)
{
}

void CGameState::Initial()
{
	gameMap.Initial();
	gameMap.LoadMap(0);

	inter[0].Create("Content/Interface/interface.png");
	inter[1].Create("Content/Interface/1.png");
	inter[2].Create("Content/Interface/item icon/S.png");
	inter[3].Create("Content/Interface/item icon/B.png");
	inter[4].Create("Content/Interface/item icon/SS.png");
	inter[5].Create("Content/Interface/item icon/실드.png");

	brqInter[0].Create("Content/Interface/Buraqui/1.png");
	brqInter[1].Create("Content/Interface/Buraqui/2.png");

	gameClear.Create("Content/Etc/클리어.png");
	gameOver.Create("Content/Etc/겜오버.png");

	m_levelShow.Create("MS Gothic", 12);
}

void CGameState::Update(double dt)
{
	static bool gameClear = false;

	if(gameMap.GetHero().GetHP() <= 0)
	{
		if(g_Input.KeyDown(DIK_SPACE))
		{
			gameMap.LoadMap(gameMap.myIndex);
			gameMap.GetHero().x = 0;
			gameMap.GetHero().hp = gameMap.GetHero().maxHp;
			gameMap.GetHero().currentAni = HA_BREATH;
		}
		else if(g_Input.KeyDown(DIK_ESCAPE))
		{
			g_Game.SetIndex(1);
		}
	}
	else if ((-gameMap.currentX) >= gameMap.image.GetWidth() - 640 && gameMap.bossIsDead)
	{
		if(!gameClear)
		{
			gameClear = true;
			CLib::SoundPlay("Content/Sound/StageClear.wav");
		}

		if(g_Input.KeyDown(DIK_SPACE))
		{
			if(gameMap.myIndex == 1)
				g_Game.SetIndex(1);
			else
			{
				gameMap.LoadMap(gameMap.myIndex + 1);
				gameMap.GetHero().x = 0;
				gameClear = false;
			}
		}
	}
	else
	{
		gameMap.Update(dt);
		
		if(g_Input.KeyDown(DIK_ESCAPE))
		{
			g_Game.SetIndex(1);
		}
	}
}

void CGameState::Draw()
{
	gameMap.Draw();

	inter[0].Draw(10, 10);
	CHero temp = gameMap.GetHero();
	inter[1].Draw(94, 67, 0, 0, (int)((double)temp.GetHP() / (double)temp.GetMaxHP() * (double)231), 23);
	switch(gameMap.GetHero().myEquip)
	{
	case HCE_SWORD:
		inter[2].Draw(10, 80);
		break;
	case HCE_BOW:
		inter[3].Draw(10, 80);
		break;
	}
	if(gameMap.GetHero().haveShield)
		inter[5].Draw(100, 10);
	
	for(int i = 0; i < gameMap.GetHero().haveSsanghwa; i++)
	{
		inter[4].Draw(135 + (i * 40), 90);
	}

	char levels[128];
	wsprintf(levels, "등급 : %d, 경험치 : %d", gameMap.GetHero().level, gameMap.GetHero().exp);
	m_levelShow.DrawShadow(levels, 100, 40);

	if(gameMap.bossIsRaise)
	{
		brqInter[0].Draw(360, 10);
		if(gameMap.m_enermies[gameMap.maxEnermy - 1].hp > 0)
			brqInter[1].Draw(360, 10, 
				0, 0,
				(gameMap.m_enermies[gameMap.maxEnermy - 1].hp / 200.0 * brqInter[1].GetWidth()), 
				brqInter[1].GetHeight());
	}

	if(gameMap.GetHero().GetHP() <= 0)
		gameOver.Draw(640 / 2 - gameOver.GetWidth() / 2, 480 / 2 - gameOver.GetHeight() / 2);
	else if ((-gameMap.currentX) >= gameMap.image.GetWidth() - 640 && gameMap.bossIsDead)
	{
		gameClear.Draw(640 / 2 - gameClear.GetWidth() / 2, 480 / 2 - gameClear.GetHeight() / 2);
	}
}

void CGameState::Destroy()
{
	gameMap.Destroy();
}