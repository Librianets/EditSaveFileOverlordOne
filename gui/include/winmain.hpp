#ifndef __WINMAIN_H__
#define __WINMAIN_H__

extern HMENU hMenu;
extern HWND notmodaldialog;
extern HWND global_window;
extern HACCEL haccel;
extern WNDCLASSEX global_class;
extern HWND logo;

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpszCmdParam, int nCmdShow);

#endif // __WINMAIN_H__