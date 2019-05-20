#pragma once

#include "State.h"
#include "Texture.h"

class CMenuState :
	public CState
{
private:
	CTexture m_bg;
	CTexture m_cursor;

	int cursor;

public:
	CMenuState(void);
	~CMenuState(void);

	void Initial();
	void Update(double et);
	void Draw();
	void Destroy();
};
