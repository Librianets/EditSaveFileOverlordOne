#include "global.hpp"		// project

class CGameSaveControl CGameSaveControlOne;
class CUnpackPack CUnpackPackOne;
class CSaveInfo CSaveInfoOne;
class CSaveInfoWndControl CSaveInfoWndControlOne;
class CGlobal CGG;
//class CLogging Log;

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

int CGlobal::Init(HINSTANCE hInstance)
{
	gapp.inst = hInstance;
	if (MainRegClass(WndCExMain, CGG.gapp.WndProc, CGG.gapp.gclass, CGG.gapp.inst) != SUCCESS) return ERROR_GCLASSNOT;
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

if (RegClassGroupBox(WndCExGroupBoxOne, GroupBoxWndProcOne, aWndSI[0].sClassName, CGG.gapp.inst) != SUCCESS) {errormsg(ERROR_GCLASSNOT, APP);} // переделать
if (RegClassGroupBox(WndCExGroupBoxTwo, GroupBoxWndProcTwo, aWndSI[1].sClassName, CGG.gapp.inst) != SUCCESS) {errormsg(ERROR_GCLASSNOT, APP);} // переделать
if (RegClassGroupBox(WndCExGroupBoxThree, GroupBoxWndProcThree, aWndSI[2].sClassName, CGG.gapp.inst) != SUCCESS) {errormsg(ERROR_GCLASSNOT, APP);} // переделать

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
		if (i==0) {info(L"\r\n", L"");}
		info(L"DestroyWindow [%i] = %i, ", i, hWndSI[i]);
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
	if (iTempValue != SUCCESS ) {errormsg(iTempValue, APP); 
	info(L"SelectGameFile -%X", abs(iTempValue) ); 
	return FAILURE;}
	
	iTempValue = CGameSaveControlOne.ReadGameFile();
	if (iTempValue != SUCCESS) {errormsg(iTempValue, APP);
	info(L"ReadGameFile -%X", abs(iTempValue) ); 
	return FAILURE;}
				
	if (CUnpackPackOne.lpGetBuffer(1)->capacity() > 1) {CUnpackPackOne.lpGetBuffer(1)->clear();}
	CUnpackPackOne.lpGetBuffer(1)->reserve(CGameSaveControlOne.iNumberReadByte);
	CUnpackPackOne.lpGetBuffer(1)->resize(CGameSaveControlOne.iNumberReadByte);

	*(CUnpackPackOne.lpGetBuffer(1)) = *(CGameSaveControlOne.lpGetBuffer());

	CGameSaveControlOne.ClearClass();	
	
	iTempValue = CUnpackPackOne.CheckFileSignature();
	if (iTempValue != SUCCESS) {errormsg(iTempValue, PACKLIB);
	info(L"CheckFileSignature -%X", abs(iTempValue) );
	return FAILURE;}
	
	iTempValue = CUnpackPackOne.Decompression();
	if (iTempValue != SUCCESS) {errormsg(iTempValue, PACKLIB);
	info(L"Decompression -%X", abs(iTempValue) );
	return FAILURE;}
	
	iTempValue = CUnpackPackOne.DefineTypeFile();
	if (iTempValue != SUCCESS) {errormsg(iTempValue, PACKLIB);
		info(L"DefineTypeFile -%X", abs(iTempValue) );
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
	if (iTempValue != SUCCESS) {errormsg(iTempValue, APP);
	info(L"SelectSaveGameFile -%X", abs(iTempValue) );
	return FAILURE;}
	
	iTempValue = CSaveInfoOne.AssemblySI();
	if (iTempValue != SUCCESS) {errormsg(iTempValue, APP);
	info(L"AssemblySI -%X", abs(iTempValue) );
	return FAILURE;}
	
	
	/*
	iTempValue = CUnpackPackOne.Compression();
	if (iTempValue != SUCCESS) {errormsg(iTempValue);
	#ifdef LOGGING
	info(L"Compression -%X", abs(iTempValue) );
	#endif
	return FAILURE;}
	
	if (CGameSaveControlOne.lpGetBuffer()->capacity() > 1) {CGameSaveControlOne.lpGetBuffer()->clear();}
	CGameSaveControlOne.lpGetBuffer()->reserve( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );
	CGameSaveControlOne.lpGetBuffer()->resize( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );

	*(CGameSaveControlOne.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	CGameSaveControlOne.iNumberReadByte = CUnpackPackOne.lpGetDataInfo()->data.iLenFile;
	if (CGameSaveControlOne.iNumberReadByte < 50) return FAILURE;
	
	iTempValue = CGameSaveControlOne.WriteGameFile();
	if (iTempValue != SUCCESS) {errormsg(iTempValue);
	#ifdef LOGGING
	info(L"WriteGameFile -%X", abs(iTempValue) );
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
	
info(L"\r\n lpGetDataInfo()->iUnzip = %i", CUnpackPackOne.lpGetDataInfo()->data.iUnzip);
info(L"\r\n SaveInfoStructOne.header.numbersize = %i", CSaveInfoOne.SaveInfoStructOne.header.numbersize);
for(int l = 0; l < CUnpackPackOne.lpGetDataInfo()->data.iUnzip; l++)
{if (l == 0) {info(L"\r\n", L"");} else {} ; info(L"%x, ", (*(CSaveInfoOne.lpGetBuffer()))[l] );}

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
}

int CGameSaveControl::SelectSaveGameFile(void)
{
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
	
	if( GetSaveFileName(&ofn) != 0 ) {return SUCCESS;} else {return ERROR_SAVEFILE;}
}

int CGameSaveControl::WriteGameFile(void)
{
	//info(L"ofn", ofn.);
	info(L"szFileTitle", szFileTitle);
	if (szFileTitle == 0) return ERROR_SAVEFILE;
	FILE *pFile;
	pFile = _wfopen (szFileTitle, L"wb");
	if (pFile == NULL) {fclose(pFile); return ERROR_SAVEFILE;}
	
	fseek(pFile, 0, SEEK_SET);
	if ( (iNumberReadByte > MAXSIZEFILE) | (iNumberReadByte <= 0) ) {fclose(pFile); return ERROR_LIMITMAXSIZE;}
	if( iNumberReadByte != fwrite(&aBufferRead[0x0], sizeof(char), iNumberReadByte, pFile) ) {fclose(pFile); return ERROR_FILESIZE;}
	fclose(pFile);
	
	return SUCCESS;
}

int CGameSaveControl::ReadGameFile(void)
{
	if (szFileTitle == 0) return ERROR_OPENFILE;
	
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

HDC CGlobal::CreateWnd (HWND hwnd)
{
CGG.hBitmap = LoadBitmap(CGG.gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
GetObject(CGG.hBitmap, sizeof(BITMAP), &CGG.bitmap);
HDC hDC = GetDC(hwnd);
if (hDC == NULL){PostQuitMessage(WM_NULL);}
HDC hDC2 = CreateCompatibleDC(hDC);
ReleaseDC(hwnd, hDC);
return hDC2;
}

void CGlobal::PaintWnd (HWND hwnd, HDC hDC2)
{
HGDIOBJ hSOOne;
PAINTSTRUCT ps;

HDC hDC = BeginPaint(hwnd, &ps);
hSOOne = SelectObject(hDC2, CGG.hBitmap);
BitBlt(hDC, 0, 0, CGG.bitmap.bmWidth, CGG.bitmap.bmHeight, hDC2, 0, 0, SRCCOPY);

DeleteObject(hSOOne);
EndPaint(hwnd, &ps);
}

BOOL CGlobal::MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
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

BOOL CSaveInfoWndControl::RegClassGroupBox(WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
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




HWND CGlobal::CreateMainWndApp (void) 
{
	RECT RECTmainwnd;
	/*uxtheme.h*/
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_STANDARD_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES;
	InitCommonControlsEx(&icex);
	
	//// Размер клиентской области ////
	POINT metric;
	POINT stdsize;
	POINT sizewndapp;
	
	metric.x = GetSystemMetrics(SM_CXSCREEN); //1920 
	metric.y = GetSystemMetrics(SM_CYSCREEN); //1080
	stdsize.x = iSizeWndX;
	stdsize.y = iSizeWndY; //512 минимум
	sizewndapp.x = (metric.x-stdsize.x)/2; //(1920-640)/2=640
	sizewndapp.y = (metric.y-stdsize.y)/2; //(1080-512)/2=284
	RECTmainwnd.left = sizewndapp.x; //
	RECTmainwnd.right = sizewndapp.x + stdsize.x; //
	RECTmainwnd.top = sizewndapp.y; //
	RECTmainwnd.bottom = sizewndapp.y + stdsize.y;
	AdjustWindowRectEx(&RECTmainwnd, WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, TRUE, 0);
	stdsize.x = RECTmainwnd.right-RECTmainwnd.left;
	stdsize.y = RECTmainwnd.bottom-RECTmainwnd.top;
	///////////////////////////////////////////////////////////////////
	
	HWND hwnd;
	hwnd = CreateWindowEx(0, CGG.gapp.gclass, CGG.gapp.gwnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, \
	sizewndapp.x, sizewndapp.y, stdsize.x, stdsize.y, \
	NULL, NULL, CGG.gapp.inst, NULL);
	return hwnd;
}

void CGlobal::ShowWnd(HWND hWnd)
{
	ShowWindow(hWnd, SW_SHOW);
}

int CGlobal::SetPosDlg(HWND hwnd, HWND dia, POINT *pt)
{
if (pt == NULL || hwnd == NULL || dia == NULL) return -0x1;
RECT t_poswnd;
RECT t_posdia;
GetWindowRect(hwnd, &t_poswnd);
GetWindowRect(dia, &t_posdia);
pt->x = t_posdia.right - t_posdia.left;
pt->y = t_posdia.bottom - t_posdia.top;
t_poswnd.left += ((t_poswnd.right-t_poswnd.left-pt->x)/2);
t_poswnd.top += ((t_poswnd.bottom-t_poswnd.top-pt->y)/2);

pt->x = t_poswnd.left;
pt->y = t_poswnd.top;
return 0;
}

void CGlobal::DlgInit(int numdlg)
{
	switch (numdlg)
	{
		case DLG_ABOUT:
		{
		CGG.dlgapp[0].hWnd = CreateDialog(CGG.gapp.inst, MAKEINTRESOURCE(IDDLG_ABOUT), CGG.gapp.hwnd, CGG.dlgapp[0].WndProc);
		POINT dia_pos_temp;
		CGG.SetPosDlg(CGG.gapp.hwnd, CGG.dlgapp[0].hWnd, &dia_pos_temp);
		SetWindowPos(CGG.dlgapp[0].hWnd, HWND_TOP, dia_pos_temp.x, dia_pos_temp.y, 0, 0, SWP_SHOWWINDOW|SWP_NOSIZE );
		}
	}
}



////////////////////////////////////////////////////////////////////////////////////////
////////////////////// TEST TEST TEST TEST TEST TEST TEST TEST TEST ////////////////////


LRESULT WINAPI TestWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;	HGDIOBJ hSOOne;	HDC hWndGBOne;
	
	switch (msg)
	{
		
		case WM_CREATE: { }break;
		case WM_PAINT:	
		{
			HDC hDC = BeginPaint(hWnd, &ps);
			Graphics g(hDC);
			g.SetPageUnit(UnitPixel);
			RectF bounds(0, 0, float(800.0), float(400.0));
			Image bg(L"logologo.png");
			g.DrawImage(&bg, bounds);
			EndPaint(hWnd, &ps);
		}break;
		
		case WM_CTLCOLORBTN: {} break;
		case WM_CTLCOLORSTATIC: {} break;
		case WM_ERASEBKGND: {} break;
		case WM_TIMER: {} break;
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDI_EXIT: 				PostQuitMessage(WM_DESTROY); 	break;
			}
		}
		}break;
		
		default: return (DefWindowProc(hWnd, msg, wParam, lParam));
	}
}

BOOL TestClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
{
	classex.cbSize = sizeof(classex);
	classex.style = CS_HREDRAW | CS_VREDRAW ;
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