#include "Game.h"

CGame g_Game;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	OSVERSIONINFO info; ZeroMemory(&info, sizeof(info));
	info.dwOSVersionInfoSize = sizeof(info);
	GetVersionEx(&info);

	if(info.dwMajorVersion < 5)
	{
		MessageBox(NULL, "Windows ������ XP �̻����� ���߽ʽÿ�.", NULL, NULL);
		return -1;
	}

	if(!g_Game.Create()) {MessageBox(NULL, "������ �߻��Ͽ� ������ �ߴ��մϴ�", NULL, NULL); return 0;}
	g_Game.Run();
	g_Game.Destroy();

	return 1;
}