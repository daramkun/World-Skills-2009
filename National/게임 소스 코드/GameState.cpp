#include "GameState.h"
#include "Bullet.h"

CGameState::CGameState(CGame* game) : CState(game)
{
}

CGameState::~CGameState(void)
{
}

void CGameState::Initial()
{
	stageNumber = 1;

	// 인터페이스 데이터 로드
	m_interBack = new CSprite(Graphics(), L"..\\Content\\Interface\\interface.png");
	m_hpBar = new CSprite(Graphics(), L"..\\Content\\Interface\\hp.png");
	m_pgBar = new CSprite(Graphics(), L"..\\Content\\Interface\\pg.png");

	// 게임 오버 및 클리어 데이터 로드
	m_alphaBack = new CSprite(Graphics(), L"..\\Content\\Menu\\alpha.png");
	m_gameOver = new CSprite(Graphics(), L"..\\Content\\Menu\\gameover.png");
	m_clear = new CSprite(Graphics(), L"..\\Content\\Menu\\gameclear.png");

	// 아이템 인터페이스 이미지 로드
	m_itemSpr[0] = new CSprite(Graphics(), L"..\\Content\\Interface\\Item\\killingpain.png");
	m_itemSpr[1] = new CSprite(Graphics(), L"..\\Content\\Interface\\Item\\wrench.png");
	m_itemSpr[2] = new CSprite(Graphics(), L"..\\Content\\Interface\\Item\\boom.png");
	m_itemSpr[3] = new CSprite(Graphics(), L"..\\Content\\Interface\\Item\\g.png");

	// 스테이지 및 플레이어, 총알 이미지 생성
	m_player = new CPlayer(this, m_selectedType);
	m_stage = new CStage(this, stageNumber);
	CBullet::InitBullet(Graphics());

	m_scorePrint = new CImageFont(Graphics());

	m_gameOverDelay = m_clearDelay = NULL;

	m_Score = 0; m_Bac1Hit = m_Bac2Hit = m_Bac3Hit = m_Virus1Hit = m_Virus2Hit = m_JeokHit = 0;

	m_takeItem = EIT_NONE;

	m_play = new CSound(L"..\\Content\\Sound\\play.mid");
	m_play->Play(true);

	m_clearSound = new CSound(L"..\\Content\\Sound\\E_die.wav");
	m_gameOverSound = new CSound(L"..\\Content\\Sound\\die.wav");

	//for(int i = 0; i < 150; i++)
	//	m_effect[i] = new CEffect(this);

	m_weaponIcon[0] = new CSprite(Graphics(), L"..\\Content\\Interface\\Weapon\\1.png");
	m_weaponIcon[1] = new CSprite(Graphics(), L"..\\Content\\Interface\\Weapon\\2.png");
	m_weaponIcon[2] = new CSprite(Graphics(), L"..\\Content\\Interface\\Weapon\\3.png");
	m_weaponIcon[3] = new CSprite(Graphics(), L"..\\Content\\Interface\\Weapon\\4.png");
	m_weaponIcon[4] = new CSprite(Graphics(), L"..\\Content\\Interface\\Weapon\\5.png");
}

