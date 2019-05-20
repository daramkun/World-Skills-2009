#pragma once

#include "Enermy.h"
#include "BulletShooter.h"
#include "Delay.h"

enum CancerType
{
	ECT_CANCER_SINGLE = 0,
	ECT_CANCER_DOUBLE_LEFT,
	ECT_CANCER_DOUBLE_RIGHT,
};

class CCancer
	: public CEnermy
{
private:
	CBulletShooter *m_shooter;
	int m_stage;

	CDelay *m_shootDelay;
	CDelay *m_patternDelay;
	int patternNumber;

	float m_shootAngle;
	float m_shootAngle2;

	CancerType m_ct;

public:
	CCancer(CState *state, int stage, CancerType ct);
	~CCancer(void);

	void Update(float);
	void Draw(float);
};
