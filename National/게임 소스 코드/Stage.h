#pragma once

#include "Anime.h"
#include "GameObject.h"

class CStage
	: public CGameObject
{
	friend class CGameState;
private:
	CAnime *m_map;
	CDelay *m_bloodDelay;
	CSprite *m_stageNumber;

	bool m_moveEnable;

public:
	CStage(CState *state, int stageNum);
	~CStage(void);

	void Update(float dt);
	void Draw(float dt);
};
