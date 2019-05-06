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
	CreateConsoleScreenBuffer(GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	//PCONSOLE_SCREEN_BUFFER_INFO 
	//GetConsoleScreenBufferInfo(hConsole, );
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