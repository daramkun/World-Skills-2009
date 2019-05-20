#pragma once

#include "Graphics.h"
#include "Texture.h"
#include "GameMap.h"
#include "Hero.h"

enum ITEMTYPE
{
	IT_SSANGHWATANG = 0,
};

class CItem
{
private:
	CTexture m_item;
	ITEMTYPE m_type;
	int x;
	bool isDead;

public:
	CItem(void);
	~CItem(void);

	void Create(CGraphics &g, ITEMTYPE type, int item_x);

	void Update(double et, CGameMap &map, CHero &hero);
	void Draw(CGraphics &g, CGameMap &map);
};
