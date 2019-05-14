#include "global.hpp"

void CreateWnd (HWND hwnd)
{
hBm = LoadBitmap(gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
GetObject(hBm, sizeof(BITMAP), &bm);
hDC = GetDC(hwnd);
if (hDC == NULL){PostQuitMessage(WM_NULL);}
hDC2 = CreateCompatibleDC(hDC);
ReleaseDC(hwnd, hDC);
}

void PaintWnd (HWND hwnd)
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
	
	if (!RegisterClassEx(&classex)){Error(ERROR_GCLASSNOT, ERROR_EXIT_APP);}
	
return TRUE;
}

void CreateMainWindow (void) 
{
	MainRegClass(WndCMain, gapp.WndProc, gapp._class, gapp.inst);
	
	gapp.wnd = CreateWindowEx(0, gapp._class, gapp._wnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, \
	pwnd.x, pwnd.y, szwnd.x, szwnd.y, NULL, NULL, gapp.inst, NULL);

	if (gapp.wnd == NULL){Error(ERROR_GWNDNOT, ERROR_EXIT_APP);}
	ShowWindow(gapp.wnd, SW_SHOW);
	UpdateWindow(gapp.wnd);
}

void SetPosDlg(HWND hwnd, HWND dia)
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

BOOL SelectFile(void)
{
	wchar_t szFileName[MAXPATHLEN];
	wchar_t szFileTitle[MAXPATHLEN];
	wchar_t lpstrTitle[MAXPATHLEN] = L"Выберите файл. По умолчанию он в папке мои документы --> overlord";
	
	memset(&szFileName, 0, sizeof(szFileName));
	memset(&szFileTitle, 0, sizeof(szFileTitle));

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
	
	if (GetOpenFileName(&ofn) != 0) 
	{
		log(L"Выбран файл: %ls", ofn.lpstrFile);
		CloseHandle(hFileOpen);
		hFileOpen = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hFileOpen == 0){Error(ERROR_OPENFILE, ERROR_NOTEXITAPP);return FALSE;}
		PostMessage(gapp.wnd, MSG_SELECTOPENFILE, 0, 0);
		return TRUE;
	}
		else {Error(ERROR_FILECHECK, ERROR_NOTEXITAPP);return FALSE;}
}


BOOL ReadFile(void)
{
	DWORD lSizeFile = SizeFile(hFileOpen);
	if (lSizeFile == INVALID_FILE_SIZE) {Error(ERROR_FILESIZE, ERROR_NOTEXITAPP); return FALSE;} //переделать
	log(L"sizefile=%i", lSizeFile);
	DWORD lNumberReadByte = 0;
	memset(aGlobalBuffer, 0, 0x10000);
	if (ReadFile(hFileOpen, aGlobalBuffer, lSizeFile, &lNumberReadByte, NULL) == 0) {Error(ERROR_OPENFILE, ERROR_NOTEXITAPP);return FALSE;}
	if (lSizeFile != lNumberReadByte){Error(ERROR_OPENFILE, ERROR_NOTEXITAPP);return FALSE;}
	log(L"lNumberReadByte=%i", lNumberReadByte);
	uniDInfo.data.iLenFile = lNumberReadByte;
	log(L"iLenFile=%i", uniDInfo.data.iLenFile);
	PostMessage(gapp.wnd, MSG_READFILE, 0, 0);
}


DWORD SizeFile(HANDLE hFileOpen)
{
	DWORD LowWord;
	return LowWord = GetFileSize(hFileOpen, NULL);
}

BOOL IdentificationFile (void)
{	int i;
	
	
	
	if (i) return TRUE;
	return FALSE;
}

void DlgInit(int numdlg)
{
	switch (numdlg)
	{
		case DLG_ABOUT:
		{
		dlgapp[0].hWnd = CreateDialog(gapp.inst, MAKEINTRESOURCE(IDDLG_ABOUT), gapp.wnd, dlgapp[0].WndProc);
		SetPosDlg(gapp.wnd, dlgapp[0].hWnd);
		SetWindowPos(dlgapp[0].hWnd, HWND_TOP, t_xy_dia.x, t_xy_dia.y, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE );
		}
	}
}