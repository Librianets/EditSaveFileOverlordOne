#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

void logging();
void showconsole (void);
void hideconsole (void);
void closeconsole (void);
void log(const wchar_t *fmt, ...);

extern HANDLE hConsoleBuf;
extern HANDLE hConsole;
extern HANDLE hbufconsole;
extern HWND WndConsole;
extern wchar_t globalmsg [512];
void log2(const wchar_t *fmt, ...);

#endif //__CONSOLE_HPP__