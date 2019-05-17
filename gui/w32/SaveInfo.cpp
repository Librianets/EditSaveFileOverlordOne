#include "global.hpp"


void StringConvert()
{
	int count;
	memcpy (&count, &aBufferOne[0xCB], 4);

	vector<wchar_t> bufstr;
	bufstr.reserve(count);

	memset (&bufstr[0x0], 0, count*sizeof(wchar_t));
	memcpy (&bufstr[0x0], &aBufferOne[0xCB+0x4], count);
	
	unsigned char *Buf = (unsigned char*)&bufstr[0x0];
	
	int asd = 0xD0;
	for (int i = 0; i < count/2; i++)
	{
		if ( memcmp( &Buf[i*2], &asd, 1) == 0)
		{Buf[i*2]-=0xCC;Buf[i*2+1]-=0x80;} else {Buf[i*2]-=0xCD;Buf[i*2+1]-=0x40;}
	}
	
	for (int i = 0; i < count/2; i++)
	{
		unsigned char temp = 0x0;
		temp = Buf[i*2];
		Buf[i*2] = Buf[i*2+1];
		Buf[i*2+1] = temp;
	}
	log(L"bufstr1 = %ls", Buf);

}

struct
{
	void *lpSaveInfo[11];
	int iSaveInfo[11];
} SaveInfoBuf, *lpSaveInfoBuf;

void Define(void* aBuf)
{
	
	unsigned char *Buf = (unsigned char*) &aBuf;
	unsigned int temp = 0;
	
	
	
	switch (Buf[0xB])
	{
		case 0x01: 
		{
			iFlagSaveCount = SAVECOUNT1;
			for (int i = 1; i <= Buf[0xB]; i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));}
			lpSaveInfoBuf->lpSaveInfo[0] = &Buf[0xA];
			lpSaveInfoBuf->iSaveInfo[1] = 4;
			
			lpSaveInfoBuf->lpSaveInfo[1] = &Buf[0xA+4];
			lpSaveInfoBuf->iSaveInfo[1] = &Buf[0xA+4];
			break;
		}
		
		case 0x02: iFlagSaveCount = SAVECOUNT2; for (int i = 1; i <= Buf[0xB]; i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
		
		case 0x82:
		{
		switch (Buf[0xC])
		{
			case 0x01: iFlagSaveCount = SAVECOUNT3; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
			
			case 0x02: iFlagSaveCount = SAVECOUNT4; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
			
			case 0x03: iFlagSaveCount = SAVECOUNT5; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
			
			case 0x04: iFlagSaveCount = SAVECOUNT6; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
			
			case 0x05: iFlagSaveCount = SAVECOUNT7; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
			
			case 0x06: iFlagSaveCount = SAVECOUNT8; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
			
			case 0x07: iFlagSaveCount = SAVECOUNT9; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
			
			case 0x08: iFlagSaveCount = SAVECOUNT10; for (int i = 1; i <= (Buf[0xB]+2); i++) {SetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[Buf[i]], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));} break;
		}
		break;
		}
		default: iFlagSaveCount = ERRORSAVECOUNT; Error(ERROR_CHECKCONST, ERROR_NOTEXITAPP); break; //переделать
	}
	
	switch (iFlagSaveCount)
	{
		case SAVECOUNT1: break;
	}
}