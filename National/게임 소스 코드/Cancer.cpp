#include "Cancer.h"
#include "GameState.h"

CCancer::CCancer(CState *state, int stage, CancerType ct) : CEnermy(state)
{
	SetY(100); SetR(60);
	m_shooter = new CBulletShooter(State(), EBT_ENERMY_CANCER, GetX(), GetY());
	m_anime = new CAnime(Graphics(), L"..\\Content\\Monster\\Cancer\\", 1, 3, 100);
	m_anime->Play(true);

	m_stage = stage;

	m_patternDelay = new CDelay(10000);
	m_shootDelay = new CDelay(100);

	patternNumber = 0;
	m_shootAngle = m_shootAngle2 = 0;

	m_ct = ct;

	switch(m_ct)
	{
	case ECT_CANCER_SINGLE:
		SetX(520 / 2);
		break;
	case ECT_CANCER_DOUBLE_LEFT:
		SetX(120);
		break;
	case ECT_CANCER_DOUBLE_RIGHT:
		SetX(400);
		break;
	}

	SetHp(300);

	m_shooter->SetX(GetX());

	m_et = EET_CANCER;
}

CCancer::~CCancer(void)
{
	delete m_patternDelay;
	delete m_shootDelay;
	delete m_anime;
	delete m_shooter;
}

void CCancer::Update(float dt)
{
	m_anime->Update(dt);

	if(((CGameState*)State())->m_stage->GetY() != 0) return;

	m_shootDelay->Update(dt);
	m_patternDelay->Update(dt);

	if(m_patternDelay->Check())
	{
		patternNumber++;
		if(patternNumber >= 4)
			patternNumber = 0;
		m_patternDelay->Reset();
	}

	CPlayer *player = ((CGameState*)State())->m_player;

	if(GetEnabled())
		if(m_shootDelay->Check())
		{
			switch(m_stage)
			{
			case 1:
				{
					switch(patternNumber)
					{
					case 0:
						m_shootAngle+= dt * 1.2f;
						m_shooter->AddBullet(m_shootAngle, 2.5f);
						break;
					case 1:
						m_shootAngle+= dt * 1.2f;
						m_shooter->AddBullet(m_shootAngle, 1.5f);
						m_shooter->AddBullet(m_shootAngle + 0.5f, 1.5f);
						m_shooter->AddBullet(m_shootAngle + 1.0f, 1.5f);
						m_shooter->AddBullet(m_shootAngle + 1.5f, 1.5f);
						break;
					case 2:
						for(int i = 0; i < 5; i++)
							m_shooter->AddBullet((25 + rand() % 65) / 100.0f, (10 + rand() % 30) / 10.0f);
						m_shootAngle = m_shootAngle2 = 0;
						break;
					case 3:
						abs(m_shootAngle2 += 0.01f);
						abs(m_shootAngle = sinf(m_shootAngle2));
						m_shooter->AddBullet(m_shootAngle + 0.25f, 2.0f);
						m_shooter->AddBullet(m_shootAngle + 0.75f, 2.0f);
						break;
					}
				}
				break;
			case 2:
				{
					switch(patternNumber)
					{
					case 0:
						m_shootAngle+= dt * 1.2f;
						m_shooter->AddBullet(m_shootAngle, 2.5f);
						m_shooter->AddBullet(m_shootAngle + 1.0f, 2.5f);
						break;
					case 1:
						m_shooter->AddBullet(
							((GetMyShipAngle(GetX(), GetY(), 
								player->GetX(), player->GetY()) * 100.0f) - 25 + rand() % 50) / 100.0f,
							(10 + rand() % 30) / 10.0f);
						m_shootAngle = m_shootAngle2 = 0;
						break;
					case 2:
						m_shootAngle+= dt * 1.2f;
						m_shooter->AddBullet(m_shootAngle, 1.5f);
						m_shooter->AddBullet(m_shootAngle + 0.5f, 1.5f);
						m_shooter->AddBullet(m_shootAngle + 1.0f, 1.5f);
						m_shooter->AddBullet(m_shootAngle + 1.5f, 1.5f);
						break;
					case 3:
						abs(m_shootAngle2 += 0.01f);
						abs(m_shootAngle = sinf(m_shootAngle2));
						m_shooter->AddBullet(m_shootAngle + 0.25f, 2.0f);
						m_shooter->AddBullet(m_shootAngle + 0.75f, 2.0f);
						break;
					}
				}
				break;
			}
			m_shootDelay->Reset();
		}

		m_shooter->Update(dt);
		m_shooter->CheckCrashPlayer(((CGameState*)State())->m_player);
}

void CCancer::Draw(float dt)
{
	m_shooter->Draw(dt);
	CSprite* spr = m_anime->Current();
	if(GetHp() > 0)
		Graphics()->Draw(spr, 
			GetX() - spr->GetWidth() / 2,
			GetY() - spr->GetHeight() / 2 - ((CGameState*)State())->m_stage->GetY());
}