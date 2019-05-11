#include "global.hpp"



/*
void logging ()
{
	AllocConsole();
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	WndConsole = GetConsoleWindow();
	//ShowWindow(WndConsole, SW_HIDE);
	hConsoleBuf = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsoleBuf);
	SetConsoleTitle(L"Overlord_console");
	
	SMALL_RECT rect;
	rect.Left = 0;
	rect.Top = 0;
	rect.Right = 50;
	rect.Bottom = 15;
	SetConsoleWindowInfo (hConsoleBuf, TRUE, &rect);
	
	if(l) log(L"Open console. Project: ESD overlord.\n");
	SetConsoleCtrlHandler((PHANDLER_ROUTINE) ConsoleHandlerRoutine, TRUE);
	
	HMENU hm = GetSystemMenu(WndConsole, FALSE );
	RemoveMenu(hm, SC_CLOSE, MF_BYCOMMAND);
	DrawMenuBar(WndConsole);
}

void showconsole (void)
{
	if (WndConsole != NULL)
	{
	ShowWindow(WndConsole, SW_SHOW);
	ShowWindow(WndConsole, SW_HIDE);
	ShowWindow(WndConsole, SW_SHOW);
	SetWindowPos(WndConsole, HWND_TOP, 10, 10, 400, 300, 0);

	}
	else{error(console, notexitapp);} //переделать
}

void hideconsole (void)
{
	ShowWindow(WndConsole, SW_HIDE);
}

void closeconsole (void)
{
	hideconsole();
	FreeConsole();
	hConsole = NULL;
	WndConsole = NULL;
}

void log(const wchar_t *fmt, ...)
{
	if (WndConsole != NULL)
	{
	va_list list;
	wchar_t msg[512];
	DWORD tmp;
	va_start(list, fmt);
	vswprintf(msg, sizeof(msg), fmt, list);
	va_end(list);
	WriteConsole (hConsoleBuf, msg, (DWORD)wcslen(msg), &tmp, 0);
	}
	else{error(console, notexitapp);} //переделать 
}
wchar_t globalmsg [512];
void log2(const wchar_t *fmt, ...)
{
	va_list list;
	//wchar_t globalmsg[512];
	DWORD tmp;
	va_start(list, fmt);
	vswprintf(globalmsg, sizeof(globalmsg), fmt, list);
	va_end(list);
}*/