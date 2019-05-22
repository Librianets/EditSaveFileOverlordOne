#include "global.hpp"

class CGameSaveControl CGameSaveControlOne;
class CUnpackPack CUnpackPackOne;

HBITMAP		hBm;
BITMAP		bm;
HDC			hDC;
HDC			hDC2;
	
WNDCLASSEX WndCMain;
RECT RECTmainwnd;
AppData gapp;
Data dlgapp[MAXCOUNTERPOINTER];
sizeall scwnd, szwnd, pwnd, t_xy_dia;

vector<HWND> HWNDSAVEINFO(30, NULL);

vector <unsigned char> *CGameSaveControl::lpGetBuffer(void)
{
	return &aBufferRead;
}

unsigned long int CGameSaveControl::GetiNumberReadByte(void)
{
	return iNumberReadByte;
}

int CGameSaveControl::SelectFile(void)
{	
#if WIN32PROJECT
#if WINAPIPROJECT

	wchar_t aTitleSaveWnd [MAXPATHLEN] = L"Выберите файл. По умолчанию он в папке мои документы --> overlord";

	ofn.lStructSize			= sizeof(OPENFILENAME);
	ofn.lpstrTitle			= aTitleSaveWnd;

	ofn.lpstrFile			= szFileName;
	ofn.nMaxFile			= MAXPATHLEN;
	
	ofn.lpstrFileTitle		= szFileTitle;
	ofn.nMaxFileTitle		= MAXPATHLEN;
	
	ofn.Flags				= OFN_EXPLORER;
	ofn.FlagsEx				= OFN_EX_NOPLACESBAR;
	
	ofn.hwndOwner			= NULL;
	ofn.lpstrFilter			= NULL;
	ofn.lpstrCustomFilter	= NULL;
	ofn.lpstrInitialDir		= NULL;
	ofn.nMaxCustFilter		= 0;
	ofn.nFilterIndex		= 1;
	ofn.lpstrDefExt			= NULL;
	
	if( GetOpenFileName(&ofn) != 0 ) {return SUCCESS;} else {return FAILURE;}
	
#else
#endif
#endif
}

int CGameSaveControl::ReadSaveFile(void)
{
	if (szFileTitle == 0) return ERROR_NOTFILESELECT;
	
	FILE *pFile;
	pFile = _wfopen (szFileTitle, L"rb");
	if (pFile == NULL) return ERROR_OPENFILE;
	
	fseek(pFile, 0, SEEK_END);

	iNumberReadByte = ftell(pFile);
	if (iNumberReadByte == -1L) return ERROR_FILESIZE;
	if ( (iNumberReadByte > MAXSIZEFILE) | (iNumberReadByte <= 0) ) return ERROR_LIMITMAXSIZE;
	
	if (aBufferRead.capacity() > 1) {aBufferRead.clear();}
	aBufferRead.reserve(iNumberReadByte);
	
	fseek(pFile, 0, SEEK_SET);
	aBufferRead.resize(iNumberReadByte);
	if( iNumberReadByte != fread(&aBufferRead[0x0], sizeof(char), iNumberReadByte, pFile) ) return ERROR_FILESIZE;
	
	iNumberReadByte = (unsigned long int) iNumberReadByte;
	return SUCCESS;
}

int OVERLORD::OpenFile(void)
{
	int iTempValue = 0;
	
	iTempValue = CGameSaveControlOne.SelectFile();	if (iTempValue != SUCCESS) {log(L"SelectFile %i", iTempValue ); return FAILURE;}
	iTempValue = CGameSaveControlOne.ReadSaveFile(); if (iTempValue != SUCCESS) {log(L"ReadSaveFile %i", iTempValue ); return FAILURE;}
				
	if (CUnpackPackOne.lpGetBuffer(1)->capacity() > 1) {CUnpackPackOne.lpGetBuffer(1)->clear();}
	CUnpackPackOne.lpGetBuffer(1)->reserve(CGameSaveControlOne.GetiNumberReadByte());
	CUnpackPackOne.lpGetBuffer(1)->resize(CGameSaveControlOne.GetiNumberReadByte());

	*(CUnpackPackOne.lpGetBuffer(1)) = *(CGameSaveControlOne.lpGetBuffer());

	CGameSaveControlOne.~CGameSaveControl();	
	
	iTempValue = CUnpackPackOne.CheckFileSignature(); if (iTempValue != SUCCESS) {log(L"CheckFileSignature %i", iTempValue ); return FAILURE;}
	iTempValue = CUnpackPackOne.Decompression(); if (iTempValue != SUCCESS) {log(L"Decompression %i", iTempValue ); return FAILURE;}
	iTempValue = CUnpackPackOne.DefineTypeFile(); if (iTempValue != SUCCESS) {log(L"DefineTypeFile %i", iTempValue ); return FAILURE;}
	
	return SUCCESS;
} 

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









/*
namespace LIA
{

BOOL OpenFile(void)
{
if (SelectFile() != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_SELECTOPENFILE, 0, 0);}
if (ReadFile() != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_READFILE, 0, 0);}
if (CUnpackPack::CheckFileSignature(&uniDInfo, aGlobalBuffer, aTableCrc32) != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_CHECKFILE, 0, 0);}
if (CUnpackPack::Decompression(uniDInfo.data.iLenFile, MAXSIZEFILE, &aGlobalBuffer[0x6], &aBufferOne[0x0], &uniDInfo) != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_DECOMP, 0, 0);}
if (CUnpackPack::DefineTypeFile(aBufferOne, uniDInfo.data.iUnzip) != TRUE) {return FALSE;} else {PostMessage(gapp.wnd, MSG_DECOMP, 0, 0);} //переделать

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

}//namespace LIA*/
/*
void CreateWndSaveInfo (HWND hwnd)
{
HWNDSAVEINFO[20] = CreateWindowEx(0, L"BUTTON", L"Сохранения", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_CENTER, 5, 7, 200, 500, hwnd, NULL, gapp.inst, NULL);

HWNDSAVEINFO[1] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 1", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 30, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[2] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 2", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 77, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[3] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 3", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 124, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[4] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 4", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 171, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[5] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 5", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 218, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[6] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 6", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 265, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[7] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 7", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 312, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[8] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 8", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 359, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[9] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 9", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 406, 170, 25, hwnd, NULL, gapp.inst, NULL);
HWNDSAVEINFO[10] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 10", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 453, 170, 25, hwnd, NULL, gapp.inst, NULL);

HWNDSAVEINFO[21] = CreateWindowEx(0, L"BUTTON", L"Информация", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_CENTER, 215, 7, 420, 500, hwnd, NULL, gapp.inst, NULL);

}*/
/*
void CloseWndSaveInfo (void)
{
	log(L"Size HWNDSI = %i", HWNDSAVEINFO.size());
	for (int i = 0; i < HWNDSAVEINFO.size(); i++)
	{
	DestroyWindow(HWNDSAVEINFO[i]);
	}

	HWNDSAVEINFO.~vector();
}*/


/*
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
}*/