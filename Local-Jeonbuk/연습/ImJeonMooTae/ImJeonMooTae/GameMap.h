#pragma once

#include "Texture.h"

class CGameState;

class CGameMap
{
	friend class CGameState;
	friend class CHero;
	friend class CMonster;
	friend class CItem;
	friend class CEquip;
private:
	CTexture m_mapData;
	int m_currentX;
	
	int nowMapNumber;

	bool m_bossClear;

public:
	CGameMap(void);
	~CGameMap(void);

	void LoadMap(CGameState *gs, int index);

	void Update(double et);
	void Draw();
};
