#include "global.hpp"		// project

class CGameSaveControl CGameSaveControlOne;
class CUnpackPack CUnpackPackOne;
class CSaveInfo CSaveInfoOne;
class CSaveInfoWndControl CSaveInfoWndControlOne;
class CGlobal CGG;

///////////////

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

void CGlobal::Init(HINSTANCE hInstance)
{
	gapp.inst = hInstance;
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
	for (int i = 0; i < 10; i++){memset(&aCBSI[i], 0, sizeof(int)*2);}
	CloseWnd();
	for (int i = 0; i < ihwndCount; i++){hWndSI[i] = NULL;}
}

int CSaveInfoWndControl::CreateWnd(void)
{
for(int i = 0; i < 3; i++)
{
hWndSI[i] = CreateWindowEx(0, aWndSI[i].sClassName, aWndSI[i].sText, WS_CHILD | WS_VISIBLE, aWndSI[i].rectWnd.left, \
aWndSI[i].rectWnd.top, aWndSI[i].rectWnd.right, aWndSI[i].rectWnd.bottom, CGG.gapp.hwnd, NULL, CGG.gapp.inst, NULL);
}

return SUCCESS;
}

int CSaveInfoWndControl::CloseWnd(void)
{
	for (int i = 0; i < ihwndCount; i++)
	{
	if (hWndSI[i] != NULL)
	{
		DestroyWindow(hWndSI[i]);
		#ifdef DEBUG
		if (i==0) {Log.Log(L"\r\n");}
		Log.Log(L"DestroyWindow [%i] = %i, ", i, hWndSI[i]);
		#endif
	}
	}

return SUCCESS;
}

