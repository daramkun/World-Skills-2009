#include "Game.h"

CGame g_Game;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	OSVERSIONINFO info; ZeroMemory(&info, sizeof(info));
	info.dwOSVersionInfoSize = sizeof(info);
	GetVersionEx(&info);

	if(info.dwMajorVersion < 5)
	{
		MessageBox(NULL, "Windows 버전을 XP 이상으로 맞추십시오.", NULL, NULL);
		return -1;
	}

	if(!g_Game.Create()) {MessageBox(NULL, "오류가 발생하여 게임을 중단합니다", NULL, NULL); return 0;}
	g_Game.Run();
	g_Game.Destroy();

	return 1;
}