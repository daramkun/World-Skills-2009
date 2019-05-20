#pragma once

#include "Anime.h"
#include "GameObject.h"
#include "Player.h"

enum EnermyType
{
	EET_BACTERIA = 0,
	EET_VIRUS,
	EET_CANCER,
};

class CEnermy
	: public CGameObject
{
	friend class CStage;
private:
	float m_hp;
	bool m_enabled;

protected:
	CAnime *m_anime;
	float r;
	EnermyType m_et;

public:
	CEnermy(CState *state);
	~CEnermy(void);

	void SetHp(float _hp) { m_hp = _hp; }
	float GetHp() { return m_hp; }

	void SetR(float _r) { r = _r; }
	float GetR() { return r; }

	bool GetEnabled() { return m_enabled; }
	void SetEnabled(bool _e) { m_enabled = _e; }

	EnermyType GetType() { return m_et; }

	virtual bool CrashPlayer(CPlayer *player) { return false; }
};
