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

void Error (int msg, int flag_exit);

#endif //__ERROR_HPP__