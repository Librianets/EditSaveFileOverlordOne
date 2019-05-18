#include "global.hpp"

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpszCmdParam, int nCmdShow)
{
	InitiationVal(hInstance);
	CreateMainWindow();
	InitConsole();
	/*
	log(L"sizeof short %i", sizeof(short));
	log(L"sizeof short int %i", sizeof(short int));
	log(L"sizeof int %i", sizeof(int));
	log(L"sizeof long int %i", sizeof(long int));
	log(L"sizeof long long int %i", sizeof(long long int));
	log(L"sizeof float %i", sizeof(float));
	log(L"sizeof double %i", sizeof(double));
	log(L"sizeof long long %i", sizeof(long long));
	log(L"sizeof char %i", sizeof(char));
	log(L"sizeof wchar_t %i", sizeof(wchar_t));
*/
	RunMsg();
return 0;	
}

/*
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