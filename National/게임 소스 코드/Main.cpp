#include "Game.h"

#include "MenuState.h"
#include "GameState.h"
#include "ResultState.h"

#include <stdlib.h>
#include <time.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	OSVERSIONINFO osinfo; ZeroMemory(&osinfo, sizeof(osinfo));
	osinfo.dwOSVersionInfoSize = sizeof(osinfo);
	GetVersionEx(&osinfo);

	if(osinfo.dwMajorVersion < 5)
	{
		MessageBox(NULL, L"�� ������ Windows XP �̻󿡼��� �۵��մϴ�.",
			L"�˸�", NULL);
		return -1;
	}

	CGame game;

	CMenuState menuState(&game);
	CGameState gameState(&game);
	CResultState resultState(&game);

	game.AddState(&menuState, STATE_MENU);
	game.AddState(&gameState, STATE_GAME);
	game.AddState(&resultState, STATE_RESULT);
	game.SetState(STATE_MENU);

	srand((int)time(NULL));
	
	game.Run();

	return 1;
}