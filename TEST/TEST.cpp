// TEST.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "TEST.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));

	// 主消息循环:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TEST));
	wcex.hCursor		= LoadCursor(NULL,IDC_IBEAM);    //光标形状
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+20);    //背景颜色
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, (LPCWSTR)_T("Introduction"), WS_OVERLAPPEDWINDOW,
      200, 100, 1100, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			if(IDYES==::MessageBoxA(hWnd,"Do you really want to quit?","Warning",MB_YESNO))
				::DestroyWindow(hWnd);	
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此添加任意绘图代码...
		::SetTextColor(hdc,RGB(50,100,180));
		::SetTextCharacterExtra(hdc,5);
		::TextOutA(hdc,45,20,"基于窗口的应用程序的流程:",strlen("基于窗口的应用程序的流程:"));
		::TextOutA(hdc,50,45,"1.设计窗口类",strlen("1.设计窗口类"));
		::TextOutA(hdc,50,65,"2.注册并创建窗口",strlen("2.注册并创建窗口"));
		::TextOutA(hdc,50,85,"3.显示及更新窗口",strlen("3.显示及更新窗口"));
		::TextOutA(hdc,50,105,"4.在窗口程序运行的过程中，不断用GetMessage从队列中抓取消息",strlen("4.在窗口程序运行的过程中，不断用GetMessage从队列中抓取消息"));
		::TextOutA(hdc,50,125,"5.若消息是WM_QUIT，GetMessage传回0结束while循环，进而程序结束",strlen("5.若消息是WM_QUIT，GetMessage传回0结束while循环，进而程序结束"));
		::TextOutA(hdc,45,180,"学完这门课，我希望可以基本了解MFC编程的知识，能够进行一定的编程操作，并且能满足我日后的编程需要。",strlen("学完这门课，我希望可以基本了解MFC编程的知识，能够进行一定的编程操作，并且能满足我日后的编程需要。"));
		::TextOutA(hdc,45,230,"你好，我叫岳淇星，学号是918108320122，我是能源与动力工程学院的一名大二学生。",strlen("你好，我叫岳淇星，学号是918108320122，我是能源与动力工程学院的一名大二学生。"));
		::TextOutA(hdc,45,255,"我来自陕西省咸阳市，我的家乡是一座历史悠久的古都，有着2000多年的历史。",strlen("我来自陕西省咸阳市，我的家乡是一座历史悠久的古都，有着2000多年的历史。"));
		::TextOutA(hdc,45,280,"我的专业是武器发射工程，如果你对这方面的知识感兴趣，我们可以一起聊聊。",strlen("我的专业是武器发射工程，如果你对这方面的知识感兴趣，我们可以一起聊聊。"));
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		WinExec("C://WINDOWS//system32//calc.exe",SW_SHOW);
		break;
	case WM_CLOSE:
		if(IDYES==::MessageBoxA(hWnd,"Do you really want to quit?","Warning",MB_YESNO))
			::DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
