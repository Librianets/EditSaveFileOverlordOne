#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

extern HANDLE hConsole;
void logging (wchar_t nametype, typeval val);
void openconsole (void);
void closeconsole (void);
void writeconsole (void);

#endif //__CONSOLE_HPP__