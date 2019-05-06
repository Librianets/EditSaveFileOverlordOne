#include "global.hpp"


HDC			hDC;
HDC			hdcmem;
HBITMAP		hBm;
BITMAP		bm;
PAINTSTRUCT ps;

void Createwnd (HWND hwnd)
{
hBm = LoadBitmap(gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
GetObject(hBm, sizeof(BITMAP), &bm);
hDC = GetDC(hwnd);
if (hDC == NULL){PostQuitMessage(WM_NULL);}
hdcmem = CreateCompatibleDC(hDC);
ReleaseDC(hwnd, hDC);
//if (hdc_globalwindow == NULL){PostQuitMessage(WM_NULL);}
}

void Paintwnd (HWND hwnd)
{
hDC = BeginPaint(hwnd, &ps);
SelectObject(hdcmem, hBm);
BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);
EndPaint(hwnd, &ps);
}


BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
{
	classex.cbSize = sizeof(classex);
	classex.style = CS_HREDRAW | CS_VREDRAW;
	classex.lpfnWndProc = Proc;
	classex.cbClsExtra = 0;
	classex.cbWndExtra = 0;
	classex.hInstance = hinstance;
	classex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APP_ICON));
	classex.hCursor = NULL;
	classex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	classex.lpszMenuName = MAKEINTRESOURCE(IDM_MENU);
	classex.lpszClassName = szClassName;
	classex.hIconSm = NULL;
	
	if (!RegisterClassEx(&classex)){error(gclassnot, exit_app);}
	
return TRUE;
}

LRESULT WINAPI MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
		
		case WM_CREATE:
		{
		Createwnd(hWnd);
		}break;
		
		case WM_PAINT: 
		{
		Paintwnd(hWnd);
		}break;
		
		case WM_DESTROY: {destroy_all(); break;}
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case ID_ABOUT:
				{
					dapp[0].hWnd = CreateDialog(gapp.inst, MAKEINTRESOURCE(ID_ABOUT), gapp.wnd, dapp[0].WndProc);
					position_dia(gapp.wnd, dapp[0].hWnd);
					SetWindowPos(dapp[0].hWnd, HWND_TOP, t_xy_dia.x, t_xy_dia.y, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE );
				}break;
				
				case ID_OPENFILE:
				{
					checkfile();
				}break;
				
				case ID_CONSOLE:
				{
					openconsole();
					writeconsole();
				}break;	
				
				case ID_EXIT:
				{
					PostQuitMessage(WM_DESTROY);
				}break;
				
				default: return (DefWindowProc(hWnd, msg, wParam, lParam));
			}
		} else {break;}
		}
default: return (DefWindowProc(hWnd, msg, wParam, lParam));
}

}

BOOL CALLBACK AboutWndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_INITDIALOG: return TRUE; break;
		case WM_COMMAND:
		{
		if (LOWORD(wparam) == ID_ABOUT1){EndDialog(hwnd, 0);} else {break;}
		}
	}
		
return FALSE;
}

void CreateMainWindow (void) 
{
	MainRegClass(WndC_main, gapp.WndProc, gapp._class, gapp.inst);
	gapp.wnd = CreateWindowEx(0, gapp._class, gapp._wnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, pwnd.x, pwnd.y, szwnd.x, szwnd.y, NULL, NULL, gapp.inst, NULL); 

	if (gapp.wnd == NULL){error(gwndnot, exit_app);}

	ShowWindow(gapp.wnd, SW_SHOW); //nCmdShow
	
	UpdateWindow(gapp.wnd);//WM_PAINT


//	CreateMainMenu();
//	SetMenu(gApp.hWnd, gApp.hMenu);
}

void runmsg(void)
{
	hAccel = LoadAccelerators(gapp.inst, MAKEINTRESOURCE(ID_G_ACCEL)); 
    if (hAccel == NULL) {error(gaccelnot, exit_app);}
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if (IsDialogMessage(dapp[0].hWnd, &msg) == TRUE)
		{
			
		}
		else
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
}

