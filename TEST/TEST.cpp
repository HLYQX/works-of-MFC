// TEST.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TEST.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TEST, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TEST));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
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
	wcex.hCursor		= LoadCursor(NULL,IDC_IBEAM);    //�����״
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+20);    //������ɫ
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TEST);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
		// TODO: �ڴ���������ͼ����...
		::SetTextColor(hdc,RGB(50,100,180));
		::SetTextCharacterExtra(hdc,5);
		::TextOutA(hdc,45,20,"���ڴ��ڵ�Ӧ�ó��������:",strlen("���ڴ��ڵ�Ӧ�ó��������:"));
		::TextOutA(hdc,50,45,"1.��ƴ�����",strlen("1.��ƴ�����"));
		::TextOutA(hdc,50,65,"2.ע�Ტ��������",strlen("2.ע�Ტ��������"));
		::TextOutA(hdc,50,85,"3.��ʾ�����´���",strlen("3.��ʾ�����´���"));
		::TextOutA(hdc,50,105,"4.�ڴ��ڳ������еĹ����У�������GetMessage�Ӷ�����ץȡ��Ϣ",strlen("4.�ڴ��ڳ������еĹ����У�������GetMessage�Ӷ�����ץȡ��Ϣ"));
		::TextOutA(hdc,50,125,"5.����Ϣ��WM_QUIT��GetMessage����0����whileѭ���������������",strlen("5.����Ϣ��WM_QUIT��GetMessage����0����whileѭ���������������"));
		::TextOutA(hdc,45,180,"ѧ�����ſΣ���ϣ�����Ի����˽�MFC��̵�֪ʶ���ܹ�����һ���ı�̲������������������պ�ı����Ҫ��",strlen("ѧ�����ſΣ���ϣ�����Ի����˽�MFC��̵�֪ʶ���ܹ�����һ���ı�̲������������������պ�ı����Ҫ��"));
		::TextOutA(hdc,45,230,"��ã��ҽ�����ǣ�ѧ����918108320122��������Դ�붯������ѧԺ��һ�����ѧ����",strlen("��ã��ҽ�����ǣ�ѧ����918108320122��������Դ�붯������ѧԺ��һ�����ѧ����"));
		::TextOutA(hdc,45,255,"����������ʡ�����У��ҵļ�����һ����ʷ�ƾõĹŶ�������2000�������ʷ��",strlen("����������ʡ�����У��ҵļ�����һ����ʷ�ƾõĹŶ�������2000�������ʷ��"));
		::TextOutA(hdc,45,280,"�ҵ�רҵ���������乤�̣��������ⷽ���֪ʶ����Ȥ�����ǿ���һ�����ġ�",strlen("�ҵ�רҵ���������乤�̣��������ⷽ���֪ʶ����Ȥ�����ǿ���һ�����ġ�"));
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

// �����ڡ������Ϣ�������
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
