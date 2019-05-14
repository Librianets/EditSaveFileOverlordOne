#include "global.hpp"

RECT RECTmainwnd;

HWND hDlgAbout;
HWND hDlgConsole;
HACCEL hAccel;
HWND hLogo;
HANDLE hFileOpen;

HDC			hDC;
HDC			hDC2;
HBITMAP		hBm;
BITMAP		bm;

WNDCLASSEX WndCMain;

AppData gapp;
Data dlgapp[MAXCOUNTERPOINTER];
sizeall scwnd, szwnd, pwnd, t_xy_dia;

OPENFILENAME ofn;

wchar_t sgClass[MAXCLASSNAME] 		= L"Class main window";
wchar_t sgWnd[MAXCLASSNAME] 		= L"Редактор сохранений игры Overlord";



wchar_t sGlobalMsg[MAXPATHLEN]		= L"TEST TEST TEST";

unsigned char aGlobalBuffer[0x10000];
unsigned char aBufferDecomp[0x10000];

void ClearVal(void)
{

}

void InitiationVal(HINSTANCE hInstance)
{

gapp.inst = NULL;
gapp.wnd = NULL;
gapp.menu = NULL;
gapp._class = sgClass;
gapp._wnd = sgWnd;
gapp.inst = hInstance;
gapp.WndProc = *MainWndProc;

scwnd.x = GetSystemMetrics(SM_CXSCREEN); //1920
scwnd.y = GetSystemMetrics(SM_CYSCREEN); //1080
szwnd.x = (1280/2); //640
szwnd.y = (1024/2); //512
pwnd.x = (scwnd.x-szwnd.x)/2; //(1920-640)/2=640
pwnd.y = (scwnd.y-szwnd.y)/2; //(1080-512)/2=284

RECTmainwnd.left = pwnd.x; //640
RECTmainwnd.right = pwnd.x + szwnd.x; //1280
RECTmainwnd.top = pwnd.y; //
RECTmainwnd.bottom = pwnd.y + szwnd.y;

AdjustWindowRectEx(&RECTmainwnd, WS_CAPTION | WS_POPUPWINDOW | WS_MINIMIZEBOX, TRUE, 0);
szwnd.x = RECTmainwnd.right-RECTmainwnd.left;
szwnd.y = RECTmainwnd.bottom-RECTmainwnd.top;

dlgapp[0].hWnd = hDlgAbout;
dlgapp[0].WndProc = AboutWndProc;

dlgapp[1].hWnd = hDlgConsole;
dlgapp[1].WndProc = ConsoleWndProc;


}