void destroy_all (void)
{
CloseWindow(gapp.wnd);
UnregisterClass(gapp._class, gapp.inst);
closeconsole();
PostQuitMessage(WM_NULL);
}


void position_dia(HWND hwnd, HWND dia)
{
RECT t_poswnd;
RECT t_posdia;
GetWindowRect(hwnd, &t_poswnd);
GetWindowRect(dia, &t_posdia);
t_xy_dia.x = t_posdia.right - t_posdia.left;
t_xy_dia.y = t_posdia.bottom - t_posdia.top;
t_poswnd.left += ((t_poswnd.right-t_poswnd.left-t_xy_dia.x)/2);
t_poswnd.top += ((t_poswnd.bottom-t_poswnd.top-t_xy_dia.y)/2);

t_xy_dia.x = t_poswnd.left;
t_xy_dia.y = t_poswnd.top;
}

void checkfile(void)
{
	OPENFILENAME ofn;
	
	wchar_t szFileName[MAXPATHLEN];
	wchar_t szFileTitle[MAXPATHLEN];
	wchar_t lpstrTitle[MAXPATHLEN] = L"Выберите файл. По умолчанию он в папке мои документы --> overlord";
	
	memset(&szFileName, 0, sizeof(szFileName));
	memset(&szFileTitle, 0, sizeof(szFileTitle));
	memset(&fileopen, 0, sizeof(fileopen));

	ofn.lStructSize			= sizeof(OPENFILENAME);
	ofn.hwndOwner			= gapp.wnd;
	ofn.lpstrFilter			= NULL;
	ofn.lpstrCustomFilter	= NULL;
	ofn.lpstrInitialDir		= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 1;
	ofn.lpstrTitle			= lpstrTitle;
	ofn.lpstrFile			= szFileName;
	ofn.nMaxFile			= MAXPATHLEN;
	ofn.lpstrFileTitle		= szFileTitle;
	ofn.nMaxFileTitle		= MAXPATHLEN;
	ofn.lpstrDefExt			= NULL;
	ofn.Flags				= OFN_EXPLORER;
	ofn.FlagsEx				= OFN_EX_NOPLACESBAR;
	if (GetOpenFileName(&ofn) != 0) {wcscpy(fileopen, ofn.lpstrFile);PostMessage(gapp.wnd, MSGOPENFILE, 0, 0);} else {error(filecheck, notexitapp);}
}


void openfile(void)
{
	
}

	
/*
#define maxfilesize		1048576
HANDLE hfileread;
CreateFile()
unsigned char [maxfilesize];
ReadFile(hFile, lpBuff, dwBuffSize, &dwCount, NULL);

Чтение из файла в буфер lpBuff размером dwBuffSize. В переменную dwCount записывается реальное количество прочитанных байт. Последний опциональный аргумент называется lpOverlapped и о нем сейчас знать не нужно.

WriteFile(hFile, lpBuff, dwBuffSize, &dwCount, NULL);
Аргументы и семантика процедуры WriteFile полностью аналогичны ReadFile.

CloseHandle(hFile);*/
	
/*
HANDLE CreateFile(
  LPCTSTR  lpFileName,                         // имя файла
  DWORD  dwDesiredAccess,                      // режим доступа
  DWORD  dwShareMode,                          // совместный доступ
  LPSECURITY_ATTRIBUTES  lpSecurityAttributes, // SD (дескр. защиты)
  DWORD  dwCreationDisposition,                // как действовать
  DWORD  dwFlagsAndAttributes,                 // атрибуты файла
  HANDLE  hTemplateFile                        // дескр.шаблона файла
);

BOOL ReadFile(
  HANDLE hFile,                // дескриптор файла
  LPVOID lpBuffer,             // буфер данных
  DWORD nNumberOfBytesToRead,  // число байтов для чтения
  LPDWORD lpNumberOfBytesRead, // число прочитанных байтов
  LPOVERLAPPED lpOverlapped    // асинхронный буфер
);*/