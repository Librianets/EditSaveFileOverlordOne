#include <windows.h> 		// WINDOWS
#include <commctrl.h> 		// WINDOWS
#include <iostream>			// Language C++
#include <vector>			// Language C++
#ifdef DEBUGMODE
#include <chrono>			// Language C++
#endif
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
class CSaveInfoOverlord CSIOO;
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

int COverlordApp::SetErrorStatus (int iError)
{
	iErrorStatus = iError;
	return iErrorStatus;
}

int COverlordApp::GetErrorStatus (void)
{
	return iErrorStatus;
}

void COverlordApp::ClearErrorStatus (void)
{
	iErrorStatus = 0;
}

void COverlordApp::ParseCommandLine(PWSTR lpszCmdParam)
{
	pArgv = CommandLineToArgvW(GetCommandLineW(), &iArgc);
	iSizePath = wcslen (pArgv[0]);
	int iOffsetPath = 0;
	for (int i = 0; i < iSizePath; i++)
	{
		if (pArgv[0][i] == L'\\')
		{
			iOffsetPath = i;
		}
	}
	aPathApp.reserve(iOffsetPath+1+1); // 0 element and \0
	for(int i = 0; i <= iOffsetPath; i++)
	{
		//aPathApp[i] = pArgv[0][i];
		aPathApp.push_back(pArgv[0][i]);
		if (i == iOffsetPath) {aPathApp.push_back(L'\0');}
			//aPathApp[i+1] = L'\0';}
			//
	}
	iSizePath += 2;
}

void COverlordApp::Init(HINSTANCE hInstance)
{
	ClearErrorStatus();
	gapp.inst = hInstance;
	
	if (MainRegClass(WndCExMain, MainWndProc, COA.gapp.gclass, COA.gapp.inst) != 0x00)
		{SetErrorStatus(ERROR_GCLASSNOT);return;}
	
	if (CSIWC.RegClassGroupBox(CSIWC.WndCExGroupBoxOne, ProcAppGroupBoxSI, L"GroupBoxSI", COA.gapp.inst) != 0x00)
		{SetErrorStatus(ERROR_GCLASSNOT);return;}
}

