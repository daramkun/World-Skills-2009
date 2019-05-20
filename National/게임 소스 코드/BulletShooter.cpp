#include "BulletShooter.h"
#include "Player.h"
#include "Bacteria.h"
#include "Virus.h"
#include "GameState.h"

CBulletShooter::CBulletShooter(CState *state, BulletType _bt, float x, float y) : CGameObject(state)
{
	for(int i = 0; i < BULLET_COUNT; i++) m_vtBullet[i] = NULL;
	SetX(x); SetY(y);
	bt = _bt;
}

CBulletShooter::~CBulletShooter(void)
{
	for(int i = 0; i < BULLET_COUNT; i++)
	{
		if(m_vtBullet[i] != NULL)
			delete m_vtBullet[i];
	}
}

void CBulletShooter::Update(float dt)
{
	for(int i = 0; i < BULLET_COUNT; i++)
	{
		if(m_vtBullet[i] != NULL)
		{
			if(m_vtBullet[i]->GetEnabled())
			{
				m_vtBullet[i]->Update(dt);
				if(m_vtBullet[i]->GetY() > 610 || m_vtBullet[i]->GetY() < -10)
					m_vtBullet[i]->SetEnabled(false);
				if(m_vtBullet[i]->GetX() > 530 || m_vtBullet[i]->GetX() < -10)
					m_vtBullet[i]->SetEnabled(false);
			}
		}
	}
}

void CBulletShooter::Draw(float dt)
{
	for(int i = 0; i < BULLET_COUNT; i++)
	{
		if(m_vtBullet[i] != NULL)
			if(m_vtBullet[i]->GetEnabled())
				m_vtBullet[i]->Draw(dt);
	}
}

void CBulletShooter::AddBullet(float angle, float speed)
{
	for(int i = 0; i < BULLET_COUNT; i++)
	{
		if(m_vtBullet[i] != NULL)
		{
			if(!m_vtBullet[i]->GetEnabled())
			{
				m_vtBullet[i]->SetEnabled(true);
				m_vtBullet[i]->SetX(GetX());
				m_vtBullet[i]->SetY(GetY());
				m_vtBullet[i]->SetAngle(angle);
				m_vtBullet[i]->SetSpeed(speed);
				m_vtBullet[i]->m_index = bt;
				break;
			}
		}
		else
		{
			m_vtBullet[i] = new CBullet(State(), bt, GetX(), GetY(), angle, speed);
			break;
		}
	}
}

// 플레이어와 총알 충돌
void CBulletShooter::CheckCrashPlayer(CPlayer *player)
{
	if(((CGameState*)State())->m_clearDelay) return;

	for(int i = 0; i < BULLET_COUNT; i++)
	{
		if(m_vtBullet[i] != NULL)
		{
			if(m_vtBullet[i]->GetEnabled())
			{
				if(m_vtBullet[i]->CrashCheck(player->GetX(), player->GetY(), PLAYER_R))
				{
					m_vtBullet[i]->SetEnabled(false);
					if(!player->GetShield())
					{
						player->SetHp(player->GetHp() - 30);
						if(player->GetHp() > 0)
							Graphics()->WeakQuake();
					}
					else
					{
						player->SetShield(false);
					}
				}
			}
		}
	}
}

// 적과 총알 충돌
void CBulletShooter::CheckCrashEnermy(CEnermy* enermy[ENERMY_COUNT])
{
	for(int i = 0; i < ENERMY_COUNT; i++)
	{
		if(enermy[i] != NULL && enermy[i]->GetEnabled())
		{
			for(int j = 0; j < BULLET_COUNT; j++)
			{
				if(m_vtBullet[j] != NULL && m_vtBullet[j]->GetEnabled())
				{
					if(m_vtBullet[j]->CrashCheck(enermy[i]->GetX(), 
						enermy[i]->GetY() - ((CGameState*)State())->m_stage->GetY(), enermy[i]->GetR()))
					{
						m_vtBullet[j]->SetEnabled(false);
						enermy[i]->SetHp(enermy[i]->GetHp() - (m_vtBullet[j]->GetIndex() + 1));
						if(enermy[i]->GetHp() <= 0)
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
							if(enermy[i]->GetType() == EET_VIRUS)
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
							if(enermy[i]->GetType() == EET_CANCER)
							{
								((CGameState*)State())->m_Score += 500;
								Graphics()->EarthQuake();
							}
							enermy[i]->SetEnabled(false);
						}
						break;
					}
				}
			}
		}
	}
}

// 적혈구와 총알 충돌
void CBulletShooter::CheckCrashRedBlood(CPlayer *player, CRedBlood* m_red[BLOOD_COUNT])
{
	for(int i = 0; i < BLOOD_COUNT; i++)
	{
		if(m_red[i] != NULL)
		{
			for(int j = 0; j < BULLET_COUNT; j++)
			{
				if(m_vtBullet[j] != NULL && m_vtBullet[j]->GetEnabled())
				{
					if(m_vtBullet[j]->CrashCheck(m_red[i]->GetX(), m_red[i]->GetY(), 30))
					{
						player->SetPg(player->GetPg() + 10);
						m_vtBullet[j]->SetEnabled(false);
						((CGameState*)State())->m_JeokHit++;
						((CGameState*)State())->m_Score -= 10;
						delete m_red[i]; m_red[i] = NULL;
						Graphics()->WeakQuake();
						break;
					}
				}
			}
		}
	}
}

// 백혈구와 총알 충돌
void CBulletShooter::CheckCrashWhiteBlood(CWhiteBlood *m_white[BLOOD_COUNT])
{
	for(int i = 0; i < BLOOD_COUNT; i++)
	{
		if(m_white[i] != NULL && !m_white[i]->IsItemMode())
		{
			for(int j = 0; j < BULLET_COUNT; j++)
			{
				if(m_vtBullet[j] != NULL && m_vtBullet[j]->GetEnabled())
				{
					if(m_vtBullet[j]->CrashCheck(m_white[i]->GetX(), m_white[i]->GetY(), 30))
					{
						m_vtBullet[j]->SetEnabled(false);
						m_white[i]->SetItemMode();
						break;
					}
				}
			}
		}
	}
}