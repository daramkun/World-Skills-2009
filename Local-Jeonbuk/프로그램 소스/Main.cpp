#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	OSVERSIONINFO osInfo; ZeroMemory(&osInfo, sizeof(osInfo));
	osInfo.dwOSVersionInfoSize = sizeof(osInfo);

	GetVersionEx(&osInfo);

	if(osInfo.dwMajorVersion < 5)
	{
		MessageBox(NULL, "이 게임은 Windows XP 이상의 운영체제에서만 실행됩니다.",
			NULL, NULL);
		return -1;
	}

	if(!g_Game.Create()) return -1;
	g_Game.Run();
	g_Game.Destroy();

	return 1;
}