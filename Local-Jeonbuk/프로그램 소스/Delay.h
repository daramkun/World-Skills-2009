#pragma once

#include <windows.h>

class CDelay
{
	DWORD lastTick;
	int delay;
public:
	CDelay(void);
	~CDelay(void);

	void Set(int delay) { this->delay = delay; Reset(); }
	void Reset() { lastTick = GetTickCount(); }

	bool Check() { if((int)(GetTickCount() - lastTick) >= delay) return true; else return false; }
};
