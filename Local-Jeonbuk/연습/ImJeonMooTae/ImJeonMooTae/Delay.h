#pragma once

class CDelay
{
private:
	int delay;
	int lastTick;

public:
	void Set(int delay) { this->delay = delay; Reset(); }
	bool Check() { if(GetTickCount() - lastTick >= delay) return true; else return false; }
	void Reset() { lastTick = GetTickCount(); }
};