#pragma once

#include "State.h"
#include "ImageFont.h"

#include "Player.h"
#include "Stage.h"
#include "WhiteBlood.h"
#include "RedBlood.h"

#include "Bacteria.h"

#include "Inc.h"

#include "Effect.h"
#include "Sound.h"

class CGameState :
	public CState
{
	friend class CPlayer;
	friend class CStage;
	friend class CBulletShooter;
	friend class CEnermy; friend class CBacteria; friend class CVirus; friend class CCancer;
	friend class CResultState;
	friend class CMenuState;
private:
	CStage *m_stage; CPlayer *m_player;

	int stageNumber;
	CSprite *m_interBack; CSprite *m_hpBar; CSprite *m_pgBar;

	CEnermy *m_vtEnermy[ENERMY_COUNT];

	CWhiteBlood *m_whiteBlood[BLOOD_COUNT]; 
	CRedBlood *m_redBlood[BLOOD_COUNT];

	CSprite *m_alphaBack;

	CSprite *m_gameOver; CSprite *m_clear;
	CDelay *m_gameOverDelay; CDelay *m_clearDelay;

	int m_Score; 
	int m_JeokHit, m_Bac1Hit, m_Bac2Hit, m_Bac3Hit, m_Virus1Hit, m_Virus2Hit;
	CImageFont *m_scorePrint;

	CSprite* m_itemSpr[4];
	ItemType m_takeItem;

	CEffect *m_effect[50];

	PlayerType m_selectedType;

	CSound *m_play;
	CSound *m_clearSound;
	CSound *m_gameOverSound;

	CSprite* m_weaponIcon[5];

public:
	CGameState(CGame*);
	~CGameState(void);

	void Initial();
	void Update(float);
	void Draw(float);
	void Destroy();
};
