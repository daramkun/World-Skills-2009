#pragma once

#include "Inc.h"

#include "GameState.h"

#include "State.h"
#include "Sprite.h"
#include "Delay.h"
#include "Player.h"
#include "ImageFont.h"

#include "Sound.h"

enum MenuIndex
{
	EMI_START = 0,
	EMI_RANKING,
	EMI_EXIT,
};

class CMenuState :
	public CState
{
private:
	CSprite *m_back;
	CSprite *m_sel;
	CSprite *m_ranking;

	MenuIndex m_index;

	CDelay *m_inputDelay;

	bool m_isRanking;
	Ranking m_rank[3];

	bool m_isSelect;
	CSprite* m_charList;
	CSprite* m_charCursor;
	PlayerType m_lstIndex;

	CImageFont *m_rankFont;

	CSound *m_title;

public:
	CMenuState(CGame *game);
	~CMenuState(void);

	void Initial();
	void Update(float dt);
	void Draw(float dt);
	void Destroy();
};