void CGameState::Update(float dt)
{
	m_stage->Update(dt);

	m_play->Update();
	m_clearSound->Update();
	m_gameOverSound->Update();
	
	// 몬스터를 모두 파괴했는지 검사
	bool isEnable = false;
	for(int i = 0; i < ENERMY_COUNT; i++)
	{
		if(m_vtEnermy[i] != NULL)
		{
			if(m_vtEnermy[i]->GetEnabled())
			{
				isEnable = true;
				break;
			}
		}
	}

	// 몬스터를 모두 파괴했다면 게임 클리어
	if(!isEnable)
	{
		if(m_clearDelay != NULL)
		{
			m_clearDelay->Update(dt);
			if(m_clearDelay->Check())
			{
				if(stageNumber == 2)
				{
					Game()->SetState(STATE_RESULT);
					return;
				}
				delete m_stage;
				m_stage = new CStage(this, ++stageNumber);
				m_player->SetPg(m_player->GetPg() + 10);
				delete m_clearDelay;
				m_clearDelay = NULL;
			}
		}
		else
		{
			m_clearDelay = new CDelay(4000);
			m_clearSound->Play(false);
		}
	}

	// 게임 오버 상태인가
	if(m_player->IsGameOver())
	{
		if(m_gameOverDelay != NULL)
		{
			m_gameOverDelay->Update(dt);
			if(m_gameOverDelay->Check())
			{
				Game()->SetState(STATE_RESULT);
				return;
			}
		}
		else
		{
			m_gameOverDelay = new CDelay(4000);
			m_gameOverSound->Play(false);
		}
	}

	//for(int i = 0; i < 150; i++)
	//	m_effect[i]->Update(dt);
}

void CGameState::Draw(float dt)
{
	m_stage->Draw(dt);
	
	//for(int i = 0; i < 150; i++)
	//	m_effect[i]->Draw(dt);

	Graphics()->DrawNoQuake(m_interBack, 0, 0, 800, 600);
	// HP 바
	Graphics()->DrawClip(m_hpBar, 594, 246, 0, 0,
		m_player->GetHp() / m_player->GetMaxHp() * 180, 36);
	// PG 바
	Graphics()->DrawClip(m_pgBar, 594, 302, 0, 0,
		m_player->GetPg() / 100.0f * 180, 36);
	CSprite*plsang = m_player->GetSangpan();
	Graphics()->DrawNoQuake(plsang, 566, 350, (float)plsang->GetWidth(), (float)plsang->GetHeight());
	Graphics()->DrawNoQuake(m_stage->m_stageNumber, 698, 22, 58, 58);
	// 스코어 표시
	m_scorePrint->Draw(559, 530, m_Score);
	// 소지 무기 표시
	Graphics()->DrawNoQuake(m_weaponIcon[m_player->m_wt], 554, 113, 96, 96);
	// 소지 아이템 표시
	if(m_takeItem != EIT_NONE)
	{
		Graphics()->DrawNoQuake(m_itemSpr[m_takeItem - 3], 674, 113, 96, 96);
	}

	// 게임 오버/클리어 공용 알파 배경 이미지 표시
	if(m_gameOverDelay || m_clearDelay)
		Graphics()->DrawNoQuake(m_alphaBack, 0, 0, 800, 600, 0xc0ffffff);

	// 게임 오버 이미지 표시
	if(m_gameOverDelay)
	{
		Graphics()->DrawNoQuake(m_gameOver, 
			400 - m_gameOver->GetWidth() / 2.0f, (float)(300 - m_gameOver->GetHeight()), 
			456, 58, 0xc0ffffff);
	}

	// 클리어 이미지 표지
	if(m_clearDelay)
	{
		Graphics()->DrawNoQuake(m_clear, 
			400 - m_clear->GetWidth() / 2.0f, (float)(300 - m_clear->GetHeight()), 
			456, 58, 0xc0ffffff);
	}
}

void CGameState::Destroy()
{
	CBullet::DestBullet();

	for(int i = 0; i < 5; i++)
		delete m_weaponIcon[i];

	m_clearSound->Stop();
	delete m_clearSound;
	m_gameOverSound->Stop();
	delete m_gameOverSound;
	m_play->Stop();
	delete m_play;
	delete m_gameOverDelay;
	delete m_alphaBack;
	delete m_gameOver; delete m_clear;
	delete m_interBack;
	delete m_hpBar; delete m_pgBar;
	delete m_player; delete m_stage;
	delete m_scorePrint;
	for(int i = 0; i < 4; i++)
		delete m_itemSpr[i];
	//for(int i = 0; i < 150; i++)
	//	delete m_effect[i];
}