#include "cw.h"

void destroy_all (void)
{
CloseWindow(global_window);
UnregisterClass(name_global_class, win32_hinst);
PostQuitMessage(0);
}

void OnPaint(HWND hInstance)
{
PAINTSTRUCT ps;
RECT rc;

HDC hdc = BeginPaint(hInstance, &ps);
GetClientRect(hInstance, &rc);
FillRect(hdc, &rc, (HBRUSH) COLOR_WINDOW);
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
	
	unsigned int f_r;
	f_r = RegisterClassEx(&classex);
	
	if (f_r == 0) 
	{
		MessageBox(NULL, L"Error 0: Не могу зарегистрировать класс окна!", L"Ошибка", MB_OK);
		exit(1);
	} 
	else {return TRUE;}
}

LRESULT CALLBACK global_call (HWND hInstance, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
switch (msg)
{
case WM_PAINT:
{
OnPaint(hInstance);
break;
}

case WM_DESTROY: destroy_all(); break;
case WM_COMMAND:
	{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDM_ABOUT:
				{
					notmodaldialog = CreateDialog(win32_hinst, MAKEINTRESOURCE(IDM_ABOUT), global_window, about_funcs);
					ShowWindow(notmodaldialog, SW_SHOW); //nCmdShow
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
		if (LOWORD(wparam) == IDM_ABOUT_ctrl1){EndDialog(hwnd, 0);} else {break;}
		}
	}
		
return FALSE;
}


void Paintlogo(HWND hInstance)
{
logo = CreateWindowEx(WS_EX_TRANSPARENT, NULL, L"123", SS_BITMAP, 500, 500, 400, 203, NULL, NULL, win32_hinst, NULL);

ShowWindow(logo, SW_SHOW);
sleep(5);
CloseWindow(logo);
}