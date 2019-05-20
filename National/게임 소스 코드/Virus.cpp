#include "Virus.h"
#include "GameState.h"

CVirus::CVirus(CState *state, float x, float y, VirusType vt) : CEnermy(state)
{
	if(vt == EVT_VIRUS_NORMAL)
	{
		m_anime = new CAnime(Graphics(), L"..\\Content\\Monster\\Virus1\\", 1, 1, 100);
		SetHp(2);
	}
	else
	{
		m_anime = new CAnime(Graphics(), L"..\\Content\\Monster\\Virus2\\", 1, 3, 100);	
		SetHp(3);
	}
	SetX(x); SetY(y); SetR(m_anime->Current()->GetHeight() / 2.0f);
	m_shooter = new CBulletShooter(State(), EBT_ENERMY_VIRUS, GetX(), GetY());
	m_delay = new CDelay(1000);

	m_vt = vt;
	m_et = EET_VIRUS;
}

CVirus::~CVirus(void)
{
	delete m_delay;
	delete m_shooter;
}

void CVirus::Update(float dt)
{
	if(GetEnabled())
	{
		SetY(GetY() + dt * 2);
		m_anime->Update(dt);

		m_shooter->SetX(GetX());
		m_shooter->SetY(GetY() - ((CGameState*)State())->m_stage->GetY());
	}

	m_shooter->Update(dt);

	if(GetEnabled())
	{
		m_delay->Update(dt);
		if(m_delay->Check())
		{
			if(m_vt == EVT_VIRUS_NORMAL)
			{
				m_shooter->AddBullet(0.35f, 1.5f);
				m_shooter->AddBullet(0.5f, 1.5f);
				m_shooter->AddBullet(0.65f, 1.5f);
			}
			else if(m_vt == EVT_VIRUS_CIRCLE)
			{
				for(int i = 0; i < 16; i++)
				{
					m_shooter->AddBullet(i / 8.0f, 3.5f);
				}
			}
			m_delay->Reset();
		}
	}

	m_shooter->CheckCrashPlayer(((CGameState*)State())->m_player);
}

void CVirus::Draw(float dt)
{
	m_shooter->Draw(dt);
	
	if(GetEnabled())
	{
		CSprite *img = m_anime->Current();
		Graphics()->Draw(img, GetX() - (img->GetWidth() / 2), 
			GetY() - (img->GetHeight() / 2) - ((CGameState*)State())->m_stage->GetY());
	}
}