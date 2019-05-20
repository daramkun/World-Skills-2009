#pragma once

#include "Enermy.h"
#include "Player.h"

enum BacteriaType
{
	EBT_BACTERIA_VERTICAL = 0,
	EBT_BACTERIA_DIAGONAL_RIGHT,
	EBT_BACTERIA_DIAGONAL_LEFT,
	EBT_BACTERIA_ZIGZAG,
};

class CBacteria :
	public CEnermy
{
	friend class CPlayer;
	friend class CBulletShooter;
private:
	BacteriaType m_bt;
	int value;
	bool leftMode;
	float baseX;

	float m_rotateAngle;

public:
	CBacteria(CState *state, float x, float y, BacteriaType bt);
	~CBacteria(void);

	void Update(float dt);
	void Draw(float dt);

	bool CrashPlayer(CPlayer *player);
};
