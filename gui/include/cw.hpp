#ifndef __CW_HPP__
#define __CW_HPP__

BOOL CALLBACK AboutWndProc (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT WINAPI MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);

void position_dia(HWND hwnd, HWND dia);
void Createwnd (HWND hwnd);
void Paintwnd (HWND hwnd);
void destroy_all (void);
void runmsg (void);
void CreateMainWindow (void);
void checkfile(void);
void openfile(void);

#endif // __CW_HPP__