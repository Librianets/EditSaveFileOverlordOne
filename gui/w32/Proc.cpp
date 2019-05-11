#include "global.hpp"

LRESULT WINAPI MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE: 	Createwnd(hWnd); 	break;
		case WM_PAINT: 		Paintwnd(hWnd); 	break;
		
		case WM_MOVE: 	break;
		case WM_MOVING: break;
		case WM_SIZE:	break;
		
		case WM_DESTROY: destroy_all(); break;
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDDLG_ABOUT: 		dialoginit(DLG_ABOUT); 			break;
				case IDI_CONSOLE_SHOW: 	dlgconsoleshow(); 				break;
				case IDI_CONSOLE_HIDE: 	dlgconsolehide(); 				break;
				case IDI_OPENFILE:		checkfile(); 					break;
				case IDI_EXIT: 			PostQuitMessage(WM_DESTROY); 	break;

				default: return (DefWindowProc(hWnd, msg, wParam, lParam));
			}
		}
		}
	default: return (DefWindowProc(hWnd, msg, wParam, lParam));
}
}

BOOL CALLBACK AboutWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)\
{switch (msg){case WM_INITDIALOG: return TRUE; break;case WM_COMMAND:{if \
(HIWORD(wParam) == 0){switch (LOWORD(wParam)) {case IDI_ABOUT1: \
EndDialog(hwnd, 0); break;}}}}return FALSE;}

BOOL CALLBACK ConsoleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG: return TRUE; break;
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				//case IDI_ABOUT1: EndDialog(hwnd, 0); break;
				case IDI_EXIT: PostQuitMessage(WM_DESTROY);break;
			}
		}
		}
	}
return FALSE;
}