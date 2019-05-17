#include "global.hpp"

wchar_t sgClass[MAXCLASSNAME] 		= L"Class main window";
wchar_t sgWnd[MAXCLASSNAME] 		= L"Редактор сохранений игры Overlord";
wchar_t sGlobalMsg[MAXPATHLEN]		= L"TEST TEST TEST";

unsigned char aGlobalBuffer[MAXSIZEFILE];
unsigned char aBufferOne[MAXSIZEFILE];

HWND hDlgAbout;
HWND hDlgConsole;

void ClearVal(void){}

void InitiationVal(HINSTANCE hInstance)
{
gapp.inst = NULL;
gapp.wnd = NULL;
gapp.menu = NULL;
gapp._class = sgClass;
gapp._wnd = sgWnd;
gapp.inst = hInstance;
gapp.WndProc = *MainWndProc;

dlgapp[0].hWnd = hDlgAbout;
dlgapp[0].WndProc = AboutWndProc;

dlgapp[1].hWnd = hDlgConsole;
dlgapp[1].WndProc = ConsoleWndProc;
}