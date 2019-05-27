#include "global.hpp"

void InitConsole(void)
{
dlgapp[1].hWnd = CreateDialog(gapp.inst, MAKEINTRESOURCE(IDDLG_CONSOLE), gapp.hwnd, dlgapp[1].WndProc);

HMENU hMenu = LoadMenu(gapp.inst, MAKEINTRESOURCE(IDM_MENUERROR_CONSOLE));
SetMenu(dlgapp[1].hWnd, hMenu);
SetPosDlg(gapp.hwnd, dlgapp[1].hWnd);
SetWindowPos(dlgapp[1].hWnd, HWND_TOP, t_xy_dia.x,(t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
ShowWindow(dlgapp[1].hWnd, SW_HIDE);
}

void log(const wchar_t *fmt, ...)
{
	va_list list;
	DWORD tmp;
	va_start(list, fmt);
	vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
	
#if WIN32PROJECT
#if WINAPIPROJECT
	WriteDlgConsole();
#else

#endif
#endif
}

void WriteDlgConsole(void)
{
	
}

void DlgConsoleShow(void)
{
	SetPosDlg(gapp.hwnd, dlgapp[1].hWnd);
	SetWindowPos(dlgapp[1].hWnd, HWND_TOP, t_xy_dia.x,(t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
	ShowWindow(dlgapp[1].hWnd, SW_SHOW);
}

void DlgConsoleHide(void)
{
	ShowWindow(dlgapp[1].hWnd, SW_HIDE);
}