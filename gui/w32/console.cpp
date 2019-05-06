#include "global.hpp"

DWORD tmp;
void logging (wchar_t nametype, typeval val)
{
	
}

void openconsole (void)
{
	if (hConsole == NULL)
	{
	tmp = 0x00;
	AllocConsole();
	SetConsoleTitle(L"Overlord_console");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	}
	else{error(console, notexitapp);}
}

void closeconsole (void)
{
	FreeConsole();
	hConsole = NULL;
	tmp = 0x00;
}

void writeconsole (void)
{
	/*LPDWORD aa;
	wchar_t ab[105] = L"qwe";
	WriteConsole(hConsole, ab, 3, aa, NULL);*/
}