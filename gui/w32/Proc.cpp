#include "global.hpp"

LRESULT WINAPI MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE: 	CreateWnd(hWnd); 	break;
		case WM_PAINT: 		PaintWnd(hWnd); 	break;
		
		case WM_MOVE: 	break;
		case WM_MOVING: break;
		case WM_SIZE:	break;
		
		///////// PROJECT MESSAGE //////////////
		case MSG_SELECTOPENFILE: ReadFile(); break;
		case MSG_READFILE: CheckFileSignature(&uniDInfo, aGlobalBuffer, aTableCrc32); break;
		case MSG_CHECKFILE: Decompression(uniDInfo.data.iLenFile, MAXSIZEFILE, &aGlobalBuffer[0x6], &aBufferDecomp[0x0], &uniDInfo); 
		case MSG_DECOMP: Compression(uniDInfo.data.iUnzip, MAXSIZEFILE, aBufferDecomp, aGlobalBuffer, &uniDInfo); break;
	
		
		
		
		//////////////////////////////////
		
		
		
		case WM_DESTROY: DestroyAll(); break;
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDDLG_ABOUT: 		DlgInit(DLG_ABOUT); 			break;
				case IDI_CONSOLE_SHOW: 	DlgConsoleShow(); 				break;
				case IDI_CONSOLE_HIDE: 	DlgConsoleHide(); 				break;
				case IDI_OPENFILE:		SelectFile(); 					break;
				case IDI_CLOZEFILE:		CloseHandle(hFileOpen);			break;
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
		case WM_CLOSE:EndDialog(hwnd, 0); break;
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
		case WM_CLOSE: DlgConsoleHide(); break;
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				//case IDI_ABOUT1: EndDialog(hwnd, 0); break;
				case IDI_EXIT: PostQuitMessage(WM_DESTROY); break;
				case IDI_CONSOLE_CLEAR: SendDlgItemMessage(dlgapp[1].hWnd, IDI_CONSOLE_LB, LB_RESETCONTENT,0,0); break;
				case IDI_CONSOLE_HIDE: DlgConsoleHide(); break;
				case IDI_GETLINECONSOLE:
				{
					wchar_t sTempLine[70];
					GetDlgItemText(hwnd, IDI_CONSOLECOMLINE, sTempLine, sizeof(sTempLine));
					log(L"%ls", sTempLine);
					break;
				}
			}
		}
		}
	}
return FALSE;
}