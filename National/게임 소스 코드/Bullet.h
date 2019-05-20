#pragma once

#include "GameObject.h"

#include "Inc.h"

enum BulletType
{
	EBT_PLAYER_DEFAULT = 0,
	EBT_PLAYER_UPGRADE1 = 1,
	EBT_PLAYER_UPGRADE2 = 2,
	EBT_ENERMY_VIRUS = 3,
	EBT_ENERMY_VIRUS2 = 4,
	EBT_ENERMY_CANCER = 5,
	EBT_ENERMY_CANCER2 = 6
};

class CBullet
	: public CGameObject
{
	friend class CBulletShooter;
private:
	static CSprite *m_bullet[7];
	BulletType m_index;
	float m_angle, m_speed;
	bool enabled;

public:
	static void InitBullet(CGraphics* g);
	static void DestBullet();

	CBullet(CState *state, BulletType type, float x, float y, float _angle, float _speed);
	~CBullet(void);

	void Update(float);
	void Draw(float);

	void SetEnabled(bool _enabled) { enabled = _enabled; }
	bool GetEnabled() { return enabled; }

	void SetAngle(float _angle) { m_angle = _angle; }
	void SetSpeed(float _speed) { m_speed = _speed; }

	bool CrashCheck(float x, float y, float r);

	int GetIndex() { return m_index; }
};
