#include "StateManager.h"
#include "Input.h"

CStateManager g_stateManager;

CStateManager::CStateManager(void)
{
}

CStateManager::~CStateManager(void)
{
	Destroy();
}

bool CStateManager::Create()
{
	if(!m_fadeImage.Create(D3DCOLOR_XRGB(0, 0, 0))) return false;
	if(!m_help.Create("MS Gothic", 12)) return false;
	m_fadeIn = false;
	m_fadeOut = true;
	m_fadeAlpha = 255;
	currentState = -1;

	return true;
}

void CStateManager::Destroy()
{
	m_help.Destroy();
	m_fadeImage.Destroy();
}

void CStateManager::SetIndex(int index, CState *state)
{
	m_states[index] = state;
}

void CStateManager::SetState(int index, double dt)
{
	if(!m_fadeIn && !m_fadeOut)
	{
		if(currentState == index) return;
		m_fadeOut = true;
	}
	else if(m_fadeOut)
	{
		m_fadeAlpha += 5 * dt;
		if(m_fadeAlpha >= 255)
		{
			m_fadeAlpha = 255;
			m_fadeOut = false;
			m_fadeIn = true;
			if(currentState != -1)
				m_states[index]->Destroy();
			currentState = index;
			m_states[index]->Initial();
		}
	}
	else if(m_fadeIn)
	{
		m_fadeAlpha -= 5 * dt;
		if(m_fadeAlpha <= 0)
		{
			m_fadeAlpha = 0;
			m_fadeIn = false;
		}
	}
}

void CStateManager::Update(double dt)
{
	g_Input.Update();
	if(currentState != -1) m_states[currentState]->Update(dt);
}

void CStateManager::Draw()
{
	g_Graphics.Clear(0xff000000);
	g_Graphics.Begin();
	if(currentState != -1) m_states[currentState]->Draw();
	if(m_fadeIn || m_fadeOut)
		m_fadeImage.Draw(0, 0, D3DCOLOR_ARGB(m_fadeAlpha, 255, 255, 255));
	m_help.DrawShadow("ΐΣΐόΉ«Επ v1.0", 530, 460);
	g_Graphics.End();
	g_Graphics.Rendering();
}