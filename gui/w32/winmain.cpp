#include <windows.h> 		// WINDOWS
#include <iostream>			// Language C++
#include <vector>			// Language C++
using std::vector;

#include "global.hpp"		// project
#include "functions.hpp"	// project
#include "mainfuncs.hpp"	// project
#include "logging.hpp"		// project
#include "winmain.hpp"		// project

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpszCmdParam, int nCmdShow)
{
	COA.Init(hInstance);
	if (COA.GetErrorStatus() == ERROR_GCLASSNOT) errormsg(ERROR_GCLASSNOT, APP);
	
	COA.ParseCommandLine(lpszCmdParam);
	
	COA.gapp.hwnd = COA.CreateMainWndApp();
	if (COA.gapp.hwnd == NULL) errormsg(ERROR_GWNDNOT, APP); //поменять
	
	COA.ShowWnd(COA.gapp.hwnd);
	
	CACon.hInstanceapp = COA.gapp.inst;
	CACon.hWndapp = COA.gapp.hwnd;
	CACon.InitConsole();

	WPARAM ParamReturn = RunMsg();
	return ParamReturn;
}


//GdiplusStartupInput gdiplusStartupInput;
//ULONG_PTR gdiplusToken;
//GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
//WNDCLASSEX WndCTest;
//TestClass(WndCTest, TestWndProc, L"testClass", hInstance);
//HWND TESTS = CreateWindowEx(WS_EX_LAYERED, L"testClass", L"Textwind",  WS_POPUP | WS_DISABLED | WS_VISIBLE, 100, 100, 800, 400, NULL, NULL, hInstance, NULL);
//SetLayeredWindowAttributes(TESTS, 0, 100, LWA_ALPHA );
//GdiplusShutdown(gdiplusToken);

/*
by BYTE
c char
dw DWORD
fn Функция
lpsz



s		string					строка	sClientName
sz		zero-terminated string	строка, ограниченная нулевым символом	szClientName
n, i	int						целочисленная переменная	nSize, iSize
l		long					длинное целое	lAmount
b		boolean					булева переменная	bIsEmpty
a		array					массив	aDimensions
t, dt	time, datetime			время, дата и время	tDelivery, dtDelivery
p		pointer					указатель	pBox
lp		long pointer			двойной (дальний) указатель	lpBox
r		reference				ссылка	rBoxes
h		handle					дескриптор	hWindow
m_		member					переменная-член	m_sAddress
g_		global					глобальная переменная	g_nSpeed
C		class					класс	CString
T		type					тип	TObject
I		interface				интерфейс	IDispatch
v		void					отсутствие типа	vReserved

i		index					Индекс	int ix;Array[ix] = 10;
d		delta					Разница между значениями	int a, b;... dba = b - a;
n		number					Количество	size_t nFound = 0;
a		argument				Аргумент	SomeClass::SomeClass(int aX) : x(aX) {}

g_	префикс для глобальной переменной	 
m_	префикс для переменной класса	 
c	константа (префикс для типа)	const
l	длинный (префикс для типа)	far, long
p	указатель (префикс для типа)	*
ch	char	char
b	байт	BYTE, unsinged char
w	16-битное слово (2 байта)	WORD, unsigned short
dw	32-битное слово (4 байта)	DWORD, unsigned long
n,i	целое	int
flt	с плавающей точкой	float
dbl	с плавающей точкой	double
f	логическое	BOOL
sz	ASCIZ строка	char[]
psz	ASCIZ строка	char *
pcsz	константа ASCIZ строка	const char *
pv	произвольный указатель	void *
ppv	указатель на произвольный указатель	void **
h	хендл	HANDLE, void *
unk	OLE объект	IUnknown
punk	указатель на OLE объект	IUnknown *
disp	Automation объект	IDispatch
pdisp	указатель на Automation объект	IDispatch *
*/