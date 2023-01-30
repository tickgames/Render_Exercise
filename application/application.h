#pragma once

#include<Windows.h>
#include"../global/base.h"


#define  app  Application::getInstance()

class Application {
public:
	static Application* getInstance();

	
	~Application();

	bool initApplication(HINSTANCE hInstance, const uint32_t& width = 800, const uint32_t& height = 600);

	void handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	bool peekMessage();
private:
	Application();
	BOOL createWindow(HINSTANCE hInstance);
	ATOM registerWindowsClass(HINSTANCE hInstance);
private:
	static Application* mInstance;

	bool mAlive{ true };

	HINSTANCE mWindowInst;
	CHAR mWindowClassName[100] = "AppWindow";
	uint32_t mWidth;
	uint32_t mHeight;
	HWND mHwnd;

 
};