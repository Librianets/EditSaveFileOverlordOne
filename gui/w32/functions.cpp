#include <windows.h> 		// WINDOWS
#include <iostream>			// Language C++
#include <vector>			// Language C++
using std::vector;

#include "packunpack.hpp"	// project
using OESD::CUnpackPack;

#include "saveinfo.hpp"		// project
#include "resource.hpp"		// project

#include "proc.hpp"			// project
#include "global.hpp"		// project

#include "debug.hpp"		// project
#include "logging.hpp"		// project

#include "functions.hpp" 	// project


class CGameSaveControl CGameSaveControlOne;
class CUnpackPack CUnpackPackOne;
class CSaveInfoOverlordOne CSIOO;
class CSaveInfoWndControl CSIWC;
class COverlordApp COA;

//////////////////////////////////////////////////////
//////////////////	COverlordApp	//////////////////
//////////////////////////////////////////////////////
COverlordApp::COverlordApp()
{
	gapp.inst = NULL;
	gapp.hwnd = NULL;
	gapp.menu = NULL;
	
	gapp.gclass = sg_WndClass;
	gapp.gwnd = sg_Wnd;
	gapp.WndProc = *MainWndProc;

	dlgapp[0].WndProc = *AboutWndProc;
}

COverlordApp::~COverlordApp()
{
	
}

void COverlordApp::ClearClass(void)
{
	memset( &gapp, 0, sizeof(AppData) );
	for(int i = 0; i < 5; i++) {memset( &dlgapp[i], 0, sizeof(DataWnd) );}
}

int COverlordApp::Init(HINSTANCE hInstance)
{
	gapp.inst = hInstance;
	if (MainRegClass(WndCExMain, MainWndProc, COA.gapp.gclass, COA.gapp.inst) != 0x00) return ERROR_GCLASSNOT;
	if (CSIWC.RegClassGroupBox(CSIWC.WndCExGroupBoxOne, ProcAppGroupBoxSI, L"GroupBoxSI", COA.gapp.inst) != 0x00) return ERROR_GCLASSNOT;

}

HDC COverlordApp::CreateWnd (HWND hwnd)
{
COA.hBitmap = LoadBitmap(COA.gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
GetObject(COA.hBitmap, sizeof(BITMAP), &COA.bitmap);
HDC hDC = GetDC(hwnd);
if (hDC == NULL){PostQuitMessage(WM_NULL);}
HDC hDC2 = CreateCompatibleDC(hDC);
ReleaseDC(hwnd, hDC);
return hDC2;
}

void COverlordApp::PaintWnd (HWND hwnd, HDC hDC2)
{
HGDIOBJ hSOOne;
PAINTSTRUCT ps;

HDC hDC = BeginPaint(hwnd, &ps);
hSOOne = SelectObject(hDC2, COA.hBitmap);
BitBlt(hDC, 0, 0, COA.bitmap.bmWidth, COA.bitmap.bmHeight, hDC2, 0, 0, SRCCOPY);

DeleteObject(hSOOne);
EndPaint(hwnd, &ps);
}

BOOL COverlordApp::MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
{
	classex.cbSize = sizeof(classex);
	classex.style = CS_HREDRAW | CS_VREDRAW ;
	classex.lpfnWndProc = Proc;
	classex.cbClsExtra = 0;
	classex.cbWndExtra = 0;
	classex.hInstance = hinstance;
	classex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(ID_APP_ICON));
	classex.hCursor = NULL;
	classex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	classex.lpszMenuName = MAKEINTRESOURCE(IDM_MENU);
	classex.lpszClassName = szClassName;
	classex.hIconSm = NULL;
	
	if (!RegisterClassEx(&classex)){return ERROR_GCLASSNOT;}
	
return 0x00;
}

