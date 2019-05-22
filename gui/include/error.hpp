#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#define FAILURE					-0x0001
#define SUCCESS					 0x0000

#define ERROR_EXIT_APP 			-0x2000 // флаг аварийного завершения программы
#define ERROR_NOTEXITAPP 		-0x1000 // флаг продолжения работы программы
#define ERROR_GWNDNOT 			-0x0001
#define ERROR_GCLASSNOT 		-0x0002
#define ERROR_ACCELNOT 			-0x0003
#define ERROR_FILECHECK 		-0x0004
#define ERROR_CONSOLE 			-0x0005
#define ERROR_OPENFILE 			-0x0006
#define ERROR_FILESIZE 			-0x0007
#define ERROR_CHECKCONST 		-0x0008
#define ERROR_CHECKCRC32 		-0x0009
#define ERROR_DECOMPRESS 		-0x000A
#define ERROR_CHECKSUM 			-0x000B
#define ERROR_COMPRESS 			-0x000C
#define ERROR_OPENSAVEFILE 		-0x000D
#define ERROR_SAVECOUNT 		-0x000E
#define ERROR_LIMITMAXSIZE 		-0x000F
#define ERROR_NOTFILESELECT 	-0x0010 //16
#define ERROR_FAILCHECKCONST	-0x0011 //17
#define ERROR_FAILCHECKLANG		-0x0012 //18
void Error (int msg, int flag_exit);

#endif //__ERROR_HPP__