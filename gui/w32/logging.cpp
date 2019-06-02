#include "global.hpp"

class CLogging Log;

void CLogging::ClearClass(void)
{
	
}

CLogging::CLogging()
{
	WndProc = *ConsoleWndProc;
}

CLogging::~CLogging()
{
	ClearClass();
}

void CLogging::ErrorMsg(int iMSG)
{	
	int iExit = 0;
	switch (iMSG)
	{
	case ERROR_GWNDNOT: 		{MessageBox(NULL, sWndNot, sError, MB_OK); iExit = APPEXIT;} break;
	case ERROR_GCLASSNOT: 		{MessageBox(NULL, sClassNot, sError, MB_OK); iExit = APPEXIT;} break;
	case ERROR_ACCELNOT: 		MessageBox(NULL, sAccaelNot, sError, MB_OK); break;
	case ERROR_FILECHECK: 		MessageBox(NULL, sFileSelect, sWarning, MB_OK); break;
	case ERROR_CONSOLE: 		MessageBox(NULL, sConsole, sWarning, MB_OK); break; 
	case ERROR_OPENFILE: 		MessageBox(NULL, sOpenFile, sWarning, MB_OK); break;
	case ERROR_FILESIZE: 		MessageBox(NULL, sFileSize, sWarning, MB_OK); break;
	case ERROR_CHECKCONST: 		MessageBox(NULL, sFailCheckConst, sWarning, MB_OK); break;
	case ERROR_CHECKCRC32: 		MessageBox(NULL, sCheckCrc32, sWarning, MB_OK); break;
	case ERROR_DECOMPRESS: 		MessageBox(NULL, sDecompress, sWarning, MB_OK); break;
	case ERROR_CHECKSUM: 		MessageBox(NULL, sCheckSum, sWarning, MB_OK); break;
	case ERROR_COMPRESS: 		MessageBox(NULL, sCompress, sWarning, MB_OK); break;
	case ERROR_OPENSAVEFILE: 	MessageBox(NULL, sOpenSave, sWarning, MB_OK); break;
	case ERROR_SAVECOUNT: 		MessageBox(NULL, sSaveCount, sWarning, MB_OK); break;
	case FAILURE: 				break;
	default: 					MessageBox(NULL, sNotErrorCorrect, sError, MB_OK); break;
	}
	
	if (iExit == APPEXIT){PostQuitMessage(WM_DESTROY);}
}
/*
void CLogging::Debug(const wchar_t *fmt, ...)
{
#ifdef DEBUG
	va_list list;
	DWORD tmp;
	va_start(list, fmt);
	vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
	
#ifdef WINAPIPROJECT
	WriteDlgConsole(hWndConsole);
#else

#endif //WINAPIPROJECT
#endif //WINAPIPROJECT
}
*/
void CLogging::Log(const wchar_t *fmt, ...)
{

	va_list list;
	DWORD tmp;
	va_start(list, fmt);
	vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
	
#ifdef WINAPIPROJECT
	WriteDlgConsole(hWndConsole);
#else

#endif //WINAPIPROJECT

}

void CLogging::WriteDlgConsole(HWND hwnd)
{
	SendDlgItemMessage(hwnd, IDI_CONSOLE_EDIT, EM_REPLACESEL, 0, (LPARAM)sGlobalMsg);
}

void CLogging::InitConsole(void)
{
#ifdef WINAPIPROJECT
hWndConsole = CreateDialog(hInstanceapp, MAKEINTRESOURCE(IDDLG_CONSOLE), hWndapp, WndProc);
if (hWndConsole == NULL) ErrorMsg(ERROR_CONSOLE);
hMenuConsole = LoadMenu(hInstanceapp, MAKEINTRESOURCE(IDM_MENU_CONSOLE));
SetMenu(hWndConsole, hMenuConsole);
SetPosDlg(hWndapp, hWndConsole);
SetWindowPos(hWndConsole, HWND_TOP, CGG.t_xy_dia.x,(CGG.t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
ShowWindow(hWndConsole, SW_HIDE);

Log(L"Project: ESD overlord. \r\n");
Log(L"TEST ТЕСТ. i=%i, c=%c, f=%f, s=%ls, wc=%ls \r\n", 5, 't', 5.5, L"ТЕСТ TEST", sGlobalMsg);
#else

#endif
}

void CLogging::ConsoleShow(void)
{
#ifdef WINAPIPROJECT
	SetPosDlg(hWndapp, hWndConsole);
	SetWindowPos(hWndConsole, HWND_TOP, CGG.t_xy_dia.x,(CGG.t_xy_dia.y+(-25+Y_CONSOLE_DLG)*2), 0, 0, SWP_NOSIZE );
	ShowWindow(hWndConsole, SW_SHOW);
#else

#endif
}

void CLogging::ConsoleHide(void)
{
#ifdef WINAPIPROJECT
	ShowWindow(hWndConsole, SW_HIDE);
#else

#endif
}

void CLogging::ConsoleClear(void)
{
#ifdef WINAPIPROJECT
	SendDlgItemMessage(hWndConsole, IDI_CONSOLE_EDIT, WM_SETTEXT, 0, (LPARAM)L"");
#else

#endif
}

void CLogging::ConsoleGetLine(void)
{
#ifdef WINAPIPROJECT
	wchar_t sTempLine[70];
	GetDlgItemText(hWndConsole, IDI_CONSOLELINE, sTempLine, sizeof(sTempLine));
	Log(L"%ls", sTempLine);
#else

#endif
}