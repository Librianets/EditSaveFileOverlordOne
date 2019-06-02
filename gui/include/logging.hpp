#ifndef __LOGGING_HPP__
#define __LOGGING_HPP__

extern class CLogging Log;

//#define log(fmt) Log.Log(fmt)//#define error(iMSG, iExit) Log.Error(iMSG, iExit)

#define APPEXIT 				-0x2000 // флаг аварийного завершения программы
#define NOTAPPEXIT 				-0x1000 // флаг продолжения работы программы

#define ERROR_GWNDNOT 			-0x0002
#define ERROR_GCLASSNOT 		-0x0003
#define ERROR_ACCELNOT 			-0x0004
#define ERROR_FILECHECK 		-0x0005
#define ERROR_CONSOLE 			-0x0006
#define ERROR_OPENFILE 			-0x0007
#define ERROR_FILESIZE 			-0x0008
#define ERROR_CHECKCONST 		-0x0009
#define ERROR_CHECKCRC32 		-0x000A
#define ERROR_DECOMPRESS 		-0x000B
#define ERROR_CHECKSUM 			-0x000C
#define ERROR_COMPRESS 			-0x000D
#define ERROR_OPENSAVEFILE 		-0x000E
#define ERROR_SAVECOUNT 		-0x000F
#define ERROR_LIMITMAXSIZE 		-0x0010
#define ERROR_NOTFILESELECT 	-0x0011 //16
#define ERROR_FAILCHECKCONST	-0x0012 //17
#define ERROR_FAILCHECKLANG		-0x0013 //18

class CLogging
{
public:
	CLogging();
	~CLogging();
	
	// public val
	HWND hWndConsole;
	HMENU hMenuConsole;
	HINSTANCE hInstanceapp;
	HWND hWndapp;
	
	// public funcs
	void ClearClass(void);
	void ErrorMsg(int iMSG);
	//void Debug(const wchar_t *fmt, ...);
	void Log(const wchar_t *fmt, ...);
	void WriteDlgConsole(HWND hwnd);
	void InitConsole(void);
	void ConsoleShow(void);
	void ConsoleHide(void);
	void ConsoleClear(void);
	void ConsoleGetLine(void);
	
private:
	DLGPROC WndProc;
	
	wchar_t sGlobalMsg[MAXPATHLEN]		= L"TEST TEST TEST";
	
	wchar_t sError[MAXMSGLEN] 			= L"Ошибка";
	wchar_t sWarning[MAXMSGLEN]			= L"Предупреждение";
	
	wchar_t sWndNot[MAXMSGLEN] 			= L"Не удалось создать главное окно";
	wchar_t sClassNot[MAXMSGLEN] 		= L"Не удалось зарегистрировать класс окна";
	wchar_t sAccaelNot[MAXMSGLEN] 		= L"Проблемы с таблицей акселератов";
	wchar_t sFileSelect[MAXMSGLEN] 		= L"Проблемы с файлом. Повторите попытку";
	wchar_t sConsole[MAXMSGLEN] 		= L"Не удалось создать консоль";
	wchar_t sOpenFile[MAXMSGLEN] 		= L"Не удалось открыть файл";
	wchar_t sFileSize[MAXMSGLEN] 		= L"Не удалось установить размер файла";
	wchar_t sFailCheckConst[MAXMSGLEN] 	= L"Файл не прошел проверку сигнатур";
	wchar_t sCheckCrc32[MAXMSGLEN] 		= L"Crc32 не совпадают";
	wchar_t sDecompress[MAXMSGLEN] 		= L"Распаковка провалилась";
	wchar_t sCheckSum[MAXMSGLEN] 		= L"Суммы не совпадают";
	wchar_t sCompress[MAXMSGLEN] 		= L"Упаковка провалилась";
	wchar_t sOpenSave[MAXMSGLEN] 		= L"Не удалось сохранить";
	wchar_t sNotErrorCorrect[MAXMSGLEN] = L"Не известная ошибка";
	wchar_t sSaveCount[MAXMSGLEN] 		= L"Не удалось установить количество сохранений";
};

#endif //__LOGGING_HPP__