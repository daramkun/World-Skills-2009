#include "Game.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	OSVERSIONINFO osInfo; ZeroMemory(&osInfo, sizeof(osInfo));
	osInfo.dwOSVersionInfoSize = sizeof(osInfo);

	GetVersionEx(&osInfo);

	if(osInfo.dwMajorVersion < 5)
	{
		MessageBox(NULL, "�� ������ Windows XP �̻��� �ü�������� ����˴ϴ�.",
			NULL, NULL);
		return -1;
	}

	if(!g_Game.Create()) return -1;
	g_Game.Run();
	g_Game.Destroy();

	return 1;
}