HDC COverlordApp::CreateWnd (HWND hwnd)
{
hBitmap = LoadBitmap(gapp.inst, MAKEINTRESOURCE(IDB_LOGO));
GetObject(hBitmap, sizeof(BITMAP), &bitmap);
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
hSOOne = SelectObject(hDC2, hBitmap);

POINT metric;
RECT WndSize;
GetWindowRect(hwnd, &WndSize);

//debug(L"\r\n y = %i",WndSize.bottom-WndSize.top);
//debug(L"\r\n x = %i", WndSize.right-WndSize.left);
//BitBlt(hDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hDC2, 0, 0, SRCCOPY);

StretchBlt(hDC, 0, 0, WndSize.right-WndSize.left, WndSize.bottom-WndSize.top, hDC2, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

DeleteObject(hSOOne);
EndPaint(hwnd, &ps);
SendMessage(statusbar, WM_SIZE, 0, 0);

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
	//DWORD iStyleWnd = WS_OVERLAPPEDWINDOW | WS_SIZEBOX ;
	DWORD iStyleWnd = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN | WS_SIZEBOX;
	//WS_BORDER - Создает окно, которое имеет тонкую линию рамки.
	//WS_CAPTION - Создает окно, которое имеет строку заголовка (включает в себя стиль WS_BORDER).
	//WS_POPUP - Создает выскакивающее окно. Этот стиль не может использоваться со стилем WS_CHILD
	
	//WS_CAPTION | WS_CLIPCHILDREN | WS_POPUPWINDOW | WS_MINIMIZEBOX; 
	/*uxtheme.h*/
	//INITCOMMONCONTROLSEX icex;
	//icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	//icex.dwICC = ICC_STANDARD_CLASSES | ICC_BAR_CLASSES | ICC_USEREX_CLASSES;
	//InitCommonControlsEx(&icex);
	
//////// Размер клиентской области ///////////////////////////////////
	POINT metric;													//
	POINT stdsize;													//
	POINT sizewndapp;												//
	metric.x = GetSystemMetrics(SM_CXSCREEN);						//1920 
	metric.y = GetSystemMetrics(SM_CYSCREEN);						//1080
	stdsize.x = iSizeWndX;											//
	stdsize.y = iSizeWndY;											//512 минимум
	sizewndapp.x = (metric.x-stdsize.x)/2;							//(1920-640)/2=640
	sizewndapp.y = (metric.y-stdsize.y)/2;							//(1080-512)/2=284
	RECTmainwnd.left = sizewndapp.x;								//
	RECTmainwnd.right = sizewndapp.x + stdsize.x;					//
	RECTmainwnd.top = sizewndapp.y;									//
	RECTmainwnd.bottom = sizewndapp.y + stdsize.y;					//
	AdjustWindowRectEx(&RECTmainwnd, iStyleWnd, TRUE, 0);			//
	stdsize.x = RECTmainwnd.right-RECTmainwnd.left;					//
	stdsize.y = RECTmainwnd.bottom-RECTmainwnd.top;					//
//////////////////////////////////////////////////////////////////////
	
	HWND hwnd;
	hwnd = CreateWindowEx(0, COA.gapp.gclass, COA.gapp.gwnd, iStyleWnd, \
	sizewndapp.x, sizewndapp.y, stdsize.x, stdsize.y+22, \
	NULL, NULL, COA.gapp.inst, NULL);
	
	statusbar = CreateStatusWindow(WS_CHILD | WS_VISIBLE, L"VerProg 0.4 / VerLibCore 0.3", hwnd, 123);
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

/*HWND TESTEDIT = CreateWindowEx(WS_EX_TRANSPARENT, L"EDIT", L"", WS_CHILD | ES_LEFT, \
230, 50, 20, 20, \
hWndSI[0], NULL, COA.gapp.inst, NULL);
ShowWindow(TESTEDIT, SW_SHOW);



CreateUpDownControl(WS_CHILD | WS_BORDER | WS_VISIBLE | UDS_SETBUDDYINT, 250, 50, 15, 20, hWndSI[0], 50, COA.gapp.inst, TESTEDIT, 10, 0, 5);*/
/*
HWND CreateUpDownControl(
  DWORD     dwStyle,
  int       x,
  int       y,
  int       cx,
  int       cy,
  HWND      hParent,
  int       nID,
  HINSTANCE hInst,
  HWND      hBuddy,
  int       nUpper,
  int       nLower,
  int       nPos
);
*/


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
	debug(L"\r\niSaveSelect = %i", iSaveSelect);
	
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
	
	debug(L"\r\nCUnpackPackOne.iFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);
	unsigned char *pText;
	if (CUnpackPackOne.iFlagDefSaveLang == LANGRU)
	{pText = CSIOO.StringConvert(iSaveSelect, 1);} else {pText = CSIOO.StringConvert(iSaveSelect, 0);}
	
	//debug(L"\r\niFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);
	
	SendMessage(hWndSI[2], WM_SETTEXT, 0, (LPARAM)L"");
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)L"Локация: ");
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)pText);
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)L"\r\n");
	
	float iTime = CSIOO.TimeDissambler(iSaveSelect);
	int iHour = (int)iTime/60;
	int iMinute = (int)iTime - iHour*60;
	
	debug(L"\r\niTime = %i", iTime);
	debug(L"\r\niHour = %i", iHour);
	debug(L"\r\niMinute = %i", iMinute);

	if (CSIOO.GetErrorStatus() == 0) 
	{
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)L"Время в игре: ");
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)L"\r\n");
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)CSIOO.TimeConvector(iHour));
	
	wchar_t iText [20]; int iFlagText = 0; int iLOWHour = 0;
		
#ifdef DEBUGMODE
	std::chrono::system_clock::time_point TimeSpeed;
	std::chrono::system_clock::time_point TimeSpeed2;
	TimeSpeed = std::chrono::system_clock::now();
#endif
	if (iHour < 10) {iLOWHour = iHour;} else {iLOWHour = iHour << 24 >> 24;}
#ifdef DEBUGMODE
	TimeSpeed2 = std::chrono::system_clock::now();
	debug(L"\r\nTimeSpeed = %e, %u", TimeSpeed, TimeSpeed);
	debug(L"\r\nTimeSpeed2 = %e, %u", TimeSpeed2, TimeSpeed2);
	debug(L"\r\n^TimeSpeed = %e, %u", TimeSpeed2-TimeSpeed, TimeSpeed2-TimeSpeed);
