#include "global.hpp"

RECT rectmainwnd;

HWND hDlgAbout;
HWND hDlgConsole;
HACCEL hAccel;
HWND hLogo;

WNDCLASSEX WndC_main;

AppData gapp;
Data dapp[MAXCOUNTERPOINTER];
sizeall scwnd, szwnd, pwnd, t_xy_dia;

wchar_t s_gclass[MAXCLASSNAME] = L"Class main window";
wchar_t s_gwnd[MAXCLASSNAME] = L"Редактор сохранений игры Overlord";

wchar_t sError[MAXMSGLEN] 		= L"Ошибка";
wchar_t sWarning[MAXMSGLEN] 	= L"Предупреждение";
wchar_t s_gwndnot[MAXMSGLEN] 	= L"Не удалось создать главное окно";
wchar_t s_gclassnot[MAXMSGLEN] 	= L"Не удалось зарегистрировать класс окна";
wchar_t s_gaccelnot[MAXMSGLEN] 	= L"Проблемы с таблицей акселератов";
wchar_t s_filecheck[MAXMSGLEN] 	= L"Проблемы с файлом. Повторите попытку";
wchar_t s_console[MAXMSGLEN] 	= L"Не удалось создать консоль";
wchar_t globalmsg[MAXPATHLEN]	= L"TEST TEST TEST";

wchar_t fileopen[MAXPATHLEN];

void clearval(void)
{

}

void initiationval(HINSTANCE hInstance)
{

gapp.inst = NULL;
gapp.wnd = NULL;
gapp.menu = NULL;
gapp._class = s_gclass;
gapp._wnd = s_gwnd;
gapp.inst = hInstance;
gapp.WndProc = *MainWndProc;

scwnd.x = GetSystemMetrics(SM_CXSCREEN); //1920
scwnd.y = GetSystemMetrics(SM_CYSCREEN); //1080
szwnd.x = (1280/2); //640
szwnd.y = (1024/2); //512
pwnd.x = (scwnd.x-szwnd.x)/2; //(1920-640)/2=640
pwnd.y = (scwnd.y-szwnd.y)/2; //(1080-512)/2=284

rectmainwnd.left = pwnd.x; //640
rectmainwnd.right = pwnd.x + szwnd.x; //1280
rectmainwnd.top = pwnd.y; //
rectmainwnd.bottom = pwnd.y + szwnd.y;

AdjustWindowRectEx(&rectmainwnd, WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, TRUE, 0);
szwnd.x = rectmainwnd.right-rectmainwnd.left;
szwnd.y = rectmainwnd.bottom-rectmainwnd.top;

dapp[0].hWnd = hDlgAbout;
dapp[0].WndProc = AboutWndProc;

dapp[1].hWnd = hDlgConsole;
dapp[1].WndProc = ConsoleWndProc;

}