#include "MenuState.h"

#include "Game.h"
#include "Input.h"

#include "Lib.h"

CMenuState::CMenuState(void)
{
}

CMenuState::~CMenuState(void)
{
}

void CMenuState::Initial()
{
	bg.Create("Content/Menu/Main.png");
	cursor.Create("Content/Menu/C.png");
}

void CMenuState::Update(double dt)
{
	if(g_Input.KeyDown(DIK_UP) || g_Input.KeyDown(DIK_DOWN))
	{
		currentCursor = !currentCursor;
		CLib::SoundPlay("Content/Sound/MenuSelect.wav");
	}

	if(g_Input.KeyDown(DIK_SPACE))
	{
		CLib::SoundPlay("Content/Sound/MenuChoose.wav");
		switch(currentCursor)
		{
		case 0:
			g_Game.SetIndex(2);
			break;
		case 1:
			PostQuitMessage(0);
			break;
		}
	}
}

void CMenuState::Draw()
{
	bg.Draw(0, 0);
	cursor.Draw(380, 270 + (currentCursor * 70));
}

void CMenuState::Destroy()
{
	bg.Destroy();
	cursor.Destroy();
}