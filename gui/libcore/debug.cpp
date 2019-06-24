#include <iostream>			// Language C++
#include <cstdarg>			// Language C++

#include "debug.hpp"

void CDebugInfo::Debug(const wchar_t *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
	
	/*
	
	Добавить обработчик logfile
	
	*/
}

void CDebugInfo::Info(const wchar_t *fmt, ...)
{
	va_list list;
	va_start(list, fmt);
	vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
}

CDebugInfo::CDebugInfo(){}
CDebugInfo::~CDebugInfo(){ClearClass();}
void CDebugInfo::ClearClass(void){}

wchar_t *CDebugInfo::lpGetGlobalMsg(void)
{
	return sGlobalMsg;
}