HWND COverlordApp::CreateMainWndApp (void) 
{
	RECT RECTmainwnd;
	/*uxtheme.h*/
	//INITCOMMONCONTROLSEX icex;
	//icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	//icex.dwICC = ICC_STANDARD_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES;
	//InitCommonControlsEx(&icex);
	
	//// Размер клиентской области ////
	POINT metric;
	POINT stdsize;
	POINT sizewndapp;
	
	metric.x = GetSystemMetrics(SM_CXSCREEN);//1920 
	metric.y = GetSystemMetrics(SM_CYSCREEN);//1080
	stdsize.x = iSizeWndX;
	stdsize.y = iSizeWndY;//512 минимум
	sizewndapp.x = (metric.x-stdsize.x)/2;//(1920-640)/2=640
	sizewndapp.y = (metric.y-stdsize.y)/2;//(1080-512)/2=284
	RECTmainwnd.left = sizewndapp.x;//
	RECTmainwnd.right = sizewndapp.x + stdsize.x;//
	RECTmainwnd.top = sizewndapp.y;//
	RECTmainwnd.bottom = sizewndapp.y + stdsize.y;
	AdjustWindowRectEx(&RECTmainwnd, WS_CAPTION | WS_CLIPCHILDREN | WS_POPUPWINDOW | WS_MINIMIZEBOX, TRUE, 0);
	stdsize.x = RECTmainwnd.right-RECTmainwnd.left;
	stdsize.y = RECTmainwnd.bottom-RECTmainwnd.top;
	///////////////////////////////////////////////////////////////////
	
	HWND hwnd;
	hwnd = CreateWindowEx(0, COA.gapp.gclass, COA.gapp.gwnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX | WS_CLIPCHILDREN, \
	sizewndapp.x, sizewndapp.y, stdsize.x, stdsize.y, \
	NULL, NULL, COA.gapp.inst, NULL);
	return hwnd;
}

void COverlordApp::ShowWnd(HWND hWnd)
{
	ShowWindow(hWnd, SW_SHOW);
}

int COverlordApp::SetPosDlg(HWND hwnd, HWND dia, POINT *pt)
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

void COverlordApp::DlgInit(int numdlg)
{
	switch (numdlg)
	{
		case DLG_ABOUT:
		{
		dlgapp[0].hWnd = CreateDialog(gapp.inst, MAKEINTRESOURCE(IDDLG_ABOUT), gapp.hwnd, dlgapp[0].WndProc);
		POINT dia_pos_temp;
		SetPosDlg(gapp.hwnd, dlgapp[0].hWnd, &dia_pos_temp);
		SetWindowPos(dlgapp[0].hWnd, HWND_TOP, dia_pos_temp.x, dia_pos_temp.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE );
		}break;
		//default:
	}
}

//////////////////////////////////////////////////////
////////////////	CSaveInfoWndControl	//////////////
//////////////////////////////////////////////////////

CSaveInfoWndControl::CSaveInfoWndControl()
{
	//ClearClass();
}

CSaveInfoWndControl::~CSaveInfoWndControl()
{
	ClearClass();
}
	
void CSaveInfoWndControl::ClearClass(void)
{
	for (int i = 0;i < 10;i++)
	{
		memset(&aCBSI[i], 0, sizeof(int)*2);
		memset(&iPosSaveInCB[i], 0, sizeof(int));
	}
	CloseWnd();
}

