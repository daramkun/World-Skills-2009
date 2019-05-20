#pragma once

#include "Enermy.h"
#include "BulletShooter.h"

#include "Delay.h"

enum VirusType
{
	EVT_VIRUS_NORMAL = 0,
	EVT_VIRUS_CIRCLE,
};

class CVirus
	: public CEnermy
{
	friend class CPlayer;
	friend class CBulletShooter;
private:
	CBulletShooter *m_shooter;
	CDelay *m_delay;

	VirusType m_vt;

public:
	CVirus(CState *state, float x, float y, VirusType vt);
	~CVirus(void);
	
	void Update(float dt);
	void Draw(float dt);
};