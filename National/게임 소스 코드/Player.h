#pragma once

#include "GameObject.h"
#include "Anime.h"
#include "Sound.h"

// ĳ���� Ÿ��
enum PlayerType
{
	EPT_NANO_MOUSE,		// ���� ���콺
	EPT_NANO_LAVA,		// ���� ���
	EPT_NANO_FIGHTER,	// ���� ������
};

// ĳ���� �ִϸ��̼�
enum AnimeState
{
	// �������� Ʋ��
	EAS_ANIME_LEFT = 0,
	// �⺻
	EAS_ANIME_NORMAL = 1,
	// ���������� Ʋ��
	EAS_ANIME_RIGHT = 2,
};

#include "BulletShooter.h"
#include "Delay.h"

// �÷��̾� �浹 ������
#define PLAYER_R 5

class CPlayer
	: public CGameObject
{
	friend class CStage;
	friend class CGameState;
private:
	CAnime *m_anime[3];
	CSprite *m_sangpan;
	CSprite *m_shieldSpr;
	AnimeState m_animeState;

	PlayerType m_myType;

	// �÷��̾� �Ѿ� ����
	CBulletShooter *m_shooter;

	CDelay *m_shootDelay;

	float m_Hp, m_maxHp;
	float m_Pg;

	bool m_isGameOver;

	int m_wt;

	bool m_shield;

	CSound *m_shoot;
	CSound *m_laser;
	CSound *m_bomber;

public:
	CPlayer(CState *state, PlayerType pt);
	~CPlayer(void);

	void Update(float);
	void Draw(float);

	float GetHp() { return m_Hp; }
	void SetHp(float hp) { m_Hp = hp; }
	float GetPg() { return m_Pg; }
	void SetPg(float pg) { m_Pg = pg; }
	float GetMaxHp() { return m_maxHp; }

	bool IsGameOver() { return m_isGameOver; }

	CSprite* GetSangpan() { return m_sangpan; }

	int GetWeaponType() { return m_wt; }
	void SetWeaponType(int _wt) { m_wt = _wt; }

	bool GetShield() { return m_shield; }
	void SetShield(bool s) { m_shield = s; }
};
