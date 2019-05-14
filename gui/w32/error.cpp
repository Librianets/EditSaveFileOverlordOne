#include "global.hpp"



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

void Error (int msg, int flag_exit)
{//--HN
	
	switch (msg)
	{
	case ERROR_GWNDNOT: 		MessageBox(NULL, sWndNot, sError, MB_OK); break;
	case ERROR_GCLASSNOT: 		MessageBox(NULL, sClassNot, sError, MB_OK); break;
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
	}
	
	if (flag_exit == ERROR_EXIT_APP){PostQuitMessage(WM_DESTROY);}
}