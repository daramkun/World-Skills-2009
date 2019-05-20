#include "Effect.h"

CEffect::CEffect(CState *state) : CGameObject(state)
{
	m_anime = new CAnime(Graphics(), L"..\\Content\\Effect\\E_", 1, 7, 50);
	m_visible = false;
}

CEffect::~CEffect(void)
{
}

void CEffect::Play()
{
	m_anime->Play(false);
}

void CEffect::Update(float dt)
{
	if(m_anime->Update(dt))
		m_visible = false;
}

void CEffect::Draw(float dt)
{
	if(m_visible)
		Graphics()->Draw(m_anime->Current(), GetX() - 35, GetY()- 35);
}