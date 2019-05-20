#pragma once

#include "Texture.h"
#include "Hero.h"
#include "GameMap.h"

class CEquip
{
private:
	CTexture m_equipImage;
	EQUIPTYPE m_equipType;
	int m_x;

	bool isWearing;

public:
	CEquip(void);
	~CEquip(void);

	void Create(CGraphics& g, EQUIPTYPE et, int x);

	void Update(double et, CHero& hero, CGameMap &map);
	void Draw(CGraphics& g, CGameMap &map);

	void Destroy();
};
