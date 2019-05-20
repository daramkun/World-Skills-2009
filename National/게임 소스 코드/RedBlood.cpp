#include "RedBlood.h"

CRedBlood::CRedBlood(CState *state) : CGameObject(state)
{
	m_anime = new CAnime(Graphics(), L"..//Content//Npc//Blood//", 1, 6, 100);
	m_anime->Play(true);

	SetX((float)(50 + rand() % 420)); SetY(-100.0f);
}

CRedBlood::~CRedBlood(void)
{
	delete m_anime;
}

void CRedBlood::Update(float dt)
{
	SetY(GetY() + dt * 15);
	m_anime->Update(dt);
}

void CRedBlood::Draw(float dt)
{
	CSprite* spr = m_anime->Current();
	Graphics()->Draw(spr, GetX() - spr->GetWidth() / 2, GetY() - spr->GetHeight() / 2);
}