int CSaveInfoWndControl::CreateWnd(void)
{

hWndSI[0] = CreateWindowEx(WS_EX_TRANSPARENT, L"GroupBoxSI", L"", WS_CHILD , \
0, 0, COA.iSizeWndX, COA.iSizeWndY, COA.gapp.hwnd, NULL, COA.gapp.inst, NULL);
ShowWindow(hWndSI[0], SW_SHOW);

for(int i = 0; i < 10; i++)
{
aCBSI[i].hWnd = CreateWindowEx(0, L"BUTTON", aCBSI[i].sText, BS_3STATE | WS_CHILD , \
aCBSI[i].rectCB.left, aCBSI[i].rectCB.top, aCBSI[i].rectCB.right, aCBSI[i].rectCB.bottom, \
hWndSI[0], NULL, COA.gapp.inst, NULL);

//SetWindowLongPtr(aCBSI[i].hWnd, GWLP_WNDPROC, (LONG_PTR) ProcAppCheckBox); 
}
for(int i = 0; i < 10; i++) {ShowWindow(aCBSI[i].hWnd, SW_SHOW);} // на потом

hWndSI[1] = CreateWindowEx(WS_EX_TRANSPARENT, L"COMBOBOX", L"", WS_CHILD | CBS_DROPDOWNLIST, \
aWndSI[3].rectWnd.left, aWndSI[3].rectWnd.top, aWndSI[3].rectWnd.right, aWndSI[3].rectWnd.bottom, \
hWndSI[0], NULL, COA.gapp.inst, NULL);
ShowWindow(hWndSI[1], SW_SHOW);

hWndSI[2] = CreateWindowEx(WS_EX_TRANSPARENT, L"EDIT", L"", WS_CHILD | ES_LEFT | ES_MULTILINE | ES_READONLY, \
aWndSI[4].rectWnd.left, aWndSI[4].rectWnd.top, aWndSI[4].rectWnd.right, aWndSI[4].rectWnd.bottom, \
hWndSI[0], NULL, COA.gapp.inst, NULL);
ShowWindow(hWndSI[2], SW_SHOW);

//SetWindowPos (hWndSI[0], HWND_TOPMOST, 0, 0, 0, 0, SWP_NOOWNERZORDER);
//SetLayeredWindowAttributes(hTest, RGB(240, 240, 240), 0, LWA_COLORKEY);
return 0x00;
}

int CSaveInfoWndControl::CloseWnd(void)
{
	for (int i = 0; i < 10; i++)
	{
	if (aCBSI[i].hWnd != NULL)
	{
		DestroyWindow(aCBSI[i].hWnd);
		aCBSI[i].hWnd = NULL;
		debug(L"\r\nDestroyWindow aCBSI[%i]", i);
	}
	}
	
	for (int i = 0; i < 5; i++)
	{
	if (hWndSI[i] != NULL)
	{
		DestroyWindow(hWndSI[i]);
		hWndSI[i] = NULL;
		debug(L"\r\nDestroyWindow hWndSI[%i]", i);
	}
	}
	
return 0x00;
}

int CSaveInfoWndControl::SetWndLong(int num)
{
	SetWindowLongPtr(aCBSI[num].hWnd, GWL_STYLE, (GetWindowLongPtr(aCBSI[num].hWnd, GWL_STYLE) - BS_3STATE) | BS_AUTOCHECKBOX);
	SendMessage(aCBSI[num].hWnd, BM_SETCHECK, BM_SETCHECK, 0);

	iPosSaveInCB[num] = SendMessage(hWndSI[1], CB_ADDSTRING , 0, (LPARAM)aCBSI[num].sText);
	return 0x00;
}

