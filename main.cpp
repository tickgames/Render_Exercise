#include<iostream>
#include<Windows.h>
#include"application/application.h"

#pragma comment(linker, "/subsystem:console /entry:wWinMainCRTStartup")
#pragma comment(lib, "winmm.lib")


int WINAPI wWinMain(
	HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	PWSTR pCmdLine, 
	int nCmdShow)
{
	PlaySound("asset/ÎÒ¼ÇµÃ.wav", NULL, SND_FILENAME | SND_ASYNC);

	if (!app->initApplication(hInstance, 800, 600)) {
		return -1;
	}

	bool alive = true;

	while (alive) {
		alive = app->peekMessage();
	}

	return 0;

}