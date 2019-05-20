#include "Player.h"
#include "Virus.h"
#include "Bacteria.h"
#include "Game.h"
#include "GameState.h"

CPlayer::CPlayer(CState *state, PlayerType pt) : CGameObject(state)
{
	switch(pt)
	{
		// 나노 마우스 이미지 로드
	case EPT_NANO_MOUSE:
		m_anime[0] = new CAnime(Graphics(), L"..\\Content\\Hero\\Mouse\\1", 1, 3, 150);
		m_anime[1] = new CAnime(Graphics(), L"..\\Content\\Hero\\Mouse\\", 1, 3, 150);
		m_anime[2] = new CAnime(Graphics(), L"..\\Content\\Hero\\Mouse\\2", 1, 3, 150);
		m_sangpan = new CSprite(Graphics(), L"..\\Content\\Interface\\Nano\\Mouse.png");
		m_maxHp = 100;
		break;
		// 나노 라바 이미지 로드
	case EPT_NANO_LAVA:
		m_anime[1] = new CAnime(Graphics(), L"..\\Content\\Hero\\Lava\\", 1, 4, 150);
		m_sangpan = new CSprite(Graphics(), L"..\\Content\\Interface\\Nano\\Lava.png");
		m_maxHp = 120;
		break;
		// 나노 파이터 이미지 로드
	case EPT_NANO_FIGHTER:
		m_anime[1] = new CAnime(Graphics(), L"..\\Content\\Hero\\Fighter\\", 1, 3, 150);
		m_sangpan = new CSprite(Graphics(), L"..\\Content\\Interface\\Nano\\Fighter.png");
		m_maxHp = 140;
		break;
	}

	m_shieldSpr = new CSprite(Graphics(), L"..\\Content\\Etc\\Shield.png");

	m_myType = pt;

	m_Hp = m_maxHp;
	m_Pg = 10;

	m_animeState = EAS_ANIME_NORMAL;

	m_shooter = new CBulletShooter(State(), EBT_PLAYER_DEFAULT, GetX(), GetY());
	m_shootDelay = new CDelay(200);

	m_isGameOver = false;

	m_wt = 0;

	m_shield = false;

	m_shoot = new CSound(L"..\\Content\\Sound\\tan.wav");
	m_laser = new CSound(L"..\\Content\\Sound\\laser.wav");
}

CPlayer::~CPlayer(void)
{
	m_laser->Stop();
	delete m_laser;
	m_shoot->Stop();
	delete m_shoot;
	delete m_shieldSpr;
	delete m_shootDelay;
	delete m_shooter;
	delete m_anime[1];
	delete m_sangpan;
}

