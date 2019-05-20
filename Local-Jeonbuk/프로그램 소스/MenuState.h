#pragma once

#include "State.h"
#include "Img.h"

class CMenuState
	: public CState
{
private:
	CImg bg;
	CImg cursor;

	int currentCursor;

public:
	CMenuState(void);
	~CMenuState(void);

	void Initial();
	void Update(double dt);
	void Draw();
	void Destroy();
};