BOOL CSaveInfoWndControl::RegClassGroupBox(WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
{
	classex.cbSize = sizeof(classex);
	classex.style = CS_PARENTDC;
	classex.lpfnWndProc = Proc;
	classex.cbClsExtra = 0;
	classex.cbWndExtra = 0;
	classex.hInstance = hinstance;
	classex.hIcon = NULL;
	classex.hCursor = NULL;
	classex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	classex.lpszMenuName = NULL;
	classex.lpszClassName = szClassName;
	classex.hIconSm = NULL;
	
	if (!RegisterClassEx(&classex)){return ERROR_GCLASSNOT;}
	
return 0x00;
}

int CSaveInfoWndControl::RefreshAlternativeInfoSI(int iSaveSelect)
{
	debug(L"\r\n iSaveSelect = %i", iSaveSelect);
	
	if (iSaveSelect == CB_ERR) {return -1;}
	/*int pos = 0;
	for(int l = 0; l < 10; l++)
	{
		if (iSaveSelect == iPosSaveInCB[l])
		{
			pos = l;
			break;		
		}
	}
	if (pos == 0 && iSaveSelect != 0) {return -1;}*/
	
	//// эм.... как то не так реализовалось... потом доработать и перенести в другой класс
	
	debug(L"\r\n CUnpackPackOne.iFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);
	if (CUnpackPackOne.iFlagDefSaveLang == LANGRU)
	{CSIOO.StringConvert(iSaveSelect, 1);} else {CSIOO.StringConvert(iSaveSelect, 0);}
	
	//debug(L"\r\n iFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);
	
	SendMessage(hWndSI[2], WM_SETTEXT, 0, (LPARAM)L"");
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)L"Локация=");
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)CSIOO.aTempOne);
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)L"\r\n");
	//debug(L"\r\n CUnpackPackOne.iFlagDefSave = %02X", CUnpackPackOne.iFlagDefSave);
	//debug(L"\r\n CUnpackPackOne.iFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);
	
	return 0;
}

//////////////////////////////////////////////////////
////////////////////	OVERLORD	/////////////////
//////////////////////////////////////////////////////

int OVERLORD::OpenFile(void)
{
	CGameSaveControlOne.ClearClass();
	CUnpackPackOne.ClearClass();
	
	int iTempValue = 0;
	
	iTempValue = CGameSaveControlOne.SelectGameFile();
	if (iTempValue != 0x00 ) {errormsg(iTempValue, APP);
	info(L"SelectGameFile -%X", abs(iTempValue) );
	return -0x01;}
	
	iTempValue = CGameSaveControlOne.ReadGameFile();
	if (iTempValue != 0x00) {errormsg(iTempValue, APP);
	info(L"ReadGameFile -%X", abs(iTempValue) );
	return -0x01;}
				
	//if (CUnpackPackOne.lpGetBuffer(1)->capacity() > 1) {CUnpackPackOne.lpGetBuffer(1)->clear();}
	//CUnpackPackOne.lpGetBuffer(1)->reserve(CGameSaveControlOne.iNumberReadByte);
	CUnpackPackOne.lpGetBuffer(1)->resize(CGameSaveControlOne.iNumberReadByte);

	*(CUnpackPackOne.lpGetBuffer(1)) = *(CGameSaveControlOne.lpGetBuffer());

	CGameSaveControlOne.ClearClass();	
	
	iTempValue = CUnpackPackOne.CheckFileSignature();
	if (iTempValue != 0x00) {errormsg(iTempValue, PACKLIB);
	info(L"CheckFileSignature -%X", abs(iTempValue) );
	return -0x01;}
	
	iTempValue = CUnpackPackOne.Decompression();
	if (iTempValue != 0x00) {errormsg(iTempValue, PACKLIB);
	info(L"Decompression -%X", abs(iTempValue) );
	return -0x01;}
	
//	debug(L"\r\n %02X", CUnpackPackOne.aBufferOne[CUnpackPackOne.UnionDataInfoOne.data.iUnzip-1]);
//	debug(L"\r\n %02X", CUnpackPackOne.aBufferOne[CUnpackPackOne.UnionDataInfoOne.data.iUnzip-2]);
//	debug(L"\r\n %02X", CUnpackPackOne.aBufferOne[CUnpackPackOne.UnionDataInfoOne.data.iUnzip-3]);

	iTempValue = CUnpackPackOne.DefineTypeFile();
	if (iTempValue != 0x00) {errormsg(iTempValue, PACKLIB);
		info(L"DefineTypeFile -%X", abs(iTempValue) );
	return -0x01;}
	
	//debug(L"\r\n CUnpackPackOne.iFlagDefSave = %02X", CUnpackPackOne.iFlagDefSave);
	//debug(L"\r\n CUnpackPackOne.iFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);

	
	switch (CUnpackPackOne.iFlagDefSave)
	{
		case SAVEINFO: PostMessage(COA.gapp.hwnd, MSG_SAVEINFO, 0, 0);break;
		case SAVESLOT: PostMessage(COA.gapp.hwnd, MSG_SAVESLOT, 0, 0);break;
	}

	return 0x00;
} 

