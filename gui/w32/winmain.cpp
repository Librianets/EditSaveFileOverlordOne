#include "global.hpp"		// project

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpszCmdParam, int nCmdShow)
{
	int iStatus = 0;
	
	iStatus = CGG.Init(hInstance);
	if (iStatus == ERROR_GCLASSNOT) errormsg(ERROR_GCLASSNOT, APP);
	iStatus = 0;
	
	CGG.gapp.hwnd = CGG.CreateMainWndApp();
	if (CGG.gapp.hwnd == NULL) errormsg(ERROR_GWNDNOT, APP);
	
	CGG.ShowWnd(CGG.gapp.hwnd);
	
	CACon.hInstanceapp = CGG.gapp.inst;
	CACon.hWndapp = CGG.gapp.hwnd;
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

i		index					Индекс	int ix; Array[ix] = 10;
d		delta					Разница между значениями	int a, b; ... dba = b - a;
n		number					Количество	size_t nFound = 0;
a		argument				Аргумент	SomeClass::SomeClass(int aX) : x(aX) {}
*/