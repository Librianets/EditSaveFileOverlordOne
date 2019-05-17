#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#define ERROR_EXIT_APP 			0x0001 // флаг аварийного завершения программы
#define ERROR_NOTEXITAPP 		0x0000 // флаг продолжения работы программы
#define ERROR_GWNDNOT 			0x0002
#define ERROR_GCLASSNOT 		0x0003
#define ERROR_ACCELNOT 			0x0004
#define ERROR_FILECHECK 		0x0005
#define ERROR_CONSOLE 			0x0006
#define ERROR_OPENFILE 			0x0007
#define ERROR_FILESIZE 			0x0008
#define ERROR_CHECKCONST 		0x0009
#define ERROR_CHECKCRC32 		0x0010
#define ERROR_DECOMPRESS 		0x0011
#define ERROR_CHECKSUM 			0x0012
#define ERROR_COMPRESS 			0x0013
#define ERROR_OPENSAVEFILE 		0x0014

void Error (int msg, int flag_exit);

extern wchar_t sError[MAXMSGLEN];
extern wchar_t sWarning[MAXMSGLEN];
extern wchar_t sWndNot[MAXMSGLEN];
extern wchar_t sClassNot[MAXMSGLEN];
extern wchar_t sAccaelNot[MAXMSGLEN];
extern wchar_t sFileSelect[MAXMSGLEN];
extern wchar_t sConsole[MAXMSGLEN];
extern wchar_t sGlobalMsg[MAXPATHLEN];
extern wchar_t sOpenFile[MAXMSGLEN];
extern wchar_t sFileSize[MAXMSGLEN];
extern wchar_t sFailCheckConst[MAXMSGLEN];
extern wchar_t sCheckCrc32[MAXMSGLEN];
extern wchar_t sDecompress[MAXMSGLEN];
extern wchar_t sCheckSum[MAXMSGLEN];
extern wchar_t sNotErrorCorrect[MAXMSGLEN];

#endif //__ERROR_HPP__