#include "WhiteBlood.h"
#include "Inc.h"
#include "Player.h"

CWhiteBlood::CWhiteBlood(CState *state) : CGameObject(state)
{
	SetX((float)(10 + rand() % 500)); SetY(-50.0f);
	m_anime = new CAnime(Graphics(), L"..\\Content\\Npc\\White\\", 1, 1, 100);

	m_item = NULL;
	m_itemType = EIT_NONE;
	m_itemMode = false;

	m_rotateAngle = 0.0f;
}

CWhiteBlood::~CWhiteBlood(void)
{
	delete m_anime;
}

void CWhiteBlood::Update(float dt)
{
	SetY(GetY() + dt * 10);
	m_rotateAngle += (dt * 0.2f);
	m_anime->Update(dt);
}

void CWhiteBlood::Draw(float dt)
{
	CSprite* spr = m_anime->Current();
	if(!m_itemMode)
		Graphics()->Draw(spr, GetX() - spr->GetWidth() / 2, GetY() - spr->GetHeight() / 2, 
			100, 100, m_rotateAngle);
	else
		Graphics()->Draw(m_item, GetX() - m_item->GetWidth() / 2, GetY() - m_item->GetHeight() / 2,
			30, 30, m_rotateAngle);
}

bool CWhiteBlood::CheckCrash(CPlayer *player)
{
	if(!m_item) return false;
	float r = 0;
	if(!m_itemMode) r = m_item->GetWidth() / 2.0f;
	else r = m_anime->Current()->GetWidth() / 2.0f;

	if(::CrashCheck(GetX(), GetY(), r, player->GetX(), player->GetY(),
		PLAYER_R))
		return true;
	else
		return false;
}

void CWhiteBlood::SetItemMode()
{
	m_itemType = (ItemType)(1 + rand() % 6);

	wchar_t *file = NULL;
	switch(m_itemType)
	{
	case 1:
		file = L"..\\Content\\Item\\weapon.png";
		break;
	case 2:
		file = L"..\\Content\\Item\\s.png";
		break;
	case 3:
		file = L"..\\Content\\Item\\killingpain.png";
		break;
	case 4:
		file = L"..\\Content\\Item\\wrench.png";
		break;
	case 5:
		file = L"..\\Content\\Item\\boom.png";
		break;
	case 6:
		file = L"..\\Content\\Item\\g.png";
		break;
	}
	
	m_item = new CSprite(Graphics(), file);

	m_itemMode = true;
}