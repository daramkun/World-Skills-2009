#include "Delay.h"

CDelay::CDelay(int delay)
{
	m_delay = delay;
	Reset();
}

void CDelay::Update(float dt)
{
	// 지금까지의 시간을 누적
	m_elaps += dt * 100.0f;
}

void CDelay::Reset()
{
	m_elaps = 0;
}

bool CDelay::Check()
{
	// 누적된 시간이 지정된 딜레이 시간과 같은가
	if(m_elaps >= m_delay)
		return true;
	else
		return false;
}