int OVERLORD::CloseFile(void)
{
	CGameSaveControlOne.ClearClass();
	CUnpackPackOne.ClearClass();
	CSIOO.ClearClass();
	CSIWC.ClearClass();

	return 0x00;
}

int OVERLORD::SaveFile(void)
{
	int iTempValue = 0;
	CGameSaveControlOne.ClearClass();
	
	iTempValue = CGameSaveControlOne.SelectSaveGameFile();
	if (iTempValue != 0x00) {errormsg(iTempValue, APP);
	info(L"SelectSaveGameFile -%X", abs(iTempValue) );
	return -0x01;}
	
	iTempValue = CSIOO.AssemblySI();
	if (iTempValue != 0x00) {errormsg(iTempValue, APP);
	info(L"AssemblySI -%X", abs(iTempValue) );
	return -0x01;}
	
	
	/*
	iTempValue = CUnpackPackOne.Compression();
	if (iTempValue != 0x00) {errormsg(iTempValue);
	#ifdef LOGGING
	info(L"Compression -%X", abs(iTempValue) );
	#endif
	return -0x01;}
	
	if (CGameSaveControlOne.lpGetBuffer()->capacity() > 1) {CGameSaveControlOne.lpGetBuffer()->clear();}
	CGameSaveControlOne.lpGetBuffer()->reserve( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );
	CGameSaveControlOne.lpGetBuffer()->resize( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );

	*(CGameSaveControlOne.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	CGameSaveControlOne.iNumberReadByte = CUnpackPackOne.lpGetDataInfo()->data.iLenFile;
	if (CGameSaveControlOne.iNumberReadByte < 50) return -0x01;
	
	iTempValue = CGameSaveControlOne.WriteGameFile();
	if (iTempValue != 0x00) {errormsg(iTempValue);
	#ifdef LOGGING
	info(L"WriteGameFile -%X", abs(iTempValue) );
	#endif
	return -0x01;}
	
	CGameSaveControlOne.ClearClass();*/
	return 0x00;
}

int OVERLORD::SaveSlot(void) 
{
	
return 0x00;
}

