#pragma once

#include "Img.h"

class CArrow
{
public:
	int baseX;
	int x, y;

	bool isShow;

	CImg m_img;

public:
	CArrow(void);
	~CArrow(void);

	void Create(int x, int y);
	void Update(double dt);
	void Draw();
	void Destroy();
};
