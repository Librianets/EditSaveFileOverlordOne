#ifndef __PROC_HPP__
#define __PROC_HPP__

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK AboutWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK ProcAppCheckBox(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ProcAppGroupBoxSI(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif // __PROC_HPP__