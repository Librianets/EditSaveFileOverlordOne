#include <windows.h> 		// WINDOWS
#include <iostream>			// Language C++
#include <vector>			// Language C++
using std::vector;

#include "packunpack.hpp"	// project
#include "saveinfo.hpp"		// project
#include "resource.hpp"		// project

#include "global.hpp"		// project
#include "functions.hpp"	// project
#include "mainfuncs.hpp"	// project

#include "logging.hpp"		// project
#include "debug.hpp"		// project

BOOL CALLBACK ConsoleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class CDebugInfo 	Cdbg;
class CAppLogging 	CALog;
class CAppConsole 	CACon;

static wchar_t aMessageErrorTxt 	[MAXMSGLEN] = L"Ошибка";
static wchar_t aMessageWarningTxt 	[MAXMSGLEN] = L"Предупреждение";

TMessageErrorTxt aMsgErrorTxt[32] //2+2+2*64=132*50=6600 Байт (на каждыйе 30 элементов)
{
	{0, ERROR_NOTCORRECT, 		L"Не известная ошибка"},
	{1, ERROR_GWNDNOT, 			L"Не удалось создать главное окно"},
	{2, ERROR_GCLASSNOT, 		L"Не удалось зарег. главный класс окна"},
	{3, ERROR_ACCELNOT, 		L"Проблемы с таблицей акселератов"},
//	{ERROR_FILECHECK, 			L"Не удалось создать главное окно"},
	{4, ERROR_CREATECONSOLE, 	L"Не удалось создать консоль"},
	{5, ERROR_OPENFILE, 		L"Не удалось открыть файл"},
	{6, ERROR_FILESIZE, 		L"Не удалось установить размер файла"},
	{7, ERROR_SAVEFILE, 		L"Не удалось сохранить файл"},
	{8, 0, 		L"Не удалось установить количество сохранений"},
	{9, ERROR_LIMITMAXSIZE, 	L"Превышен лимит размера файла ( > 1 мб)"},
//	{ERROR_NOTFILESELECT, 		L"Открытие файла отменено"},
	{10, 0, 					L""},
	{11, 0, 					L""},
	{12, 0, 					L""},
	{13, 0, 					L""},
	{14, 0, 					L""},
	{15, 0, 					L""},
	{16, 0, 					L""},
	{17, 0, 					L""},
	{18, 0, 					L""},
	{19, 0, 					L""},
	
//PACKLIB
	{20, 0, 					L""},
	{21, E_LIBPACK_CHECKSUM, 	L"Суммы не совпадают"},
	{22, E_LIBPACK_TYPEFILE, 	L"Не удалось установить тип файла"},
	{23, E_LIBPACK_CHECKCRC32, 	L"Crc32 не совпадают"},
	{24, E_LIBPACK_DECOMPRESS, 	L"Распаковка не удалась"},
	{25, E_LIBPACK_COMPRESS, 	L"Упаковка не удалась"},
	{26, E_LIBPACK_CHECKCONST, 	L"Отсутствуют константы в файле"},
//	{E_LIBPACK_CHECKLANG, 		L"Не удалось установить язык"}	
	{27, 0, 					L""},
	{28, 0, 					L""},
	{29, 0, 					L""},
//SAVEINFO
	{30, 0, 					L""},
	{31, 0, 					L""}
};

void CAppLogging::ErrorMsg(int iMSG, int iCategory)
{
int iExit = 0;
int flag_find = 0;

switch (iCategory)
{
	case APP:
	{
		for (int i = APP, a = i+20;i < a;i++)
		{
			if (aMsgErrorTxt[i].iMsgNum == iMSG)
			{
				if 
				(
				aMsgErrorTxt[i].iMsgNum == ERROR_GWNDNOT 
				|| 
				aMsgErrorTxt[i].iMsgNum == ERROR_GCLASSNOT
				)
				{
					MessageBox(NULL, aMsgErrorTxt[i].aMessageError, aMessageErrorTxt, MB_OK);
					iExit = 1;
				} 
				else
				{
					MessageBox(NULL, aMsgErrorTxt[i].aMessageError, aMessageWarningTxt, MB_OK);
				}
				flag_find = 1;
				break;
			}
		}
	}break;
	
	case PACKLIB:
	{
		for (int i = 10*PACKLIB, a = i+10;i < a;i++)
		{
			if (aMsgErrorTxt[i].iMsgNum == iMSG)
			{
				MessageBox(NULL, aMsgErrorTxt[i].aMessageError, aMessageWarningTxt, MB_OK);
				flag_find = 1;
				break;
			}
		}
	}break;	
	
	case SI:
	{
		for (int i = 10*SI, a = i+10; i < a; i++)
		{
			if (aMsgErrorTxt[i].iMsgNum == iMSG)
			{
				MessageBox(NULL, aMsgErrorTxt[i].aMessageError, aMessageWarningTxt, MB_OK);
				flag_find = 1;
				break;
			}
		}
	}break;
	
	case SS:
	{
		for (int i = 10*SS, a = i+10; i < a; i++)
		{
			if (aMsgErrorTxt[i].iMsgNum == iMSG)
			{
				MessageBox(NULL, aMsgErrorTxt[i].aMessageError, aMessageWarningTxt, MB_OK);
				flag_find = 1;
				break;
			}
		}
	}break;
	
	
	default:		MessageBox(NULL, aMsgErrorTxt[0].aMessageError, aMessageWarningTxt, MB_OK);	break;
}

if (flag_find !=1) {MessageBox(NULL, aMsgErrorTxt[0].aMessageError, aMessageWarningTxt, MB_OK);}
if (iExit == 1) {PostQuitMessage(WM_DESTROY);}	
}

