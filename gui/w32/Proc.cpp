#include "global.hpp"


LRESULT WINAPI MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE: 		CreateWnd(hWnd); 	break;
		case WM_PAINT: 			PaintWnd(hWnd); 	break;
		case MSG_SAVEINFO:		{Log.Log(L"\r\n MSG_SAVEINFO");	OVERLORD::SaveInfo();} break;
		case MSG_SAVESLOT: 		{Log.Log(L"\r\n MSG_SAVESLOT"); OVERLORD::SaveSlot();} break;
		
		case WM_MOVE: 	break;
		case WM_MOVING: break;
		case WM_SIZE:	break;
		
		///////// PROJECT MESSAGE //////////////
		case MSG_SELECTOPENFILE: 	break;
		case MSG_READFILE: 			break;
		case MSG_CHECKFILE: 		break; 
		case MSG_DECOMP: 			break;
		
		//////////////////////////////////
		case WM_DESTROY: DestroyAll(); break;
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDDLG_ABOUT: 		DlgInit(DLG_ABOUT); 			break;
				case IDI_CONSOLE_SHOW: 	Log.ConsoleShow(); 				break;
				case IDI_CONSOLE_HIDE: 	Log.ConsoleHide(); 				break;
				case IDI_OPENFILE:		OVERLORD::OpenFile();			break;
				case IDI_SAVEFILE: 		OVERLORD::SaveFile(); 			break;
				case IDI_CLOZEFILE:		OVERLORD::CloseFile();			break;
				case IDI_EXIT: 			PostQuitMessage(WM_DESTROY); 	break;

				default: return (DefWindowProc(hWnd, msg, wParam, lParam));
			}
		}
		}
	default: return (DefWindowProc(hWnd, msg, wParam, lParam));
}
}

BOOL CALLBACK AboutWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG: return TRUE; break;
		case WM_CLOSE: EndDialog(hwnd, 0); break;
		case WM_COMMAND:
		{
			if (HIWORD(wParam) == 0)
			{
				switch (LOWORD(wParam))
				{
					case IDI_ABOUT1: EndDialog(hwnd, 0); break;
				}
			}
		}
	}
return FALSE;
}

BOOL CALLBACK ConsoleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG: return TRUE; break;
		case WM_CLOSE: Log.ConsoleHide(); break;
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDI_EXIT: 				PostQuitMessage(WM_DESTROY); 	break;
				case IDI_CONSOLE_CLEAR: 	Log.ConsoleClear(); 			break;
				case IDI_CONSOLE_HIDE: 		Log.ConsoleHide(); 				break;
				case IDI_GETLINECONSOLE:	Log.ConsoleGetLine(); 			break;
			}
		}
		}
	}

return FALSE;
}