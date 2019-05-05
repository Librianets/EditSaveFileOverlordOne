#ifndef __CW_HPP__
#define __CW_HPP__

BOOL CALLBACK about_funcs(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
LRESULT CALLBACK global_call (HWND hInstance, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL lia_RegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);

void OnPaint(HWND hInstance);
void destroy_all (void);
void runmsg (void);
void CreateMainWindow (void);

#endif // __CW_HPP__