int OVERLORD::SaveInfo(void)
{
	CSIOO.ClearClass();
	CSIWC.ClearClass();
	
	CSIWC.CreateWnd();
	
	CSIOO.SaveInfoStructOne.header.numbersize = CUnpackPackOne.lpGetDataInfo()->data.iUnzip;
	CSIOO.lpGetBuffer()->reserve(CSIOO.SaveInfoStructOne.header.numbersize);
	*(CSIOO.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	
debug(L"\r\n lpGetDataInfo()->iUnzip = %i", CUnpackPackOne.lpGetDataInfo()->data.iUnzip);
debug(L"\r\n SaveInfoStructOne.header.numbersize = %i", CSIOO.SaveInfoStructOne.header.numbersize);
#ifdef DEBUGMODE
for(int l = 0;l < CUnpackPackOne.lpGetDataInfo()->data.iUnzip;l++)
{if (l == 0) {debug(L"\r\n", L"");} else {} ;debug(L"%x, ", (*(CSIOO.lpGetBuffer()))[l] );}
#endif
	CUnpackPackOne.ClearClass();
	
	CSIOO.DisassemblySI();
	
debug(L"\r\nCSIOO.iFlagSaveCount = %i", CSIOO.iFlagSaveCount);
#ifdef DEBUGMODE
for(int l = 0;l < 10;l++)
{debug(L"\r\n iFlagSaveNum[%i]=%i", l, CSIOO.SaveInfoStructOne.data.iFlagSaveNum[l])}
#endif

	for (int i = 0; i < 10; i++)
	{
		if (CSIOO.SaveInfoStructOne.data.iFlagSaveNum[i] == 1)
		{
		CSIWC.SetWndLong(i);
		}
	}
	
	for(int i = 0; i < 10; i++)
	{
		debug(L"\r\n iPosSaveInCB[%i] = %i", i, CSIWC.iPosSaveInCB[i]);
	}
	
/*	for(int i = 0; i < 10; i++)
	{
	aCBSI[i].hWnd
	SetWindowLongPtr(aCBSI[i].hWnd, GWLP_WNDPROC, (LONG_PTR) ProcAppCheckBox); 
	}*/
	//InvalidateRect(CSIWC.hWndSI[0], NULL, TRUE);
	
return 0x00;
}

//////////////////////////////////////////////////////
/////////////////	CGameSaveControl	//////////////
//////////////////////////////////////////////////////

CGameSaveControl::~CGameSaveControl()
{
	ClearClass();
	//aBufferRead.~vector();
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
	
	if( GetOpenFileName(&ofn) != 0 ) {return 0x00;} else {return ERROR_OPENFILE;}
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
	
	if( GetSaveFileName(&ofn) != 0 ) {return 0x00;} else {return ERROR_SAVEFILE;}
}

int CGameSaveControl::WriteGameFile(void)
{
	//info(L"ofn", ofn.);
	info(L"szFileTitle", szFileTitle);
	if (szFileTitle == 0) return ERROR_SAVEFILE;
	FILE *pFile;
	pFile = _wfopen (szFileTitle, L"wb");
	if (pFile == NULL) {fclose(pFile);return ERROR_SAVEFILE;}
	
	fseek(pFile, 0, SEEK_SET);
	if ( (iNumberReadByte > MAXSIZEFILE) | (iNumberReadByte <= 0) ) {fclose(pFile);return ERROR_LIMITMAXSIZE;}
	if( iNumberReadByte != fwrite(&aBufferRead[0x0], sizeof(char), iNumberReadByte, pFile) ) {fclose(pFile);return ERROR_FILESIZE;}
	fclose(pFile);
	
	return 0x00;
}

int CGameSaveControl::ReadGameFile(void)
{
	if (szFileTitle == 0) return ERROR_OPENFILE;
	
	FILE *pFile;
	pFile = _wfopen (szFileTitle, L"rb");
	if (pFile == NULL) {fclose(pFile);return ERROR_OPENFILE;}
	
	fseek(pFile, 0, SEEK_END);

	iNumberReadByte = ftell(pFile);
	if (iNumberReadByte == -1L) {fclose(pFile);return ERROR_FILESIZE;}
	if ( (iNumberReadByte > MAXSIZEFILE) | (iNumberReadByte <= 0) ) {fclose(pFile);return ERROR_LIMITMAXSIZE;}
	
	if (aBufferRead.capacity() > 1) {aBufferRead.clear();}
	aBufferRead.reserve(iNumberReadByte);
	
	fseek(pFile, 0, SEEK_SET);
	aBufferRead.resize(iNumberReadByte);
	if( iNumberReadByte != fread(&aBufferRead[0x0], sizeof(char), iNumberReadByte, pFile) ) {fclose(pFile);return ERROR_FILESIZE;}
	
	iNumberReadByte = (unsigned long int) iNumberReadByte;
	fclose(pFile);
	return 0x00;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////// TEST TEST TEST TEST TEST TEST TEST TEST TEST ////////////////////
////////////////////////////////////////////////////////////////////////////////////////
/*
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
				case IDI_EXIT: 				PostQuitMessage(WM_DESTROY);	break;
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
	
return 0x00;
}*/