#include "global.hpp"		// project

LRESULT WINAPI MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_CREATE:
		{
			CGG.HdcPaint = CreateWnd(hWnd);
		}break;
		
		case WM_PAINT:
		{
			//Log.Log(L"\r\n MainWndProc WM_PAINT");
			PaintWnd(hWnd, CGG.HdcPaint); 
		}break;
		
		case WM_CTLCOLORBTN:
		{
		}break;
		
		
		case WM_CTLCOLORSTATIC:
        {
            /*if((HWND)lParam == hTest)
            {
                HDC hdctest = (HDC)wParam;
                SetBkMode(hdctest, TRANSPARENT);
                SetTextColor(hdctest, RGB(255, 0, 0));
                return (LRESULT)GetStockObject(NULL_BRUSH);
            }*/
        }
        break;
		
		case WM_ERASEBKGND:
		{
		}break;
		
		case MSG_SAVEINFO:
		{
			#ifdef DEBUG
			Log.Log(L"\r\n MSG_SAVEINFO");
			#endif
			OVERLORD::SaveInfo();
		} break;
		
		case MSG_SAVESLOT: 		
		{
			#ifdef DEBUG
			Log.Log(L"\r\n MSG_SAVESLOT");
			#endif
			OVERLORD::SaveSlot();
		} break;
		
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

BOOL CALLBACK AboutWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

LRESULT WINAPI GroupBoxWndProcOne(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;	HGDIOBJ hSOOne;	HDC hWndGBOne;
	switch (msg)
	{
		case WM_CREATE:
		{

		}break;

		case WM_PAINT:
		{
		hWndGBOne = BeginPaint(hWnd, &ps);
		HGDIOBJ hSOOne = SelectObject(hWndGBOne, GetStockObject(WHITE_BRUSH));
		for(int i = 0; i < 10; i++)
		{
			Rectangle(hWndGBOne, \
			CSaveInfoWndControlOne.aCBSI[i].rectCB.left, \
			CSaveInfoWndControlOne.aCBSI[i].rectCB.top, \
			CSaveInfoWndControlOne.aCBSI[i].rectCB.right, \
			CSaveInfoWndControlOne.aCBSI[i].rectCB.bottom);
			COLORREF colortext = 0x00FFFFFF;
			SetBkMode(hWndGBOne, TRANSPARENT);
			SetTextColor(hWndGBOne, colortext);
			
			DrawTextEx(hWndGBOne, CSaveInfoWndControlOne.aCBSI[i].sText, \
			sizeof(CSaveInfoWndControlOne.aCBSI[i].sText), \
			&CSaveInfoWndControlOne.aCBSI[i].rectText, DT_LEFT, NULL);
		}

		hSOOne = SelectObject(hWndGBOne, GetStockObject(NULL_BRUSH));
		Rectangle(hWndGBOne, 0, 0, \
		CSaveInfoWndControlOne.aWndSI[0].rectWnd.right, \
		CSaveInfoWndControlOne.aWndSI[0].rectWnd.bottom);
	
		for(int i = 0; i < 10; i++)
		{
			if (CSaveInfoWndControlOne.aCBSI[i].iStatus == 1)
			{
				MoveToEx(hWndGBOne, CSaveInfoWndControlOne.aCBSI[i].rectCB.left+1, CSaveInfoWndControlOne.aCBSI[i].rectCB.top+1,NULL);
				LineTo(hWndGBOne, CSaveInfoWndControlOne.aCBSI[i].rectCB.right-1, CSaveInfoWndControlOne.aCBSI[i].rectCB.bottom-1);
				MoveToEx(hWndGBOne, CSaveInfoWndControlOne.aCBSI[i].rectCB.left+1, CSaveInfoWndControlOne.aCBSI[i].rectCB.bottom-2, NULL);
				LineTo(hWndGBOne, CSaveInfoWndControlOne.aCBSI[i].rectCB.right-1, CSaveInfoWndControlOne.aCBSI[i].rectCB.top);
			}
		}
		DeleteObject(hSOOne);
		EndPaint(hWnd, &ps);
		}break;
		
		case WM_CTLCOLORBTN:
		{

		}break;
		
		case WM_CTLCOLORSTATIC:
		{

		}break;
		
		case WM_ERASEBKGND:
		{

		}break;
		
		case WM_LBUTTONDOWN:
		{
			switch(wParam)
			{
				case MK_LBUTTON:
				{
					POINT pt;
					pt.x = LOWORD(lParam);
					pt.y = HIWORD(lParam);
					for(int i = 0; i < 10; i++)
					{
						if ((PtInRect(&CSaveInfoWndControlOne.aCBSI[i].rectCB, pt) == TRUE) &&
						(CSaveInfoWndControlOne.aCBSI[i].iEnable == 1))
						{
							CSaveInfoWndControlOne.aCBSI[i].iStatus^=1;
							InvalidateRect(hWnd, NULL, TRUE);
						}
					}
				}break;
			}
		}break;
		
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

LRESULT WINAPI GroupBoxWndProcTwo(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;	HGDIOBJ hSOOne;	HDC hWndGBOne;
	switch (msg)
	{
		
		case WM_CREATE:
		{

		}break;

		case WM_PAINT:
		{
		hWndGBOne = BeginPaint(hWnd, &ps);
		hSOOne = SelectObject(hWndGBOne, GetStockObject(NULL_BRUSH));
		Rectangle(hWndGBOne, 0, 0, \
		CSaveInfoWndControlOne.aWndSI[1].rectWnd.right, \
		CSaveInfoWndControlOne.aWndSI[1].rectWnd.bottom);
		
		EndPaint(hWnd, &ps);
		}break;
		
		case WM_CTLCOLORBTN:
		{

		}break;
		
		case WM_CTLCOLORSTATIC:
		{

		}break;
		
		case WM_ERASEBKGND:
		{

		}break;
		
		case WM_LBUTTONDOWN:
		{
			switch(wParam)
			{
				case MK_LBUTTON:
				{
					
				}break;
			}
		}break;
		
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

LRESULT WINAPI GroupBoxWndProcThree(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;	HGDIOBJ hSOOne;	HDC hWndGBOne;
	switch (msg)
	{
		
		case WM_CREATE:
		{

		}break;

		case WM_PAINT:
		{
		hWndGBOne = BeginPaint(hWnd, &ps);
		hSOOne = SelectObject(hWndGBOne, GetStockObject(NULL_BRUSH));
		Rectangle(hWndGBOne, 0, 0, \
		CSaveInfoWndControlOne.aWndSI[2].rectWnd.right, \
		CSaveInfoWndControlOne.aWndSI[2].rectWnd.bottom);
		
		EndPaint(hWnd, &ps);
		}break;
		
		case WM_CTLCOLORBTN:
		{

		}break;
		
		case WM_CTLCOLORSTATIC:
		{

		}break;
		
		case WM_ERASEBKGND:
		{

		}break;
		
		case WM_LBUTTONDOWN:
		{
			switch(wParam)
			{
				case MK_LBUTTON:
				{
					
				}break;
			}
			
		}break;
		
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