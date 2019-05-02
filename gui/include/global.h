#include <windows.h> 	// WINDOWS
#include <stdio.h> 		// Language C
#include <unistd.h> 		// Language C
#include <wchar.h>		// Language C
#include <resource.h>	// lia

extern HMENU hMenu;
extern HWND global_window;
extern MSG msg;
extern wchar_t name_global_class[16];
extern wchar_t name_global_window[16];
extern HINSTANCE win32_hinst;
extern WNDCLASSEX global_class;
extern BOOL CALLBACK about_funcs(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
extern HWND notmodaldialog;

