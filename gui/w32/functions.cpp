#include "global.hpp"

HANDLE 		hFileOpen;
HDC			hDC;
HDC			hDC2;
HBITMAP		hBm;
BITMAP		bm;

OPENFILENAME ofn;

wchar_t szFileName[MAXPATHLEN];
	
WNDCLASSEX WndCMain;
RECT RECTmainwnd;
AppData gapp;
Data dlgapp[MAXCOUNTERPOINTER];
sizeall scwnd, szwnd, pwnd, t_xy_dia;

vector<HWND> HWNDSAVEINFO(30, NULL);

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

namespace LIA
{

BOOL OpenFile(void)
{
if (SelectFile() != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_SELECTOPENFILE, 0, 0);}
if (ReadFile() != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_READFILE, 0, 0);}
if (CheckFileSignature(&uniDInfo, aGlobalBuffer, aTableCrc32) != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_CHECKFILE, 0, 0);}
if (Decompression(uniDInfo.data.iLenFile, MAXSIZEFILE, &aGlobalBuffer[0x6], &aBufferOne[0x0], &uniDInfo) != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_DECOMP, 0, 0);}
if (DefineTypeFile (aBufferOne, uniDInfo.data.iUnzip) != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_DECOMP, 0, 0);} //переделать

switch (iFlagDefSave)
{
case SAVEINFO: PostMessage(gapp.wnd, MSG_SAVEINFO, 0, 0); break;
case SAVESLOT: PostMessage(gapp.wnd, MSG_SAVESLOT, 0, 0); break;
default: Error(ERROR_GCLASSNOT, ERROR_EXIT_APP); break; //переделать
}
return TRUE;
}

BOOL SaveFile(void)
{
if (Compression(uniDInfo.data.iUnzip, MAXSIZEFILE, aBufferOne, aGlobalBuffer, &uniDInfo) != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_COMP, 0, 0);}
if (SaveFileEnd() != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_WRITEFILE, 0, 0);}
return TRUE;
}

}//namespace LIA


//	HBUTTON.reserve(count);

void CreateWndSaveInfo (HWND hwnd)
{
HWNDSAVEINFO[20] = CreateWindowEx(0, L"BUTTON", L"Сохранения", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_CENTER, 5, 7, 310, 500, hwnd, NULL, gapp.inst, NULL);

HWNDSAVEINFO[1] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 1", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 20, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[2] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 2", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 50, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[3] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 3", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 80, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[4] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 4", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 110, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[5] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 5", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 140, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[6] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 6", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 170, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[7] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 7", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 200, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[8] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 8", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 230, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[9] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 9", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 260, 250, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[10] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 10", BS_3STATE | WS_CHILD | WS_VISIBLE, 10, 290, 250, 25, hwnd, NULL, gapp.inst, NULL);

HWNDSAVEINFO[21] = CreateWindowEx(0, L"BUTTON", L"Информация", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_CENTER, 325, 7, 310, 500, hwnd, NULL, gapp.inst, NULL);

}

void CloseWndSaveInfo (void)
{
	log(L"Size HWNDSI = %i", HWNDSAVEINFO.size());
	for (int i = 0; i < HWNDSAVEINFO.size(); i++)
	{
	DestroyWindow(HWNDSAVEINFO[i]);
	}

	HWNDSAVEINFO.~vector();
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
	//// Вычисляю размер клиентской области ////
	scwnd.x = GetSystemMetrics(SM_CXSCREEN); //1920
	scwnd.y = GetSystemMetrics(SM_CYSCREEN); //1080
	szwnd.x = (1280/2); //640
	szwnd.y = (1024/2); //512
	pwnd.x = (scwnd.x-szwnd.x)/2; //(1920-640)/2=640
	pwnd.y = (scwnd.y-szwnd.y)/2; //(1080-512)/2=284
	RECTmainwnd.left = pwnd.x; //640
	RECTmainwnd.right = pwnd.x + szwnd.x; //1280
	RECTmainwnd.top = pwnd.y; //
	RECTmainwnd.bottom = pwnd.y + szwnd.y;
	AdjustWindowRectEx(&RECTmainwnd, WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, TRUE, 0);
	szwnd.x = RECTmainwnd.right-RECTmainwnd.left;
	szwnd.y = RECTmainwnd.bottom-RECTmainwnd.top;
	///////////////////////////////////////////////////////////////////
	
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
		log(L"Выбран файл: %ls", szFileName);
		CloseHandle(hFileOpen);
		hFileOpen = CreateFile(ofn.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hFileOpen == 0){Error(ERROR_OPENFILE, ERROR_NOTEXITAPP);return FALSE;}
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
	return TRUE;
}


DWORD SizeFile(HANDLE hFileOpen)
{
	DWORD LowWord;
	return LowWord = GetFileSize(hFileOpen, NULL);
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

BOOL SaveFileEnd(void)
{
	CloseHandle(hFileOpen);
	log(L"szFileName=%ls", szFileName);
	log(L"hFileOpen=%i", hFileOpen);
	hFileOpen = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, 0, NULL);
	log(L"hFileOpen=%i", hFileOpen);
	if (hFileOpen == 0){Error(ERROR_OPENSAVEFILE, ERROR_NOTEXITAPP);return FALSE;}
	DWORD iSizeFile = (DWORD)uniDInfo.data.iLenFile;
	DWORD lNumberWriteByte = 0;
	log(L"sizefile=%i", iSizeFile);
	log(L"szFileName=%ls", szFileName);
	log(L"hFileOpen=%i", hFileOpen);
	if (WriteFile(hFileOpen, aGlobalBuffer, iSizeFile, &lNumberWriteByte, NULL) == 0) {Error(ERROR_OPENSAVEFILE, ERROR_NOTEXITAPP);return FALSE;}
	log(L"lNumberWriteByte=%i", lNumberWriteByte);
	if (iSizeFile != lNumberWriteByte){Error(ERROR_OPENSAVEFILE, ERROR_NOTEXITAPP);return FALSE;}
	CloseHandle(hFileOpen);
	PostMessage(gapp.wnd, MSG_WRITEFILE, 0, 0);
	return TRUE;
}