#include "application.h"

Application* Application::mInstance = nullptr;

Application* Application::getInstance()
{
	if (mInstance == nullptr)
	{
		mInstance = new Application();
	}
	return mInstance;
}

Application::~Application(){}

Application::Application(){}





LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Application::getInstance()->handleMessage(hwnd, message, wParam, lParam);
	return(DefWindowProc(hwnd, message, wParam, lParam));
}

bool Application::initApplication(HINSTANCE hInstance, const uint32_t& width, const uint32_t& height)
{
	mWidth = width;
	mHeight = height;

	registerWindowsClass(hInstance);

	if (!createWindow(hInstance))
	{
		return false;
	}
	return true;
}

void Application::handleMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)						//switch语句开始
	{
	case WM_PAINT:						// 若是客户区重绘消息
		ValidateRect(hwnd, NULL);		// 更新客户区的显示
		break;									//跳出该switch语句

	case WM_KEYDOWN:                // 若是键盘按下消息
		if (wParam == VK_ESCAPE)    // 如果被按下的键是ESC
			DestroyWindow(hwnd);		// 销毁窗口, 并发送一条WM_DESTROY消息
		break;									//跳出该switch语句

	case WM_DESTROY:				//若是窗口销毁消息
		PostQuitMessage(0);		//向系统表明有个线程有终止请求。用来响应WM_DESTROY消息
		mAlive = false;
		break;								//跳出该switch语句
	}
}

bool Application::peekMessage()
{
	//消息循环过程
	MSG msg = { 0 };		//定义并初始化msg
	while (msg.message != WM_QUIT)			//使用while循环，如果消息不是WM_QUIT消息，就继续循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);			//分发一个消息给窗口程序。
		}
	}
	return mAlive;
}

ATOM Application::registerWindowsClass(HINSTANCE hInstance)
{
	//【1】窗口创建四步曲之一：开始设计一个完整的窗口类
	WNDCLASSEX wndClass = { 0 };							//用WINDCLASSEX定义了一个窗口类
	wndClass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndClass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndClass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndClass.cbClsExtra = 0;								//窗口类的附加内存，取0就可以了
	wndClass.cbWndExtra = 0;							//窗口的附加内存，依然取0就行了
	wndClass.hInstance = hInstance;						//指定包含窗口过程的程序的实例句柄。
	wndClass.hIcon = (HICON)::LoadImage(NULL, "asset/favicon.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  //为hbrBackground成员指定一个灰色画刷句柄	
	wndClass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndClass.lpszClassName = mWindowClassName;		//用一个以空终止的字符串，指定窗口类的名字。

	//【2】窗口创建四步曲之二：注册窗口类
	if (!RegisterClassEx(&wndClass))				//设计完窗口后，需要对窗口类进行注册，这样才能创建该类型的窗口
		return -1;
	return 1;
}

BOOL Application::createWindow(HINSTANCE hInstance)
{
	mWindowInst = hInstance;

	auto dwStyle = WS_OVERLAPPEDWINDOW;

	//【3】窗口创建四步曲之三：正式创建窗口
	mHwnd = CreateWindow(
		mWindowClassName,
		(LPCSTR)"Graphic",		//喜闻乐见的创建窗口函数CreateWindow
		dwStyle,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		mWidth,
		mHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!mHwnd)
	{
		return FALSE;
	}

	//【4】窗口创建四步曲之四：窗口的移动、显示与更新	
	ShowWindow(mHwnd, true);    //调用ShowWindow函数来显示窗口
	UpdateWindow(mHwnd);
	return TRUE;
}