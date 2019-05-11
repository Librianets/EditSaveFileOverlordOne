#include "global.hpp"

HDC			hDC;
HDC			hDC2;
HBITMAP		hBm;
BITMAP		bm;

void Createwnd (HWND hwnd)
{
hBm = LoadBitmap(gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
GetObject(hBm, sizeof(BITMAP), &bm);
hDC = GetDC(hwnd);
if (hDC == NULL){PostQuitMessage(WM_NULL);}
hDC2 = CreateCompatibleDC(hDC);
ReleaseDC(hwnd, hDC);
}

void Paintwnd (HWND hwnd)
{
PAINTSTRUCT ps;
hDC = BeginPaint(hwnd, &ps);
SelectObject(hDC2, hBm);
BitBlt(hDC, 0, 0, bm.bmWidth, bm.bmHeight, hDC2, 0, 0, SRCCOPY);
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
	classex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(ID_APP_ICON));
	classex.hCursor = NULL;
	classex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	classex.lpszMenuName = MAKEINTRESOURCE(IDM_MENU);
	classex.lpszClassName = szClassName;
	classex.hIconSm = NULL;
	
	if (!RegisterClassEx(&classex)){error(gclassnot, exit_app);}
	
return TRUE;
}

void CreateMainWindow (void) 
{
	MainRegClass(WndC_main, gapp.WndProc, gapp._class, gapp.inst);
	
	gapp.wnd = CreateWindowEx(0, gapp._class, gapp._wnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, \
	pwnd.x, pwnd.y, szwnd.x, szwnd.y, NULL, NULL, gapp.inst, NULL);

	if (gapp.wnd == NULL){error(gwndnot, exit_app);}
	ShowWindow(gapp.wnd, SW_SHOW);
	UpdateWindow(gapp.wnd);
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

void dialoginit(int numdlg)
{
	switch (numdlg)
	{
		case DLG_ABOUT:
		{
		dapp[0].hWnd = CreateDialog(gapp.inst, MAKEINTRESOURCE(IDDLG_ABOUT), gapp.wnd, dapp[0].WndProc);
		position_dia(gapp.wnd, dapp[0].hWnd);
		SetWindowPos(dapp[0].hWnd, HWND_TOP, t_xy_dia.x, t_xy_dia.y, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE );
		}
	}
}