void CAppConsole::WriteDlgConsole(wchar_t *aBufMsg)
{
	SendDlgItemMessage((HWND)hWndConsole, IDI_CONSOLE_EDIT, EM_REPLACESEL, 0, (LPARAM)aBufMsg);
}

void CAppConsole::InitConsole(void)
{
	hWndConsole = CreateDialog((HINSTANCE)hInstanceapp, MAKEINTRESOURCE(IDDLG_CONSOLE), (HWND)hWndapp, ConsoleWndProc);
	if ((HWND)hWndConsole == NULL) errormsg(ERROR_CREATECONSOLE, APP);
	hMenuConsole = LoadMenu((HINSTANCE)hInstanceapp, MAKEINTRESOURCE(IDM_MENU_CONSOLE));
	SetMenu((HWND)hWndConsole, (HMENU)(HMENU)hMenuConsole);

	info(L"Project: ESD overlord", L"");
	info(L"\r\nTEST ТЕСТ. i=%i, c=%c, f=%f, s=%ls \r\n", 5, 't', 5.5, L"ТЕСТ TEST");
}

void CAppConsole::ConsoleShow(void)
{
	POINT console_pos_temp;
	RECT t_poswnd;
	RECT t_posdia;
	GetWindowRect((HWND)hWndapp, &t_poswnd);
	GetWindowRect((HWND)hWndConsole, &t_posdia);
	console_pos_temp.x = t_posdia.right - t_posdia.left;
	console_pos_temp.y = t_posdia.bottom - t_posdia.top;
	t_poswnd.left += ((t_poswnd.right-t_poswnd.left-console_pos_temp.x)/2);
	t_poswnd.top += ((t_poswnd.bottom-t_poswnd.top-console_pos_temp.y)/2);
	console_pos_temp.x = t_poswnd.left;
	console_pos_temp.y = t_poswnd.top;
	
	SetWindowPos((HWND)hWndConsole, HWND_TOP, console_pos_temp.x,(console_pos_temp.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
	ShowWindow((HWND)hWndConsole, SW_SHOW);
}

void CAppConsole::ConsoleHide(void)
{
	ShowWindow((HWND)hWndConsole, SW_HIDE);
}

void CAppConsole::ConsoleClear(void)
{
	SendDlgItemMessage((HWND)hWndConsole, IDI_CONSOLE_EDIT, WM_SETTEXT, 0, (LPARAM)L"");
}

void CAppConsole::ConsoleGetLine(void)
{
	wchar_t sTempLine[70];
	GetDlgItemText((HWND)hWndConsole, IDI_CONSOLELINE, sTempLine, sizeof(sTempLine));
	info(L"%ls", sTempLine);
}

BOOL CALLBACK ConsoleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG: 					return TRUE;break;
		case WM_CLOSE: CACon.ConsoleHide();	return TRUE;break;
		case WM_COMMAND:
		{
		if (HIWORD(wParam) == 0)
		{
			switch (LOWORD(wParam))
			{
				case IDI_EXIT: 				PostQuitMessage(WM_DESTROY);		return TRUE;break;
				case IDI_CONSOLE_CLEAR: 	CACon.ConsoleClear();				return TRUE;break;
				case IDI_CONSOLE_HIDE: 		CACon.ConsoleHide();				return TRUE;break;
				case IDI_GETLINECONSOLE:	CACon.ConsoleGetLine();			return TRUE;break;
			}
		}
		}
	}

return FALSE;
}