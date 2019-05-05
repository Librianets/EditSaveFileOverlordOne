#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#define exit_app 		0x0001 // флаг аварийного завершения программы
#define notexit_app 	0x0000 // флаг продолжения работы программы
#define gwndnot 		0x0002
#define gclassnot 		0x0003
#define gaccelnot 		0x0004

extern MSG msg;
void error (int msg, int flag_exit);

#endif //__ERROR_HPP__