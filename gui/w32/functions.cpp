#include "global.hpp"

class CGameSaveControl CGameSaveControlOne;
class CUnpackPack CUnpackPackOne;
class CSaveInfo CSaveInfoOne;
class CSaveInfoWndControl CSaveInfoWndControlOne;
class CGlobal CGG;

HBITMAP		hBm;
BITMAP		bm;
HDC			hDC;
HDC			hDC2;

WNDCLASSEX WndCMain;
RECT RECTmainwnd;

sizeall scwnd, szwnd, pwnd, t_xy_dia;

void CGlobal::Init(HINSTANCE hInstance)
{
	gapp.inst = hInstance;
}

CGlobal::CGlobal()
{
	gapp.inst = NULL;
	gapp.hwnd = NULL;
	gapp.menu = NULL;
	
	gapp.gclass = sg_WndClass;
	gapp.gwnd = sg_Wnd;
	gapp.WndProc = *MainWndProc;

	dlgapp[0].WndProc = *AboutWndProc;
}

CGlobal::~CGlobal()
{
	
}
	
void CGlobal::ClearClass(void)
{
	memset( &gapp, 0, sizeof(AppData) );
	memset( &dlgapp, 0, sizeof(Data) );
}


CSaveInfoWndControl::CSaveInfoWndControl()
{
	ClearClass();
}

CSaveInfoWndControl::~CSaveInfoWndControl()
{
	ClearClass();
}
	
void CSaveInfoWndControl::ClearClass(void)
{
	CloseWnd();
	for (int i = 0; i < ihwndCount; i++){HWNDSAVEINFO[i] = NULL;}
}