#endif
	int temp = 0;

	if ( iLOWHour == 1 && iHour > 20) 					{wcscpy(iText, L" час и "); iFlagText = 1;} else {}
	if ( iLOWHour == 2 && (iHour < 5 || iHour > 20)) 	{wcscpy(iText, L" часа и "); iFlagText = 1;} else {}
	if ( iLOWHour == 3 && (iHour < 5 || iHour > 20)) 	{wcscpy(iText, L" часа и "); iFlagText = 1;} else {}
	if ( iLOWHour == 4 && (iHour < 5 || iHour > 20)) 	{wcscpy(iText, L" часа и "); iFlagText = 1;} else {}
	if (iFlagText == 0) 								{wcscpy(iText, L" часов и ");} else {}
		
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)iText);
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)CSIOO.TimeConvector(iMinute));
	
	memset (iText, 0, 20*2); iFlagText = 0; int iLOWMinute = 0;
	if (iMinute < 10) {iLOWMinute = iMinute;} else {iLOWMinute = iMinute << 24 >> 24;}
	if ( iLOWMinute == 1 && iMinute > 20) 					{wcscpy(iText, L" минута"); iFlagText = 1;} else {}
	if ( iLOWMinute == 2 && (iMinute < 5 || iMinute > 20)) 	{wcscpy(iText, L" минуты"); iFlagText = 1;} else {}
	if ( iLOWMinute == 3 && (iMinute < 5 || iMinute > 20)) 	{wcscpy(iText, L" минуты"); iFlagText = 1;} else {}
	if ( iLOWMinute == 4 && (iMinute < 5 || iMinute > 20)) 	{wcscpy(iText, L" минуты"); iFlagText = 1;} else {}
	if (iFlagText == 0) 									{wcscpy(iText, L" минут");} else {}
	
	SendMessage(hWndSI[2], EM_REPLACESEL, 0, (LPARAM)iText);
	}
	//debug(L"\r\nCUnpackPackOne.iFlagDefSave = %02X", CUnpackPackOne.iFlagDefSave);
	//debug(L"\r\nCUnpackPackOne.iFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);
	//CSIOO.ClearErrorStatus();
	//debug(L"\r\nerror csioo = %02X", CSIOO.GetErrorStatus());
	
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
	
//	debug(L"\r\n%02X", CUnpackPackOne.aBufferOne[CUnpackPackOne.UnionDataInfoOne.data.iUnzip-1]);
//	debug(L"\r\n%02X", CUnpackPackOne.aBufferOne[CUnpackPackOne.UnionDataInfoOne.data.iUnzip-2]);
//	debug(L"\r\n%02X", CUnpackPackOne.aBufferOne[CUnpackPackOne.UnionDataInfoOne.data.iUnzip-3]);

	iTempValue = CUnpackPackOne.DefineTypeFile();
	if (iTempValue != 0x00) {errormsg(iTempValue, PACKLIB);
		info(L"DefineTypeFile -%X", abs(iTempValue) );
	return -0x01;}
	
	//debug(L"\r\nCUnpackPackOne.iFlagDefSave = %02X", CUnpackPackOne.iFlagDefSave);
	//debug(L"\r\nCUnpackPackOne.iFlagDefSaveLang = %02X", CUnpackPackOne.iFlagDefSaveLang);

	
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
	debug(L"\r\nSelectSaveGameFile -%X", abs(iTempValue) );
	return -0x01;}
	
	CSIOO.AssemblySI();
	if (CSIOO.GetErrorStatus() != 0) 
	{
		errormsg(iTempValue, APP);
		debug(L"\r\nAssemblySI -%X", CSIOO.GetErrorStatus());
		return -0x01;
	}
	
	CUnpackPackOne.lpGetBuffer(1)->resize(CSIOO.SIS.header.numbersize);
	CUnpackPackOne.lpGetBuffer(1)->clear();
	
	*(CUnpackPackOne.lpGetBuffer(1)) = *(CSIOO.lpGetBuffer());
	debug(L"\r\nCSIOO.SIS.header.numbersize %i", CSIOO.SIS.header.numbersize);

#ifdef DEBUGMODE
debug(L"\r\nCheck data info", L"");
for(int ii = 0; ii < CSIOO.SIS.header.numbersize; ii++)
{
	if (ii == 0) {debug(L"\r\n", L"");} else {}
	debug(L"%02X, ", (*(CSIOO.lpGetBuffer()))[ii] );
}

