#include "Delay.h"

CDelay::CDelay(int delay)
{
	m_delay = delay;
	Reset();
}

void CDelay::Update(float dt)
{
	// ���ݱ����� �ð��� ����
	m_elaps += dt * 100.0f;
}

void CDelay::Reset()
{
	m_elaps = 0;
}

bool CDelay::Check()
{
	// ������ �ð��� ������ ������ �ð��� ������
	if(m_elaps >= m_delay)
		return true;
	else
		return false;
}