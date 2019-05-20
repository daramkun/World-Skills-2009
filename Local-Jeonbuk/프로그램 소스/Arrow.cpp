#include "Arrow.h"

CArrow::CArrow(void)
{
}

CArrow::~CArrow(void)
{
}

void CArrow::Create(int x, int y)
{
	m_img.Create("Content/Item/dd.png");
	baseX = this->x = x;
	this->y = y;
	isShow = true;
}

void CArrow::Update(double dt)
{
	if(!isShow) return;
	x += 10 * dt;
	if(x - 540 > baseX)
		isShow = false;
}

void CArrow::Draw()
{
	if(!isShow) return;
	m_img.Draw(x, y);
}

void CArrow::Destroy()
{
	m_img.Destroy();
}