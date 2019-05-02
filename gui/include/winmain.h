#include <global.h> 	// global include

typedef struct {
	HWND hWnd;
	HINSTANCE hInstance;
	HMENU hMenu;
} gApp;
BOOL CALLBACK about_funcs(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT CALLBACK global_call (HWND, UINT, WPARAM, LPARAM);
BOOL lia_RegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance); 

HMENU hMenu;
HWND notmodaldialog;

HWND global_window;

MSG msg;
wchar_t name_global_class[16] = L"global_class";
wchar_t name_global_window[16] = L"global_window";
HINSTANCE win32_hinst = NULL;
WNDCLASSEX global_class;
void Paintlogo();
HWND logo;


