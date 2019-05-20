#pragma once

#include "State.h"
#include "Texture.h"

class CStateManage
{
	CState *m_state[4];
	CTexture m_fade;
	int nowState;

	bool m_fadeIn, m_fadeOut;
	int m_fadeAlpha;

public:
	CStateManage(void);
	~CStateManage(void);

	void Create(CGraphics& g);
	void SetStateClass(int index, CState* state);

	void SetState(int index, double et);

	void Update(double et);
	void Draw(CGraphics &g);
};