int CSaveInfoWndControl::CreateWnd(void)
{
//GroupBox
HWNDSAVEINFO[29] = CreateWindowEx(0, L"BUTTON", L"Сохранения", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_CENTER, 5, 7, 200, 500, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[28] = CreateWindowEx(0, L"BUTTON", L"Информация", BS_GROUPBOX | WS_CHILD | WS_VISIBLE | BS_CENTER, 215, 7, 420, 500, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);

//CheckBox
HWNDSAVEINFO[0] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 1", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 30, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[1] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 2", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 77, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[2] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 3", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 124, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[3] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 4", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 171, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[4] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 5", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 218, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[5] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 6", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 265, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[6] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 7", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 312, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[7] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 8", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 359, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[8] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 9", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 406, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
HWNDSAVEINFO[9] = CreateWindowEx(0, L"BUTTON", L"Сохранение № 10", BS_3STATE | WS_CHILD | WS_VISIBLE, 15, 453, 170, 25, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
}

int CSaveInfoWndControl::CloseWnd(void)
{
	for (int i = 0; i < ihwndCount; i++)
	{
#ifdef DEBUG
	if (i==0) {Log.Log(L"\r\n");}
	Log.Log(L"DestroyWindow [%i] = %i, ", i, HWNDSAVEINFO[i]);
#endif
	DestroyWindow(HWNDSAVEINFO[i]);
	}

return SUCCESS;
}

HWND *CSaveInfoWndControl::GetHWNDSAVEINFO (void)
{
	return HWNDSAVEINFO;
}

int OVERLORD::SaveSlot(void) 
{
	
return SUCCESS;
}

int OVERLORD::SaveInfo(void)
{
	CSaveInfoOne.ClearClass();
	CSaveInfoWndControlOne.ClearClass();
	CSaveInfoWndControlOne.CreateWnd();
	
	CSaveInfoOne.SaveInfoStructOne.header.numbersize = CUnpackPackOne.lpGetDataInfo()->data.iUnzip;
	CSaveInfoOne.lpGetBuffer()->reserve(CSaveInfoOne.SaveInfoStructOne.header.numbersize);
	*(CSaveInfoOne.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	
#ifdef DEBUG
Log.Log(L"\r\n lpGetDataInfo()->iUnzip = %i", CUnpackPackOne.lpGetDataInfo()->data.iUnzip);
Log.Log(L"\r\n SaveInfoStructOne.header.numbersize = %i", CSaveInfoOne.SaveInfoStructOne.header.numbersize);
for(int l = 0; l < CUnpackPackOne.lpGetDataInfo()->data.iUnzip; l++) {if (l == 0) {Log.Log(L"\r\n");} else {} Log.Log(L"%x, ", (*(CSaveInfoOne.lpGetBuffer()))[l] );}
#endif
	CUnpackPackOne.ClearClass();
	
	CSaveInfoOne.DisassemblySI();
	
return SUCCESS;
}

int OVERLORD::CloseFile(void)
{
	CGameSaveControlOne.ClearClass();
	CUnpackPackOne.ClearClass();
	CSaveInfoOne.ClearClass();
	CSaveInfoWndControlOne.ClearClass();
	Log.ClearClass();
#ifdef DEBUG
Log.Log(L"\r\n OVERLORD::CloseFile SUCCESS ?");
#endif
	return SUCCESS;
}

int OVERLORD::OpenFile(void)
{
	CGameSaveControlOne.ClearClass();
	CUnpackPackOne.ClearClass();
	
	int iTempValue = 0;
	
	iTempValue = CGameSaveControlOne.SelectGameFile();	if (iTempValue != SUCCESS) {return FAILURE;}Log.Log(L"SelectGameFile %i", iTempValue ); 
	iTempValue = CGameSaveControlOne.ReadGameFile(); if (iTempValue != SUCCESS) {return FAILURE;}Log.Log(L"ReadGameFile %i", iTempValue ); 
				
	if (CUnpackPackOne.lpGetBuffer(1)->capacity() > 1) {CUnpackPackOne.lpGetBuffer(1)->clear();}
	CUnpackPackOne.lpGetBuffer(1)->reserve(CGameSaveControlOne.iNumberReadByte);
	CUnpackPackOne.lpGetBuffer(1)->resize(CGameSaveControlOne.iNumberReadByte);

	*(CUnpackPackOne.lpGetBuffer(1)) = *(CGameSaveControlOne.lpGetBuffer());

	CGameSaveControlOne.ClearClass();	
	
	iTempValue = CUnpackPackOne.CheckFileSignature(); if (iTempValue != SUCCESS) {return FAILURE;} Log.Log(L"CheckFileSignature %i", iTempValue ); 
	iTempValue = CUnpackPackOne.Decompression(); if (iTempValue != SUCCESS) {return FAILURE;} Log.Log(L"Decompression %i", iTempValue ); 
	iTempValue = CUnpackPackOne.DefineTypeFile(); if (iTempValue != SUCCESS) {return FAILURE;} Log.Log(L"DefineTypeFile %i", iTempValue ); 
	
	switch (CUnpackPackOne.iFlagDefSave)
	{
		case SAVEINFO: PostMessage(CGG.gapp.hwnd, MSG_SAVEINFO, 0, 0); break;
		case SAVESLOT: PostMessage(CGG.gapp.hwnd, MSG_SAVESLOT, 0, 0); break;
	}

	return SUCCESS;
} 

int OVERLORD::SaveFile(void)
{
	int iTempValue = 0;
	CGameSaveControlOne.ClearClass();
	
	iTempValue = CGameSaveControlOne.SelectSaveGameFile(); if (iTempValue != SUCCESS) {return FAILURE;}Log.Log(L"SelectSaveGameFile %i", iTempValue ); 
		
	iTempValue = CUnpackPackOne.Compression();	if (iTempValue != SUCCESS) {return FAILURE;}Log.Log(L"Compression %i", iTempValue ); 
	
	if (CGameSaveControlOne.lpGetBuffer()->capacity() > 1) {CGameSaveControlOne.lpGetBuffer()->clear();}
	CGameSaveControlOne.lpGetBuffer()->reserve( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );
	CGameSaveControlOne.lpGetBuffer()->resize( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );

	*(CGameSaveControlOne.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	CGameSaveControlOne.iNumberReadByte = CUnpackPackOne.lpGetDataInfo()->data.iLenFile;
	
	iTempValue = CGameSaveControlOne.WriteGameFile(); if (iTempValue != SUCCESS) {return FAILURE;}Log.Log(L"WriteGameFile %i", iTempValue ); 
	
	CGameSaveControlOne.ClearClass();
	return SUCCESS;
}

CGameSaveControl::~CGameSaveControl()
{
	ClearClass();
	aBufferRead.~vector();
}

CGameSaveControl::CGameSaveControl()
{
	memset(&szFileName, 0, sizeof(szFileName));
	memset(&szFileTitle, 0, sizeof(szFileTitle));
	memset(&ofn, 0, sizeof(ofn));
}

vector <unsigned char> *CGameSaveControl::lpGetBuffer(void)
{
	return &aBufferRead;
}

void CGameSaveControl::ClearClass(void)
{
	if (aBufferRead.capacity() > 1) {aBufferRead.clear();}
	memset(&szFileName, 0, sizeof(szFileName));
	memset(&szFileTitle, 0, sizeof(szFileTitle));
	memset(&ofn, 0, sizeof(ofn));
}

int CSaveInfoWndControl::SetWndLong(int num)
{
	Log.Log(L"\r\n (GetWindowLong(HWNDSAVEINFO[num], GWL_STYLE) = %i", (GetWindowLong(HWNDSAVEINFO[num], GWL_STYLE)));
	SetWindowLong(HWNDSAVEINFO[num], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
	
#ifdef DEBUG
	Log.Log(L"\r\n SetWndLong, num = %i", num);
	Log.Log(L"\r\n BS_3STATE = %i", BS_3STATE);
	Log.Log(L"\r\n BS_AUTOCHECKBOX = %i", BS_AUTOCHECKBOX);
	Log.Log(L"\r\n (GetWindowLong(HWNDSAVEINFO[num], GWL_STYLE) = %i", (GetWindowLong(HWNDSAVEINFO[num], GWL_STYLE)));
#endif
	return SUCCESS;
}

unsigned long int CGameSaveControl::GetiNumberReadByte(void)
{
	return iNumberReadByte;
}

int CGameSaveControl::SelectGameFile(void)
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

int CGameSaveControl::SelectSaveGameFile(void)
{
#if WIN32PROJECT
#if WINAPIPROJECT

	wchar_t aTitleSaveWnd [MAXPATHLEN] = L"Укажите имя файла сохранения и его место";

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
	
	if( GetSaveFileName(&ofn) != 0 ) {return SUCCESS;} else {return FAILURE;}
	
#else
#endif
#endif
}

int CGameSaveControl::WriteGameFile(void)
{
	if (szFileTitle == 0) return ERROR_NOTFILESELECT;
	FILE *pFile;
	pFile = _wfopen (szFileTitle, L"wb");
	if (pFile == NULL) {fclose(pFile); return ERROR_OPENFILE;}
	
	fseek(pFile, 0, SEEK_SET);
	if ( (iNumberReadByte > MAXSIZEFILE) | (iNumberReadByte <= 0) ) {fclose(pFile); return ERROR_LIMITMAXSIZE;}
	if( iNumberReadByte != fwrite(&aBufferRead[0x0], sizeof(char), iNumberReadByte, pFile) ) {fclose(pFile); return ERROR_FILESIZE;}
	fclose(pFile);
	return SUCCESS;
}

int CGameSaveControl::ReadGameFile(void)
{
	if (szFileTitle == 0) return ERROR_NOTFILESELECT;
	
	FILE *pFile;
	pFile = _wfopen (szFileTitle, L"rb");
	if (pFile == NULL) {fclose(pFile); return ERROR_OPENFILE;}
	
	fseek(pFile, 0, SEEK_END);

	iNumberReadByte = ftell(pFile);
if (iNumberReadByte == -1L) {fclose(pFile); return ERROR_FILESIZE;}
	if ( (iNumberReadByte > MAXSIZEFILE) | (iNumberReadByte <= 0) ) {fclose(pFile); return ERROR_LIMITMAXSIZE;}
	
	if (aBufferRead.capacity() > 1) {aBufferRead.clear();}
	aBufferRead.reserve(iNumberReadByte);
	
	fseek(pFile, 0, SEEK_SET);
	aBufferRead.resize(iNumberReadByte);
	if( iNumberReadByte != fread(&aBufferRead[0x0], sizeof(char), iNumberReadByte, pFile) ) {fclose(pFile); return ERROR_FILESIZE;}
	
	iNumberReadByte = (unsigned long int) iNumberReadByte;
	fclose(pFile);
	return SUCCESS;
}

void CreateWnd (HWND hwnd)
{
hBm = LoadBitmap(CGG.gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
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
	
if (!RegisterClassEx(&classex)){Log.Error(ERROR_GCLASSNOT, APPEXIT);}
	
return TRUE;
}

void CreateMainWindow (void) 
{
	MainRegClass(WndCMain, CGG.gapp.WndProc, CGG.gapp.gclass, CGG.gapp.inst);
	
	//// Размер клиентской области ////
	scwnd.x = GetSystemMetrics(SM_CXSCREEN); //1920
	scwnd.y = GetSystemMetrics(SM_CYSCREEN); //1080
	szwnd.x = (1280/2); //640 минимум
	szwnd.y = (1024/2); //512 минимум
	pwnd.x = (scwnd.x-szwnd.x)/2; //(1920-640)/2=640
	pwnd.y = (scwnd.y-szwnd.y)/2; //(1080-512)/2=284
	RECTmainwnd.left = pwnd.x; //
	RECTmainwnd.right = pwnd.x + szwnd.x; //
	RECTmainwnd.top = pwnd.y; //
	RECTmainwnd.bottom = pwnd.y + szwnd.y;
	AdjustWindowRectEx(&RECTmainwnd, WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, TRUE, 0);
	szwnd.x = RECTmainwnd.right-RECTmainwnd.left;
	szwnd.y = RECTmainwnd.bottom-RECTmainwnd.top;
	///////////////////////////////////////////////////////////////////
	
	CGG.gapp.hwnd = CreateWindowEx(0, CGG.gapp.gclass, CGG.gapp.gwnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, \
	pwnd.x, pwnd.y, szwnd.x, szwnd.y, NULL, NULL, CGG.gapp.inst, NULL);

	if (CGG.gapp.hwnd == NULL){Log.Error(ERROR_GWNDNOT, APPEXIT);}
	ShowWindow(CGG.gapp.hwnd, SW_SHOW);
	UpdateWindow(CGG.gapp.hwnd);
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
		CGG.dlgapp[0].hWnd = CreateDialog(CGG.gapp.inst, MAKEINTRESOURCE(IDDLG_ABOUT), CGG.gapp.hwnd, CGG.dlgapp[0].WndProc);
		SetPosDlg(CGG.gapp.hwnd, CGG.dlgapp[0].hWnd);
		SetWindowPos(CGG.dlgapp[0].hWnd, HWND_TOP, t_xy_dia.x, t_xy_dia.y, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE );
		}
	}
}
