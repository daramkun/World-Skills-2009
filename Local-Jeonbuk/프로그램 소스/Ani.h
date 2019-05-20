#pragma once

#include "Img.h"
#include "Delay.h"

#include "Fnt.h"

class CAni
{
private:
	CImg m_img[10];
	int imgLength;
	CDelay delay;

public:
	int currentFrame;

public:
	CAni(void);
	~CAni(void);

	void Create(const char *basename, int start, int end, int delayCount = 300);
	void Destroy();

	int GetWidth();
	int GetHeight();

	bool Update();
	void Draw(int x, int y);
};
