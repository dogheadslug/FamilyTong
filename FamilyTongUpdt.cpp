// FamilyTongUpdt.cpp : Defines the entry point for the application.
// FamilyTong Update module
// After FamilyTong main module detected a newer version is available
// it will start this update module.
//
// FamilyTongUpdt shall decompress and replace the old version files.
// After the update is finished, it will open the main module.

#include "stdafx.h"
#include "FamilyTongUpdt.h"

#include <string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HBITMAP bitmap;
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FAMILYTONGUPDT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FAMILYTONGUPDT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FAMILYTONGUPDT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_FAMILYTONGUPDT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, L"FamilyTongUpdate", WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, CW_USEDEFAULT,800,450, nullptr, nullptr, hInstance, nullptr);
   // L"FamilyTongUpdate" is used to turn "FamilyTongUpdate"(a const char) 
   // into LPCWSTR (Long Pointer to Constant Wide String)

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			
            // TODO: Add any drawing code that uses hdc here...

			//adding bitmap image. Source:
			//https://social.msdn.microsoft.com/Forums/vstudio/en-US/4817f6a6-e47a-4431-bbbb-e395af339eab/how-to-insert-an-image-in-win32-application?forum=vclanguage
			HDC hMemDC = CreateCompatibleDC(hdc);
			::SelectObject(hMemDC, bitmap);
			BitBlt(hdc, 20, 20, 360, 360, hMemDC, 0, 0, SRCCOPY);
			//str::string s0("this is test text");
			char szSize[100];
			//char msg1[] = L"a newer version of FamilyTong is available";

			/*TextOut(hdc, 450, 170, L"检测到全家桶有新版本!",
				strlen("检测到全家桶有新版本!"));*/

			

			//select the font in 
			//CreateFont function
			//https://msdn.microsoft.com/en-us/library/windows/desktop/dd183499(v=vs.85).aspx
			HFONT font = CreateFont(18, 0, 0, 0, 200, false, false, false, CHINESEBIG5_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY, DEFAULT_PITCH, L"Arial");
			HFONT hFontOld = (HFONT)SelectObject(hdc, font);
			//textbox RECT
			RECT textbox1 = {380,50,800,75};
			RECT textbox2 = {380,75,800,100};
			RECT textbox3 = {380,100,800,125};
			
			DrawText(hdc, L"a newer version of FamilyTong is available ", 
				strlen("a newer version of FamilyTong is available "), &textbox1, DT_CENTER);
			DrawText(hdc, L"the client will restart after the installation is complete",
				strlen("the client will restart after the installation is complete"), &textbox2, DT_CENTER);
			DrawTextW(hdc, L"检测到更新版本的全家桶，安装完成后重启。",
				/*strlen("检测到更新版本的全家桶，安装完成后重启。")*/-1, &textbox3, DT_CENTER);
			//http://c.biancheng.net/cpp/html/2952.html

			::DeleteDC(hMemDC);

            EndPaint(hWnd, &ps);
        }
        break;
	//adding a bitmap image
	case WM_CREATE: 
	{
		bitmap = (HBITMAP)LoadImage(NULL, (L"E:\\2017dh.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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
