#include "global.hpp"

void OnPaint(HWND hInstance)
{
PAINTSTRUCT ps; // typedef struct PAINTSTRUCT {HDC  hdc; BOOL fErase; RECT rcPaint; BOOL fRestore; BOOL fIncUpdate; BYTE rgbReserved[32];}
RECT rc;
HDC hdc_globalwindow;

hdc_globalwindow = BeginPaint(hInstance, &ps);
if (hdc_globalwindow == NULL){PostQuitMessage(WM_NULL);}

GetClientRect(hInstance, &rc); //заполнитель... 

FillRect(hdc_globalwindow, &rc, (HBRUSH) LTGRAY_BRUSH);
EndPaint(hInstance, &ps);
}

BOOL lia_RegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance)
{
	classex.cbSize = sizeof(classex);
	classex.style = CS_HREDRAW | CS_VREDRAW;
	classex.lpfnWndProc = Proc;
	classex.cbClsExtra = 0;
	classex.cbWndExtra = 0;
	classex.hInstance = hinstance;
	classex.hIcon = LoadIcon(hinstance, MAKEINTRESOURCE(IDI_APP_ICON));
	classex.hCursor = NULL;
	classex.hbrBackground = (HBRUSH)COLOR_WINDOW;
	classex.lpszMenuName = MAKEINTRESOURCE(IDM_MENU);
	classex.lpszClassName = szClassName;
	classex.hIconSm = NULL;
	
	if (!RegisterClassEx(&classex)){error(gclassnot, exit_app);}
	
return TRUE;
}

LRESULT CALLBACK global_call (HWND hInstance, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	switch (msg)
	{
		case WM_PAINT: 
		{
		if (global_window != NULL) {OnPaint(hInstance);}
		break;
		}
		
		case WM_DESTROY: {destroy_all(); break;}
		
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDMI_ABOUT:
				{
					notmodaldialog = CreateDialog(gapp.inst, MAKEINTRESOURCE(IDMI_ABOUT), global_window, about_funcs);
					ShowWindow(notmodaldialog, SW_SHOW); //nCmdShow
				}break;
				
				case IDMI_EXIT:
				{
					PostQuitMessage(WM_DESTROY);
				}break;
				
				default: return (DefWindowProc(hInstance, msg, wParam, lParam));
			}
		} else {break;}
	}
default: return (DefWindowProc(hInstance, msg, wParam, lParam));
}

}

BOOL CALLBACK about_funcs(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
		case WM_INITDIALOG: return TRUE; break;
		case WM_COMMAND:
		{
		if (LOWORD(wparam) == IDMI_ABOUT_1){EndDialog(hwnd, 0);} else {break;}
		}
	}
		
return FALSE;
}

void CreateMainWindow (void) 
{
	lia_RegClass(global_class, global_call, gapp._class, gapp.inst);
	
	gapp.wnd = CreateWindowEx(0, gapp._class, gapp._wnd, \
	WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, 300, 300, 600, 600, NULL, NULL, gapp.inst, NULL); //|WS_EX_TRANSPARENT|WS_EX_OVERLAPPEDWINDOW WS_EX_DLGMODALFRAME

	if (!gapp.wnd){error(gwndnot, exit_app);}


	ShowWindow(gapp.wnd,SW_SHOW); //nCmdShow
	
	UpdateWindow(gapp.wnd);//WM_PAINT


//	CreateMainMenu();
//	SetMenu(gApp.hWnd, gApp.hMenu);
}

void runmsg(void)
{
	haccel = LoadAccelerators(gapp.inst, MAKEINTRESOURCE(ID_G_ACCEL)); 
    if (haccel == NULL) {error(gaccelnot, exit_app);}
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if (IsDialogMessage(notmodaldialog, &msg) == TRUE)
		{
			
		}
		else
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
}

void destroy_all (void)
{
CloseWindow(global_window);
UnregisterClass(gapp._class, gapp.inst);
PostQuitMessage(WM_NULL);
}
