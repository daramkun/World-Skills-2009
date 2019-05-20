#pragma once

#include "GameObject.h"

#include "Anime.h"

class CRedBlood
	: public CGameObject
{
	friend class CBulletShooter;
private:
	CAnime *m_anime;

public:
	CRedBlood(CState *state);
	~CRedBlood(void);

	void Update(float);
	void Draw(float);
};