for(int ii = 0; ii < CSIOO.SIS.header.numbersize; ii++)
{
	if (ii == 0) {debug(L"\r\n", L"");} else {}
	debug(L"%02X, ", (*(CUnpackPackOne.lpGetBuffer(1)))[ii] );
}
#endif
	
	CUnpackPackOne.lpGetDataInfo()->data.iUnzip = CSIOO.SIS.header.numbersize;
	CUnpackPackOne.Compression();
	if (CUnpackPackOne.GetErrorStatus() != 0)
	{
	debug(L"\r\nCompression -%X", abs(iTempValue) );
	errormsg(iTempValue, PACKLIB);
	return -0x01;
	} else {}
	
	//if (CGameSaveControlOne.lpGetBuffer()->capacity() > 1) {
	CGameSaveControlOne.lpGetBuffer()->clear();//}
	//CGameSaveControlOne.lpGetBuffer()->reserve( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );
	CGameSaveControlOne.lpGetBuffer()->resize( CUnpackPackOne.lpGetDataInfo()->data.iLenFile );
	debug(L"\r\nCUnpackPackOne.lpGetDataInfo()->data.iLenFile=%i", CUnpackPackOne.lpGetDataInfo()->data.iLenFile);

	*(CGameSaveControlOne.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	CGameSaveControlOne.iNumberReadByte = CUnpackPackOne.lpGetDataInfo()->data.iLenFile;

#ifdef DEBUGMODE
debug(L"\r\nCheck data info", L"");
for(int ii = 0; ii < CUnpackPackOne.lpGetDataInfo()->data.iLenFile; ii++)
{
	if (ii == 0) {debug(L"\r\n", L"");} else {}
	debug(L"%02X, ", (*(CUnpackPackOne.lpGetBuffer(1)))[ii] );
}

for(int ii = 0; ii < CGameSaveControlOne.iNumberReadByte; ii++)
{
	if (ii == 0) {debug(L"\r\n", L"");} else {}
	debug(L"%02X, ", (*(CGameSaveControlOne.lpGetBuffer()))[ii] );
}
#endif

	if (CGameSaveControlOne.iNumberReadByte < 50) return -0x01;
	iTempValue = CGameSaveControlOne.WriteGameFile();
	if (iTempValue != 0x00) {errormsg(iTempValue, APP);
	debug(L"\r\nWriteGameFile -%X", abs(iTempValue) );
	return -0x01;}

	CUnpackPackOne.ClearClass();
	CSIOO.ClearClass();
	CGameSaveControlOne.ClearClass();
	
	return 0x00;
}

int OVERLORD::SaveSlot(void) 
{
	
return 0x00;
}

int OVERLORD::SaveInfo(void)
{
	CSIOO.ClearClass(); CSIWC.ClearClass();
	
	CSIWC.CreateWnd();
	
	CSIOO.SIS.header.numbersize = CUnpackPackOne.lpGetDataInfo()->data.iUnzip;
	CSIOO.lpGetBuffer()->reserve(CSIOO.SIS.header.numbersize);
	*(CSIOO.lpGetBuffer()) = *(CUnpackPackOne.lpGetBuffer(1));
	
debug(L"\r\nlpGetDataInfo()->iUnzip = %i", CUnpackPackOne.lpGetDataInfo()->data.iUnzip);
debug(L"\r\nSIS.header.numbersize = %i", CSIOO.SIS.header.numbersize);
#ifdef DEBUGMODE
for(int l = 0;l < CUnpackPackOne.lpGetDataInfo()->data.iUnzip;l++)
{if (l == 0) {debug(L"\r\n", L"");} else {} ;debug(L"%x, ", (*(CSIOO.lpGetBuffer()))[l] );}
#endif

	CUnpackPackOne.ClearClass();
	
	CSIOO.DisassemblySI();
	
debug(L"\r\nCSIOO.iFlagSaveCount = %i", CSIOO.iFlagSaveCount);
#ifdef DEBUGMODE
for(int l = 0;l < 10;l++)
{debug(L"\r\niFlagSaveNum[%i]=%i", l, CSIOO.SIS.data.iFlagSaveNum[l])}
#endif

	for (int i = 0; i < 10; i++)
	{
		if (CSIOO.SIS.data.iFlagSaveNum[i] == 1)
		{
		CSIWC.SetWndLong(i);
		}
	}
#ifdef DEBUGMODE
	for(int i = 0; i < 10; i++)
	{
		debug(L"\r\niPosSaveInCB[%i] = %i", i, CSIWC.iPosSaveInCB[i]);
	}
#endif
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
	if (pFile == NULL) {return ERROR_SAVEFILE;}
	
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
	if (pFile == NULL) {return ERROR_OPENFILE;}
	
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