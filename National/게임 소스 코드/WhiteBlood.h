#pragma once

#include "GameObject.h"
#include "Anime.h"

class CPlayer;

enum ItemType
{
	EIT_NONE = 0,
	EIT_WEAPON = 1,
	EIT_SHIELD = 2,
	EIT_KILLING_PAIN = 3,
	EIT_WRENCH = 4,
	EIT_BOMBER = 5,
	EIT_LASER = 6,
};

class CWhiteBlood
	: public CGameObject
{
	friend class CBulletShooter;
private:
	CAnime *m_anime;
	CSprite *m_item;
	ItemType m_it;

	bool m_itemMode;
	ItemType m_itemType;

	float m_rotateAngle;

public:
	CWhiteBlood(CState*);
	~CWhiteBlood(void);

	void Update(float);
	void Draw(float);

	bool CheckCrash(CPlayer *player);

	void SetItemMode();
	bool IsItemMode() { return m_itemMode; }
	ItemType GetItemType() { return m_itemType; }
};