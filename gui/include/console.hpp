#ifndef __CONSOLE_HPP__
#define __CONSOLE_HPP__

void initconsole(void);
void log(const wchar_t *fmt, ...);
void writedlgconsole(void);
void dlgconsoleshow(void);
void dlgconsolehide(void);

#endif //__CONSOLE_HPP__