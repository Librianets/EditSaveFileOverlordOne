#include "global.hpp"


void initconsole(void)
{
dapp[1].hWnd = CreateDialog(gapp.inst, MAKEINTRESOURCE(IDDLG_CONSOLE), gapp.wnd, dapp[1].WndProc);
HMENU hMenuConsole = LoadMenu(gapp.inst, MAKEINTRESOURCE(IDM_MENUCONSOLE));
SetMenu(dapp[1].hWnd, hMenuConsole);
position_dia(gapp.wnd, dapp[1].hWnd);
SetWindowPos(dapp[1].hWnd, HWND_TOP, t_xy_dia.x,(t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
ShowWindow(dapp[1].hWnd, SW_HIDE);
log(L"Project: ESD overlord.\n");
wchar_t sTeststringconsole[15] = L"TEST ТЕСТ";
log(L"TEST ТЕСТ. i=%i, c=%c, f=%f, s=%ls, wc=%ls", 5, 't', 5.5, L"ТЕСТ TEST", sTeststringconsole);
}

void log(const wchar_t *fmt, ...)
{
	va_list list;
	DWORD tmp;
	va_start(list, fmt);
	vswprintf(globalmsg, sizeof(globalmsg), fmt, list);
	va_end(list);
	writedlgconsole();
	
}

void writedlgconsole(void)
{
	SendDlgItemMessage(dapp[1].hWnd, ID_CONSOLE_LB, LB_ADDSTRING,0,(LPARAM)globalmsg);
}

void dlgconsoleshow(void)
{
	position_dia(gapp.wnd, dapp[1].hWnd);
	SetWindowPos(dapp[1].hWnd, HWND_TOP, t_xy_dia.x,(t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
	ShowWindow(dapp[1].hWnd, SW_SHOW);
}

void dlgconsolehide(void)
{
	ShowWindow(dapp[1].hWnd, SW_HIDE);
}