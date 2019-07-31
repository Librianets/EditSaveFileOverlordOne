#include <iostream>			// Language C++
#include <cstdarg>			// Language C++
#include <cstring>			// Language C++

#include "debug.hpp"
#include "logging.hpp"		// project

CDebugInfo::CDebugInfo(){}
CDebugInfo::~CDebugInfo(){ClearClass();}
void CDebugInfo::ClearClass(void){}

wchar_t *CDebugInfo::lpGetGlobalMsg(void)
{
	return sGlobalMsg;
}

void CDebugInfo::Debug(const wchar_t *fmt, ...)
{
	memset(sGlobalMsg, 0, sizeof(sGlobalMsg));
	int iNumCount = 0;
	
	va_list list;
	va_start(list, fmt);
	iNumCount = vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
	
	#ifdef DEBUGLOG
	WriteLog(1, iNumCount);
	#endif
}

void CDebugInfo::Info(const wchar_t *fmt, ...)
{
	memset(sGlobalMsg, 0, sizeof(sGlobalMsg));
	int iNumCount = 0;
	
	va_list list;
	va_start(list, fmt);
	iNumCount = vswprintf(sGlobalMsg, sizeof(sGlobalMsg), fmt, list);
	va_end(list);
	
	#ifdef INFOLOG
	WriteLog(0, iNumCount);
	#endif
}

void CDebugInfo::WriteLog(int iLogSwitch, int iNumCount)
{
	if (iNumCount < 0) {return;} else {}
	
	FILE *pFile;
	wchar_t sDebug [32] =  L"debug.log";
	wchar_t sInfo [32] =  L"info.log";
	wchar_t sPathfull [512] = {0};
	if (iLogSwitch == 0)
	{
		wcscat(sPathfull, sPathFilelog);
		wcscat(sPathfull, sInfo);
		pFile = _wfopen (sPathfull, L"a+b");
	} else {}
	
	if (iLogSwitch == 1)
	{
		wcscat(sPathfull, sPathFilelog);
		wcscat(sPathfull, sDebug);
		pFile = _wfopen (sPathfull, L"a+b");
	} else {}
	
	if (pFile != NULL) {fwrite(sGlobalMsg, iNumCount, sizeof(wchar_t), pFile);} else {return;}
	fclose(pFile);
	
}

void CDebugInfo::SetPath(wchar_t *Path, int iSizePath)
{
	for (int i = 0; i <= iSizePath; i++)
	{
		sPathFilelog[i] = Path[i];
	}
}