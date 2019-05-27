#ifndef __ERROR_CONSOLE_HPP__
#define __ERROR_CONSOLE_HPP__

void InitConsole(void);
void log(const wchar_t *fmt, ...);
void WriteDlgConsole(void);
void DlgConsoleShow(void);
void DlgConsoleHide(void);

#endif //__ERROR_CONSOLE_HPP__