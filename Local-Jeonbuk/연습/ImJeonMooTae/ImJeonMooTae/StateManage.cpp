#include "StateManage.h"

CStateManage::CStateManage(void)
{
	nowState = -1;
}

CStateManage::~CStateManage(void)
{
}

void CStateManage::Create(CGraphics& g)
{
	m_fade.Create(g, D3DCOLOR_XRGB(0, 0, 0));
}

void CStateManage::SetStateClass(int index, CState* state)
{
	m_state[index] = state;
}

void CStateManage::SetState(int index, double et)
{
	if(nowState == index && !m_fadeIn && !m_fadeOut) return;

	if(!m_fadeIn && !m_fadeOut)
	{
		m_fadeOut = true;
		//m_fadeAlpha = 255;
	}
	else if(m_fadeOut)
	{
		m_fadeAlpha += 5 * et;

		if(m_fadeAlpha >= 255)
		{
			if(nowState != -1)
				m_state[nowState]->Destroy();
			nowState = index;
			m_state[index]->Initial();
			m_fadeIn = true;
			m_fadeOut = false;
			m_fadeAlpha = 255;
		}
	}
	else if(m_fadeIn)
	{
		m_fadeAlpha -= 5 * et;

		if(m_fadeAlpha <= 0)
		{
			m_fadeIn = false;
			m_fadeAlpha = 0;
		}
	}
}

void CStateManage::Update(double et)
{
	if(nowState == -1) return;
	if(m_fadeOut) return;
	m_state[nowState]->Update(et);
}

void CStateManage::Draw(CGraphics &g)
{
	if(nowState != -1)
		m_state[nowState]->Draw();

	if(m_fadeIn || m_fadeOut) 
	{
		m_fade.Draw(g, 0, 0, 640, 480, D3DCOLOR_ARGB(((unsigned char)m_fadeAlpha), 255, 255, 255));
	}
}