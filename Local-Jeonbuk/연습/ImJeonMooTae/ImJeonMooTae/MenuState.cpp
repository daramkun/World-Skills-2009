#include "MenuState.h"
#include "Extern.h"

CMenuState::CMenuState(void)
{
}

CMenuState::~CMenuState(void)
{
}

void CMenuState::Initial()
{
	m_bg.Create(g_Game.GetG(), "Resource/Menu/Main.png");
	m_cursor.Create(g_Game.GetG(), "Resource/Menu/Cursor.png");
}

void CMenuState::Update(double et)
{
	if(g_Game.GetI().KeyDown(DIK_UP) || g_Game.GetI().KeyDown(DIK_DOWN))
	{
		if(cursor == 0)
			cursor = 1;
		else
			cursor = 0;
		sndPlaySound("Resource/Sound/SelectMenu.wav", SND_ASYNC);
	}

	if(g_Game.GetI().KeyDown(DIK_SPACE))
	{
		sndPlaySound("Resource/Sound/GameStart.wav", SND_ASYNC);

		switch(cursor)
		{
		case 0:
			g_Game.SetState(2);
			break;
		case 1:
			PostQuitMessage(0);
			break;
		}
	}
}

void CMenuState::Draw()
{
	m_bg.Draw(g_Game.GetG(), 0, 0);
	m_cursor.Draw(g_Game.GetG(), 358, 272 + cursor * m_cursor.GetHeight());
}

void CMenuState::Destroy()
{

}