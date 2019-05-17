#include "global.hpp"

void InitConsole(void)
{
dlgapp[1].hWnd = CreateDialog(gapp.inst, MAKEINTRESOURCE(IDDLG_ERROR_CONSOLE), gapp.wnd, dlgapp[1].WndProc);
HMENU hMenuERROR_CONSOLE = LoadMenu(gapp.inst, MAKEINTRESOURCE(IDM_MENUERROR_CONSOLE));
SetMenu(dlgapp[1].hWnd, hMenuERROR_CONSOLE);
SetPosDlg(gapp.wnd, dlgapp[1].hWnd);
SetWindowPos(dlgapp[1].hWnd, HWND_TOP, t_xy_dia.x,(t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
ShowWindow(dlgapp[1].hWnd, SW_HIDE);
log(L"Project: ESD overlord.\n");
wchar_t sTeststringERROR_CONSOLE[15] = L"TEST ТЕСТ";
log(L"TEST ТЕСТ. i=%i, c=%c, f=%f, s=%ls, wc=%ls", 5, 't', 5.5, L"ТЕСТ TEST", sTeststringERROR_CONSOLE);
}

void log(const wchar_t *fmt, ...)
{
	va_list list;
	DWORD tmp;
	va_start(list, fmt);
	vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
	WriteDlgConsole();
}

void WriteDlgConsole(void)
{
	SendDlgItemMessage(dlgapp[1].hWnd, IDI_CONSOLE_LB, LB_ADDSTRING,0,(LPARAM)sGlobalMsg);
}

void DlgConsoleShow(void)
{
	SetPosDlg(gapp.wnd, dlgapp[1].hWnd);
	SetWindowPos(dlgapp[1].hWnd, HWND_TOP, t_xy_dia.x,(t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
	ShowWindow(dlgapp[1].hWnd, SW_SHOW);
}

void DlgConsoleHide(void)
{
	ShowWindow(dlgapp[1].hWnd, SW_HIDE);
}