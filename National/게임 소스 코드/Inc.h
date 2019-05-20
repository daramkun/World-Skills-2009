#pragma once

#include <cmath>

#define ENERMY_COUNT 100
#define BULLET_COUNT 1200
#define BLOOD_COUNT 20

inline bool CrashCheck(float x1, float y1, float r1, float x2, float y2, float r2)
{
	float x = (x2 - x1);
	x = (x < 0) ? -x : x;
	float y = abs(y2 - y1);
	y = (y < 0) ? -y : y;
	float i = sqrt(x * x + y * y);
	if(r1 + r2 >= i)
		return true;
	else
		return false;
}

inline float GetMyShipAngle(float x, float y, float x1, float y1)
{
	return atan2f(y1 - y, x1 - y) / 3.141592f;
}

struct Ranking
{
	char initial[3];
	int point;
};