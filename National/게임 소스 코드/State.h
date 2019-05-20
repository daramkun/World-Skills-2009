#pragma once

#include "Game.h"

class CState
{
private:
	CGame *m_Game;

public:
	CState(CGame *game);
	~CState(void);

	virtual void Initial() { }
	virtual void Update(float dt) { }
	virtual void Draw(float dt) { }
	virtual void Destroy() { }

	CGame* Game() { return m_Game; }
	CGraphics* Graphics() { return m_Game->Graphics(); }
};
