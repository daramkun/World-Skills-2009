#include "Ani.h"

CAni::CAni(void)
{
}

CAni::~CAni(void)
{
}

void CAni::Create(const char *basename, int start, int end, int delayCount)
{
	char temp[256];
	for(int i = start, j = 0; i < start + end; i++, j++)
	{
		wsprintf(temp, "%s%d.png", basename, i);
		m_img[j].Create(temp);
	}
	imgLength = end - start;
	delay.Set(delayCount);
}

void CAni::Destroy()
{
	for(int i = 0; i < imgLength; i++)
		m_img[i].Destroy();
}

int CAni::GetWidth()
{
	return m_img[currentFrame].GetWidth();
}

int CAni::GetHeight()
{
	return m_img[currentFrame].GetHeight();
}

bool CAni::Update()
{
	if(delay.Check())
	{
		currentFrame++;
		if(currentFrame > imgLength)
		{
			currentFrame = 0;
			delay.Reset();
			return false;
		}

		delay.Reset();
	}

	return true;
}

void CAni::Draw(int x, int y)
{
	m_img[currentFrame].Draw(x, y);
}