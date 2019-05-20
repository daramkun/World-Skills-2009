#include "Enermy.h"

CEnermy::CEnermy(CState *state) : CGameObject(state)
{
	m_enabled = true;
}

CEnermy::~CEnermy(void)
{
}
