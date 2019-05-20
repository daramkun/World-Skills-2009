#pragma once

#include <vector>
using namespace std;
#include "Bullet.h"
#include "Inc.h"

#include "RedBlood.h"
#include "WhiteBlood.h"

class CPlayer;
class CEnermy;

class CBulletShooter
	: public CGameObject
{
	CBullet *m_vtBullet[BULLET_COUNT];
	BulletType bt;

public:
	CBulletShooter(CState *state, BulletType bt, float x, float y);
	~CBulletShooter(void);

	void Update(float);
	void Draw(float);

	void ChangeBulletType(BulletType _bt) { bt = _bt; }

	void AddBullet(float angle, float speed);

	void CheckCrashPlayer(CPlayer *player);
	void CheckCrashEnermy(CEnermy* enermy[ENERMY_COUNT]);

	void CheckCrashRedBlood(CPlayer *player, CRedBlood *m_red[BLOOD_COUNT]);
	void CheckCrashWhiteBlood(CWhiteBlood *m_white[BLOOD_COUNT]);
};