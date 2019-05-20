#include "Lib.h"

#include <windows.h>
#pragma comment (lib, "winmm.lib")

bool CLib::Crash(int x, int y, int w, int h, int x2, int y2, int w2, int h2)
{
	if(x <= x2 + w2 && x2 <= x + w &&
		y <= y2 + h2 && y2 <= y + h)
		return true;
	else
		return false;
}

void CLib::SoundPlay(const char *sound)
{
	sndPlaySound(sound, SND_ASYNC);
}