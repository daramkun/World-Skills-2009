#include "Bacteria.h"
#include "GameState.h"

CBacteria::CBacteria(CState *state, float x, float y, BacteriaType bt) : CEnermy(state)
{
	switch(bt)
	{
	case EBT_BACTERIA_VERTICAL:
		m_anime = new CAnime(Graphics(), L"..\\Content\\Monster\\Bacteria1\\", 1, 3, 100);
		SetHp(2);
		break;
	case EBT_BACTERIA_DIAGONAL_LEFT:
	case EBT_BACTERIA_DIAGONAL_RIGHT:
		m_anime = new CAnime(Graphics(), L"..\\Content\\Monster\\Bacteria2\\", 1, 1, 100);
		SetHp(1);
		break;
	case EBT_BACTERIA_ZIGZAG:
		m_anime = new CAnime(Graphics(), L"..\\Content\\Monster\\Bacteria3\\", 1, 3, 100);
		SetHp(2);
		break;
	}
	baseX = x;
	SetX(x); SetY(y);
	SetR(m_anime->Current()->GetHeight() / 2.0f);
	m_bt = bt;
	m_et = EET_BACTERIA;

	m_rotateAngle = 0;
}

CBacteria::~CBacteria(void)
{
	delete m_anime;
}

void CBacteria::Update(float dt)
{
	if(!GetEnabled()) return;
	SetY(GetY() + dt * 2);
	
	if(m_bt == EBT_BACTERIA_DIAGONAL_LEFT)
		SetX(GetX() - dt * 2.6f);
	if(m_bt == EBT_BACTERIA_DIAGONAL_RIGHT)
		SetX(GetX() + dt * 2.6f);
	
	if(m_bt == EBT_BACTERIA_ZIGZAG)
	{
		if(!leftMode)
			if(baseX - GetX() < -50)
				leftMode = true;
			else
				SetX(GetX() + dt * 5);
		else
			if(baseX - GetX() > 50)
				leftMode = false;
			else
				SetX(GetX() - dt * 5);
	}

	m_rotateAngle += dt / 2;

	m_anime->Update(dt);
}

void CBacteria::Draw(float dt)
{
	if(!GetEnabled()) return;
	CSprite *img = m_anime->Current();
	Graphics()->Draw(img, GetX() - img->GetWidth() / 2, 
		GetY() - img->GetHeight() / 2 - ((CGameState*)State())->m_stage->GetY(),
		(float)img->GetWidth(), (float)img->GetHeight(), 
		(m_bt == EBT_BACTERIA_DIAGONAL_LEFT || m_bt == EBT_BACTERIA_DIAGONAL_RIGHT) 
			? m_rotateAngle : 0.0f);
}

bool CBacteria::CrashPlayer(CPlayer *player)
{
	if(!GetEnabled()) return false;
	if(CrashCheck(GetX(), GetY() - ((CGameState*)State())->m_stage->GetY(), GetR(), 
		player->GetX(), player->GetY(), PLAYER_R))
		return true;
	else
		return false;
}