#ifndef __PROC_HPP__
#define __PROC_HPP__

LRESULT WINAPI MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


LRESULT WINAPI GroupBoxWndProcOne(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI GroupBoxWndProcTwo(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI GroupBoxWndProcThree(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif // __PROC_HPP__