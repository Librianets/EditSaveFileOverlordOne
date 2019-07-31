#include <windows.h> 		// WINDOWS
#include <vector>			// Language C++
using std::vector;

#include "global.hpp"		// project
#include "resource.hpp"		// project

#include "debug.hpp"		// project
#include "logging.hpp"		// project

#include "mainfuncs.hpp"	// project
#include "functions.hpp"	// project
#include "proc.hpp"			// project

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
/////////////////////////////////////////////////////////////////////
///////////////// извлечение сообщений для отдельных окон ///////////
//nop
//nop
//nop
//nop
//nop
///////////////// извлечение сообщений для отдельных окон ///////////
/////////////////////////////////////////////////////////////////////

	switch (msg)
	{
		case WM_CREATE:{	COA.HdcPaint = COA.CreateWnd(hWnd);		}break;
		case WM_PAINT:{		COA.PaintWnd(hWnd, COA.HdcPaint);		}break;
		
		//case WM_CTLCOLORBTN: {}break;
		//case WM_CTLCOLORSTATIC: {}break;
		//case WM_ERASEBKGND: {}break;
		//case WM_MOVE: 	break;
		//case WM_MOVING: break;
		//case WM_SIZE:	break;
		
		///////// PROJECT MESSAGE //////////////
		//case MSG_SELECTOPENFILE: 	break;
		//case MSG_READFILE: 		break;
		//case MSG_CHECKFILE: 		break;
		//case MSG_DECOMP: 			break;
		
		case MSG_SAVEINFO:
		{
			info(L"\r\nSelected SAVEINFO FILE", L"");
			OVERLORD::SaveInfo();
		} break;
		
		case MSG_SAVESLOT: 		
		{
			info(L"\r\nMSG_SAVESLOT", L"");
			OVERLORD::SaveSlot();
		} break;
		
		//case MSG_PAINTGROUPBOX: {	} break;
		
		//////////////////////////////////
		case WM_DESTROY: DestroyAll();break;
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDDLG_ABOUT: 		COA.DlgInit(DLG_ABOUT);			break;
				case IDI_CONSOLE_SHOW: 	CACon.ConsoleShow();			break;
				case IDI_CONSOLE_HIDE: 	CACon.ConsoleHide();			break;
				case IDI_OPENFILE:		OVERLORD::OpenFile();			break;
				case IDI_SAVEFILE: 		OVERLORD::SaveFile();			break;
				case IDI_CLOZEFILE:		OVERLORD::CloseFile();			break;
				case IDI_EXIT: 			PostQuitMessage(WM_DESTROY);	break;

				default: return (DefWindowProc(hWnd, msg, wParam, lParam));
			}
		}
		}
	default: return (DefWindowProc(hWnd, msg, wParam, lParam));
}
}

BOOL CALLBACK AboutWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG: return TRUE;break;
		case WM_CLOSE: EndDialog(hwnd, 0);break;
		case WM_COMMAND:
		{
			if (HIWORD(wParam) == 0)
			{
				switch (LOWORD(wParam))
				{
					case IDI_ABOUT1: EndDialog(hwnd, 0);break;
				}
			}
		}
	}
return FALSE;
}

LRESULT CALLBACK ProcAppCheckBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	switch (msg)
	{
	//case WM_PAINT: {}break;
	//case WM_CTLCOLORBTN: {}break;

	case WM_CTLCOLORSTATIC:
	{
		HDC hdcbutton = (HDC)wParam;
		SetBkMode(hdcbutton, TRANSPARENT);
		SetTextColor(hdcbutton, RGB(0xFF, 0xFF, 0xFF));
		return (LRESULT)GetStockObject(NULL_BRUSH);
	}break;
		
	//case WM_ERASEBKGND:	{	}break;
	
	default: return (DefWindowProc(hWnd, msg, wParam, lParam));
	}
}

LRESULT CALLBACK ProcAppGroupBoxSI(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
//////////////////////////////////////////////////////////////////////////////
///////////////// извлечение некоторых сообщений для дочерних окон ///////////
if (msg == WM_CTLCOLORSTATIC)
{
	if ((HWND)lParam != NULL)
	{
		for(int i = 0; i < 10; i++)
		{
		if ((HWND)lParam == CSIWC.aCBSI[i].hWnd)
			{return ProcAppCheckBox(hWnd, msg, wParam, lParam);}
		}
		
		if ((HWND)lParam == CSIWC.hWndSI[2])
		{
			HDC hdcbutton = (HDC)wParam;
			SetBkMode(hdcbutton, TRANSPARENT);
			SetTextColor(hdcbutton, RGB(0xFF, 0xFF, 0xFF));
			return (LRESULT)GetStockObject(NULL_BRUSH);
		}
	}
}
///////////////// извлечение некоторых сообщений для дочерних окон ///////////
//////////////////////////////////////////////////////////////////////////////

	//info(L"\r\nProcAppGroupBoxSI", L"");
	switch (msg)
	{
	//case WM_CREATE: {}break;
	case WM_PAINT: 
	{
		//debug(L"\r\nWM_PAINT", L"");

		HGDIOBJ hSOOne;
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint(hWnd, &ps);
		hSOOne = SelectObject(hDC, GetStockObject(NULL_BRUSH));
		SetBkMode(hDC, TRANSPARENT);
		DeleteObject(hSOOne);
		HPEN hSOOnea = CreatePen(PS_SOLID, 1, RGB(0xFF, 0x00, 0x00));
		hSOOne = SelectObject(hDC, (HGDIOBJ) hSOOnea);
	
		for(int i = 0; i < 3; i++)
		{
			Rectangle(hDC, \
			CSIWC.aWndSI[i].rectWnd.left, \
			CSIWC.aWndSI[i].rectWnd.top, \
			CSIWC.aWndSI[i].rectWnd.right, \
			CSIWC.aWndSI[i].rectWnd.bottom);
		}
		
		DeleteObject(hSOOne);
		EndPaint(hWnd, &ps);
	}break;
	
	//case WM_CTLCOLORBTN: 		{}break;
	//case WM_CTLCOLORSTATIC:	{}break;
	//case WM_ERASEBKGND:		{}break;
	case WM_COMMAND:
	{
	//	info(L"\r\nWM_COMMAND", L"");
	//	info(L"\r\nCBN_SELENDOK = %i", CBN_SELENDOK);
	//	info(L"\r\nHIWORD(wParam) = %i", HIWORD(wParam));

	if (HIWORD(wParam) == CBN_SELENDOK)
	{
		if ((HWND)lParam == CSIWC.hWndSI[1])
		{
			if (CSIWC.RefreshAlternativeInfoSI(SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0)) == -1)
			{
				errormsg(-1, SI);
			}
			break;
		}
	}
	}break;
	
	default: return (DefWindowProc(hWnd, msg, wParam, lParam));
	}
}