void CPlayer::Update(float dt)
{
	//m_shoot->Update();
	//m_laser->Update();

	// 게임 오버가 아닐 경우
	if(!m_isGameOver)
	{
		bool isImageChange = false;

		// 왼쪽 이동
		if(Game()->KeyPress(VK_LEFT))
		{
			if(GetX() <= 0) SetX(0); else SetX(GetX() - dt * 14);
			m_shooter->SetX(GetX());
			if(m_myType == EPT_NANO_MOUSE)
			{
				m_animeState = EAS_ANIME_LEFT;
				isImageChange = true;
			}
		}

		// 오른쪽 이동
		if(Game()->KeyPress(VK_RIGHT))
		{
			if(GetX() >= 520) SetX(520); else SetX(GetX() + dt * 14);
			m_shooter->SetX(GetX());
			if(m_myType == EPT_NANO_MOUSE)
			{
				m_animeState = EAS_ANIME_RIGHT;
				isImageChange = true;
			}
		}

		// 위쪽 이동
		if(Game()->KeyPress(VK_UP))
		{
			if(GetY() <= 0) SetY(0); else SetY(GetY() - dt * 14);
			m_shooter->SetY(GetY());
		}

		// 아래쪽 이동
		if(Game()->KeyPress(VK_DOWN))
		{
			if(GetY() >= 600) SetY(600); else SetY(GetY() + dt * 14);
			m_shooter->SetY(GetY());
		}

		m_shootDelay->Update(dt);
		// 공격
		if(Game()->KeyPress(VK_SPACE))
		{
			if(m_shootDelay->Check())
			{
				switch(m_wt)
				{
				case 0:
					m_shooter->ChangeBulletType(EBT_PLAYER_DEFAULT);
					m_shooter->AddBullet(-0.5f, 3.2f);
					break;
				case 1:
					m_shooter->ChangeBulletType(EBT_PLAYER_DEFAULT);
					m_shooter->SetX(m_shooter->GetX() - 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->SetX(m_shooter->GetX() + 20); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->SetX(m_shooter->GetX() - 10);
					break;
				case 2:
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE1);
					m_shooter->SetX(m_shooter->GetX() - 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->SetX(m_shooter->GetX() + 20); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->SetX(m_shooter->GetX() - 10);
					break;
				case 3:
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE1);
					m_shooter->SetX(m_shooter->GetX() - 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->ChangeBulletType(EBT_PLAYER_DEFAULT);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE1);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->SetX(m_shooter->GetX() - 10);
					break;
				case 4:
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE2);
					m_shooter->SetX(m_shooter->GetX() - 20); m_shooter->AddBullet(-0.75f, 3.2f);
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE1);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->ChangeBulletType(EBT_PLAYER_DEFAULT);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE1);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 3.2f);
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE2);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.25f, 3.2f);
					m_shooter->SetX(m_shooter->GetX() - 20);
					break;
				}
				m_shoot->Play(false);
				m_shootDelay->Reset();
			}
		}

		// 아이템 사용
		if(Game()->KeyPress(VK_CONTROL))
		{
			ItemType it = ((CGameState*)State())->m_takeItem;
			CEnermy** enermy = ((CGameState*)State())->m_vtEnermy;

			switch(it)
			{
			case EIT_KILLING_PAIN:
				SetPg(10);
				break;
			case EIT_WRENCH:
				SetHp(m_maxHp);
				break;
			case EIT_BOMBER:
				SetHp(GetHp() - 20);
				for(int i = 0; i < ENERMY_COUNT; i++)
				{
					if(enermy[i] != NULL && enermy[i]->GetEnabled())
					{
						if(enermy[i]->GetType() == EET_CANCER) continue;
						if(enermy[i]->GetY() - ((CGameState*)State())->m_stage->GetY() > 0)
						{
							if(enermy[i]->GetType() == EET_BACTERIA)
							{
								if(((CBacteria*)enermy[i])->m_bt == EBT_BACTERIA_VERTICAL)
								{
									((CGameState*)State())->m_Bac1Hit++;
									((CGameState*)State())->m_Score += 20;
								}
								if(((CBacteria*)enermy[i])->m_bt == EBT_BACTERIA_DIAGONAL_RIGHT
									|| ((CBacteria*)enermy[i])->m_bt == EBT_BACTERIA_DIAGONAL_LEFT)
								{
									((CGameState*)State())->m_Bac2Hit++;
									((CGameState*)State())->m_Score += 30;
								}
								if(((CBacteria*)enermy[i])->m_bt == EBT_BACTERIA_ZIGZAG)
								{
									((CGameState*)State())->m_Bac3Hit++;
									((CGameState*)State())->m_Score += 40;
								}
							}
							else
							{
								if(((CVirus*)enermy[i])->m_vt == EVT_VIRUS_NORMAL)
								{
									((CGameState*)State())->m_Virus1Hit++;
									((CGameState*)State())->m_Score += 30;
								}
								if(((CVirus*)enermy[i])->m_vt == EVT_VIRUS_CIRCLE)
								{
									((CGameState*)State())->m_Virus2Hit++;
									((CGameState*)State())->m_Score += 40;
								}
							}
							enermy[i]->SetEnabled(false);
						}
					}
				}
				Graphics()->EarthQuake();
				break;
			case EIT_LASER:
				{
					SetPg(GetPg() + 10);
					m_shooter->ChangeBulletType(EBT_PLAYER_UPGRADE2);
					m_shooter->SetX(m_shooter->GetX() - 40); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() + 10); m_shooter->AddBullet(-0.5f, 4.2f);
					m_shooter->SetX(m_shooter->GetX() - 40);
					m_laser->Play(false);
				}
				break;
			}

			((CGameState*)State())->m_takeItem = EIT_NONE;
		}

		if(!isImageChange)
			m_animeState = EAS_ANIME_NORMAL;
	}

	m_shooter->Update(dt);
	m_shooter->CheckCrashEnermy(((CGameState*)State())->m_vtEnermy);
	m_shooter->CheckCrashRedBlood(this, ((CGameState*)State())->m_redBlood);
	m_shooter->CheckCrashWhiteBlood(((CGameState*)State())->m_whiteBlood);

	if(GetHp() <= 0)
		if(!m_isGameOver)
			if(Graphics()->EarthQuake())
				m_isGameOver = true;
	if(GetPg() >= 100)
		if(!m_isGameOver)
			if(Graphics()->EarthQuake())
				m_isGameOver = true;
	m_anime[m_animeState]->Update(dt);
}

void CPlayer::Draw(float dt)
{
	CSprite* img = m_anime[m_animeState]->Current();
	m_shooter->Draw(dt);
	Graphics()->Draw(img, GetX() - img->GetWidth() / 2, GetY() - img->GetHeight() / 2);
	if(m_shield)
		Graphics()->Draw(m_shieldSpr, 
		GetX() - m_shieldSpr->GetWidth() / 2, GetY() - m_shieldSpr->GetHeight() / 2,
		75, 75, 0.0f, 0xa0ffffff);
}