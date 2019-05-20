#pragma once

#include "State.h"
#include "Game.h"

class CGameObject
{
private:
	CState *m_State;
	float x, y;

public:
	CGameObject(CState *state);
	~CGameObject(void);

	virtual void Update(float dt) { }
	virtual void Draw(float dt) { }

	void SetX(float _x) { x = _x; }
	void SetY(float _y) { y = _y; }

	float GetX() { return x; }
	float GetY() { return y; }

	CGame* Game() { return m_State->Game(); }
	CGraphics* Graphics() { return m_State->Graphics(); }
	CState* State() { return m_State; }
};
