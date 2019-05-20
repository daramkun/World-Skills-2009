#pragma once

#include "State.h"
#include "GameMap.h"

#include "Img.h"
#include "Fnt.h"

class CGameState
	: public CState
{
private:
	CGameMap gameMap;

	CImg inter[6];
	CImg brqInter[2];

	 CImg gameOver;
	 CImg gameClear;

	 CFnt m_levelShow;

public:
	CGameState(void);
	~CGameState(void);

	void Initial();
	void Update(double dt);
	void Draw();
	void Destroy();
};