int OVERLORD::OpenFile(void)
{
	CGameSaveControlOne.ClearClass();
	CUnpackPackOne.ClearClass();
	
	int iTempValue = 0;
	
	iTempValue = CGameSaveControlOne.SelectGameFile();
	if (iTempValue != SUCCESS ) {Log.ErrorMsg(iTempValue); 
	#ifdef LOGGING
	Log.Log(L"SelectGameFile -%X", abs(iTempValue) ); 
	#endif
	return FAILURE;}
	
	iTempValue = CGameSaveControlOne.ReadGameFile();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
	Log.Log(L"ReadGameFile -%X", abs(iTempValue) ); 
	#endif
	return FAILURE;}
				
	if (CUnpackPackOne.lpGetBuffer(1)->capacity() > 1) {CUnpackPackOne.lpGetBuffer(1)->clear();}
	CUnpackPackOne.lpGetBuffer(1)->reserve(CGameSaveControlOne.iNumberReadByte);
	CUnpackPackOne.lpGetBuffer(1)->resize(CGameSaveControlOne.iNumberReadByte);

	*(CUnpackPackOne.lpGetBuffer(1)) = *(CGameSaveControlOne.lpGetBuffer());

	CGameSaveControlOne.ClearClass();	
	
	iTempValue = CUnpackPackOne.CheckFileSignature();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
	Log.Log(L"CheckFileSignature -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	iTempValue = CUnpackPackOne.Decompression();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
	Log.Log(L"Decompression -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	iTempValue = CUnpackPackOne.DefineTypeFile();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
		Log.Log(L"DefineTypeFile -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	switch (CUnpackPackOne.iFlagDefSave)
	{
		case SAVEINFO: PostMessage(CGG.gapp.hwnd, MSG_SAVEINFO, 0, 0); break;
		case SAVESLOT: PostMessage(CGG.gapp.hwnd, MSG_SAVESLOT, 0, 0); break;
	}

	return SUCCESS;
} 

int OVERLORD::CloseFile(void)
{
	CGameSaveControlOne.ClearClass();
	CUnpackPackOne.ClearClass();
	CSaveInfoOne.ClearClass();
	CSaveInfoWndControlOne.ClearClass();
	//Log.ClearClass();

	return SUCCESS;
}

int OVERLORD::SaveFile(void)
{
	int iTempValue = 0;
	CGameSaveControlOne.ClearClass();
	
	iTempValue = CGameSaveControlOne.SelectSaveGameFile();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
	Log.Log(L"SelectSaveGameFile -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	iTempValue = CSaveInfoOne.AssemblySI();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
	Log.Log(L"AssemblySI -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	
	/*
	iTempValue = CUnpackPackOne.Compression();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
	Log.Log(L"Compression -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	if (CGameSaveControlOne.lpGetBuffer()->capacity() > 1) {CGameSaveControlOne.lpGetBuffer()->clear();}
	CGameSaveControlOne.lpGetBuffer()->reserve( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );
	CGameSaveControlOne.lpGetBuffer()->resize( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );

	*(CGameSaveControlOne.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	CGameSaveControlOne.iNumberReadByte = CUnpackPackOne.lpGetDataInfo()->data.iLenFile;
	if (CGameSaveControlOne.iNumberReadByte < 50) return FAILURE;
	
	iTempValue = CGameSaveControlOne.WriteGameFile();
	if (iTempValue != SUCCESS) {Log.ErrorMsg(iTempValue);
	#ifdef LOGGING
	Log.Log(L"WriteGameFile -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	CGameSaveControlOne.ClearClass();*/
	return SUCCESS;
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
for(int l = 0; l < CUnpackPackOne.lpGetDataInfo()->data.iUnzip; l++)
{if (l == 0) {Log.Log(L"\r\n");} else {} ; Log.Log(L"%x, ", (*(CSaveInfoOne.lpGetBuffer()))[l] );}
#endif
	CUnpackPackOne.ClearClass();
	
	CSaveInfoOne.DisassemblySI();
	InvalidateRect(CSaveInfoWndControlOne.hWndSI[0], NULL, TRUE);
	
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
	CSaveInfoWndControlOne.aCBSI[num].iStatus = 1;
	CSaveInfoWndControlOne.aCBSI[num].iEnable = 1;
	
	return SUCCESS;
}

unsigned long int CGameSaveControl::GetiNumberReadByte(void)
{
	return iNumberReadByte;
}

int CGameSaveControl::SelectGameFile(void)
{
#ifdef WINAPIPROJECT

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
	
	if( GetOpenFileName(&ofn) != 0 ) {return SUCCESS;} else {return ERROR_OPENFILE;}
	
#else
#endif
}

int CGameSaveControl::SelectSaveGameFile(void)
{
#ifdef WINAPIPROJECT

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
	
	if( GetSaveFileName(&ofn) != 0 ) {return SUCCESS;} else {return ERROR_OPENSAVEFILE;}
#else
#endif
}

int CGameSaveControl::WriteGameFile(void)
{
	//Log.Log(L"ofn", ofn.);
	Log.Log(L"szFileTitle", szFileTitle);
	if (szFileTitle == 0) return ERROR_NOTFILESELECT;
	FILE *pFile;
	pFile = _wfopen (szFileTitle, L"wb");
	if (pFile == NULL) {fclose(pFile); return ERROR_OPENSAVEFILE;}
	
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

HDC CreateWnd (HWND hwnd)
{
CGG.hBitmap = LoadBitmap(CGG.gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
GetObject(CGG.hBitmap, sizeof(BITMAP), &CGG.bitmap);
HDC hDC = GetDC(hwnd);
if (hDC == NULL){PostQuitMessage(WM_NULL);}
HDC hDC2 = CreateCompatibleDC(hDC);
ReleaseDC(hwnd, hDC);
return hDC2;
}

void PaintWnd (HWND hwnd, HDC hDC2)
{
HGDIOBJ hSOOne;
PAINTSTRUCT ps;

HDC hDC = BeginPaint(hwnd, &ps);
hSOOne = SelectObject(hDC2, CGG.hBitmap);
BitBlt(hDC, 0, 0, CGG.bitmap.bmWidth, CGG.bitmap.bmHeight, hDC2, 0, 0, SRCCOPY);

DeleteObject(hSOOne);
EndPaint(hwnd, &ps);
}

BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
{
	classex.cbSize = sizeof(classex);
	classex.style = CS_HREDRAW | CS_VREDRAW ;
	classex.lpfnWndProc = Proc;
	classex.cbClsExtra = 0;
	classex.cbWndExtra = 0;
	classex.hInstance = hinstance;
	classex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(ID_APP_ICON));
	classex.hCursor = NULL;
	classex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	classex.lpszMenuName = MAKEINTRESOURCE(IDM_MENU);
	classex.lpszClassName = szClassName;
	classex.hIconSm = NULL;
	
	if (!RegisterClassEx(&classex)){return ERROR_GCLASSNOT;}
	
return SUCCESS;
}

BOOL RegClassGroupBox(WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
{
	classex.cbSize = sizeof(classex);
	classex.style = 0;
	classex.lpfnWndProc = Proc;
	classex.cbClsExtra = 0;
	classex.cbWndExtra = 0;
	classex.hInstance = hinstance;
	classex.hIcon = NULL;
	classex.hCursor = NULL;
	classex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	classex.lpszMenuName = NULL;
	classex.lpszClassName = szClassName;
	classex.hIconSm = NULL;
	
	if (!RegisterClassEx(&classex)){return ERROR_GCLASSNOT;}
	
return SUCCESS;
}

void CreateMainWindow (void) 
{
	RECT RECTmainwnd;
	WNDCLASSEX WndCMain;
	WNDCLASSEX WndCGroupBoxOne;
	WNDCLASSEX WndCGroupBoxTwo;
	WNDCLASSEX WndCGroupBoxThree;

	if (MainRegClass(WndCMain, CGG.gapp.WndProc, CGG.gapp.gclass, CGG.gapp.inst) != SUCCESS) return Log.ErrorMsg(ERROR_GCLASSNOT);
	
	if (RegClassGroupBox(WndCGroupBoxOne, GroupBoxWndProcOne, CSaveInfoWndControlOne.aWndSI[0].sClassName, CGG.gapp.inst) != SUCCESS) return Log.ErrorMsg(ERROR_GCLASSNOT); // переделать
	if (RegClassGroupBox(WndCGroupBoxTwo, GroupBoxWndProcTwo, CSaveInfoWndControlOne.aWndSI[1].sClassName, CGG.gapp.inst) != SUCCESS) return Log.ErrorMsg(ERROR_GCLASSNOT); // переделать
	if (RegClassGroupBox(WndCGroupBoxThree, GroupBoxWndProcThree, CSaveInfoWndControlOne.aWndSI[2].sClassName, CGG.gapp.inst) != SUCCESS) return Log.ErrorMsg(ERROR_GCLASSNOT); // переделать
	
	//// Размер клиентской области ////
	CGG.scwnd.x = GetSystemMetrics(SM_CXSCREEN); //1920
	CGG.scwnd.y = GetSystemMetrics(SM_CYSCREEN); //1080
	CGG.szwnd.x = (1280/2); //640 минимум
	CGG.szwnd.y = (1024/2); //512 минимум
	CGG.pwnd.x = (CGG.scwnd.x-CGG.szwnd.x)/2; //(1920-640)/2=640
	CGG.pwnd.y = (CGG.scwnd.y-CGG.szwnd.y)/2; //(1080-512)/2=284
	RECTmainwnd.left = CGG.pwnd.x; //
	RECTmainwnd.right = CGG.pwnd.x + CGG.szwnd.x; //
	RECTmainwnd.top = CGG.pwnd.y; //
	RECTmainwnd.bottom = CGG.pwnd.y + CGG.szwnd.y;
	AdjustWindowRectEx(&RECTmainwnd, WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, TRUE, 0);
	CGG.szwnd.x = RECTmainwnd.right-RECTmainwnd.left;
	CGG.szwnd.y = RECTmainwnd.bottom-RECTmainwnd.top;
	///////////////////////////////////////////////////////////////////
	
	CGG.gapp.hwnd = CreateWindowEx(0, CGG.gapp.gclass, CGG.gapp.gwnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, \
	CGG.pwnd.x, CGG.pwnd.y, CGG.szwnd.x, CGG.szwnd.y, NULL, NULL, CGG.gapp.inst, NULL);

	if (CGG.gapp.hwnd == NULL){Log.ErrorMsg(ERROR_GWNDNOT);}
	ShowWindow(CGG.gapp.hwnd, SW_SHOW);
}

void SetPosDlg(HWND hwnd, HWND dia)
{
RECT t_poswnd;
RECT t_posdia;
GetWindowRect(hwnd, &t_poswnd);
GetWindowRect(dia, &t_posdia);
CGG.t_xy_dia.x = t_posdia.right - t_posdia.left;
CGG.t_xy_dia.y = t_posdia.bottom - t_posdia.top;
t_poswnd.left += ((t_poswnd.right-t_poswnd.left-CGG.t_xy_dia.x)/2);
t_poswnd.top += ((t_poswnd.bottom-t_poswnd.top-CGG.t_xy_dia.y)/2);

CGG.t_xy_dia.x = t_poswnd.left;
CGG.t_xy_dia.y = t_poswnd.top;
}

void DlgInit(int numdlg)
{
	switch (numdlg)
	{
		case DLG_ABOUT:
		{
		CGG.dlgapp[0].hWnd = CreateDialog(CGG.gapp.inst, MAKEINTRESOURCE(IDDLG_ABOUT), CGG.gapp.hwnd, CGG.dlgapp[0].WndProc);
		SetPosDlg(CGG.gapp.hwnd, CGG.dlgapp[0].hWnd);
		SetWindowPos(CGG.dlgapp[0].hWnd, HWND_TOP, CGG.t_xy_dia.x, CGG.t_xy_dia.y, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE );
		}
	}
}
