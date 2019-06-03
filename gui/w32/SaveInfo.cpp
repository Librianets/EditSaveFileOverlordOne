#include "global.hpp"		// project

vector <unsigned char> *CSaveInfo::lpGetBuffer(void)
{
	return &aBufferTemp;
}

CSaveInfo::CSaveInfo()
{
	ClearClass();
}

CSaveInfo::~CSaveInfo()
{
	ClearClass();
	aBufferTemp.~vector();
}

void CSaveInfo::ClearClass(void)
{
	if (aBufferTemp.capacity() > 1) {aBufferTemp.clear();} else {}
	for (int i = 0; i < 10; i++)
	{
		if (SaveInfoStructOne.data.aDataSave[i].capacity() > 0)
		{
			SaveInfoStructOne.data.aDataSave[i].clear();
			SaveInfoStructOne.data.aDataSave[i].resize(0);
		}
		SaveInfoStructOne.count.iCount[i] = 0x0;
		SaveInfoStructOne.header.count = 0x0;
		SaveInfoStructOne.header.numbersize = 0x0;
	}
	
}

void CSaveInfo::StringConvert(void)
{
/*	int count;
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
	//Log(L"bufstr1 = %ls", Buf);
*/
}

int CSaveInfo::DisassemblySI(void)
{
	memcpy (&SaveInfoStructOne.header.count, &aBufferTemp[0xA], 4);
#ifdef DEBUG
Log.Log(L"\r\nInfo->header.count = %i", SaveInfoStructOne.header.count); Log.Log(L"\r\n0xB = %X, 0xC = %X", aBufferTemp[0xB], aBufferTemp[0xC]);
#endif
	switch (aBufferTemp[0xB])
	{
		case 0x01: 
		{
			iFlagSaveCount = SAVECOUNT1;
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = ( SaveInfoStructOne.header.numbersize - iSave[iFlagSaveCount] );
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
#ifdef DEBUG
Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
Log.Log(L"\r\nSaveInfoStructOne.count.iCount[SAVECOUNT1] = %i", SaveInfoStructOne.count.iCount[SAVECOUNT1]);
Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = %i", SaveInfoStructOne.listfile.iOffset[SAVECOUNT1]);
#endif
			InitVectorSI(SAVECOUNT1);
		}break;
		
		case 0x02:
		{
			iFlagSaveCount = SAVECOUNT2;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0xF] + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			InitVectorSI(SAVECOUNT1);
			InitVectorSI(SAVECOUNT2);
		}break;
		
		case 0x82:
		{
		switch (aBufferTemp[0xC])
		{
			case 0x01:
			{
			iFlagSaveCount = SAVECOUNT3;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif 
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}
			}break;
			
			case 0x02:
			{
			iFlagSaveCount = SAVECOUNT4;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			SaveInfoStructOne.count.iCount[SAVECOUNT4] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT4];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}
			}break;
			
			case 0x03:
			{
			iFlagSaveCount = SAVECOUNT5;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			SaveInfoStructOne.count.iCount[SAVECOUNT4] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT4];
			SaveInfoStructOne.count.iCount[SAVECOUNT5] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT5];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}
			}break;
			
			case 0x04:
			{
			iFlagSaveCount = SAVECOUNT6;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			SaveInfoStructOne.count.iCount[SAVECOUNT4] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT4];
			SaveInfoStructOne.count.iCount[SAVECOUNT5] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT5];
			SaveInfoStructOne.count.iCount[SAVECOUNT6] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT6];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}
			}break;
			
			case 0x05:
			{
			iFlagSaveCount = SAVECOUNT7;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			SaveInfoStructOne.count.iCount[SAVECOUNT4] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT4];
			SaveInfoStructOne.count.iCount[SAVECOUNT5] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT5];
			SaveInfoStructOne.count.iCount[SAVECOUNT6] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT6];
			SaveInfoStructOne.count.iCount[SAVECOUNT7] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT7];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}
			}break;
			
			case 0x06:
			{
			iFlagSaveCount = SAVECOUNT8;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT8] = ((aBufferTemp[0x41] << 8) | aBufferTemp[0x40]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			SaveInfoStructOne.count.iCount[SAVECOUNT4] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT4];
			SaveInfoStructOne.count.iCount[SAVECOUNT5] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT5];
			SaveInfoStructOne.count.iCount[SAVECOUNT6] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT6];
			SaveInfoStructOne.count.iCount[SAVECOUNT7] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT8] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT7];
			SaveInfoStructOne.count.iCount[SAVECOUNT8] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT8];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}			
			}break;
			
			case 0x07:
			{
			iFlagSaveCount = SAVECOUNT9;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT8] = ((aBufferTemp[0x41] << 8) | aBufferTemp[0x40]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT9] = ((aBufferTemp[0x49] << 8) | aBufferTemp[0x48]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			SaveInfoStructOne.count.iCount[SAVECOUNT4] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT4];
			SaveInfoStructOne.count.iCount[SAVECOUNT5] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT5];
			SaveInfoStructOne.count.iCount[SAVECOUNT6] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT6];
			SaveInfoStructOne.count.iCount[SAVECOUNT7] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT8] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT7];
			SaveInfoStructOne.count.iCount[SAVECOUNT8] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT9] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT8];
			SaveInfoStructOne.count.iCount[SAVECOUNT9] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT9];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}
			}break;
			
			case 0x08:
			{
			iFlagSaveCount = SAVECOUNT10;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT8] = ((aBufferTemp[0x41] << 8) | aBufferTemp[0x40]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT9] = ((aBufferTemp[0x49] << 8) | aBufferTemp[0x48]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT10] = ((aBufferTemp[0x51] << 8) | aBufferTemp[0x50]) + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT3];
			SaveInfoStructOne.count.iCount[SAVECOUNT4] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT4];
			SaveInfoStructOne.count.iCount[SAVECOUNT5] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT6] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT5];
			SaveInfoStructOne.count.iCount[SAVECOUNT6] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT7] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT6];
			SaveInfoStructOne.count.iCount[SAVECOUNT7] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT8] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT7];
			SaveInfoStructOne.count.iCount[SAVECOUNT8] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT9] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT8];
			SaveInfoStructOne.count.iCount[SAVECOUNT9] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT10] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT9];
			SaveInfoStructOne.count.iCount[SAVECOUNT10] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[SAVECOUNT10];
			
#ifdef DEBUG
	Log.Log(L"\r\niFlagSaveCount = %i", iFlagSaveCount);
	for (int l = 0x0; l <= iFlagSaveCount; l++)
	{
		Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %X", l, SaveInfoStructOne.listfile.iOffset[l]);
		Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%i] = %X", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
			for (int l = 0; l <= iFlagSaveCount; l++)
			{
				InitVectorSI(l);
			}
			}break;
			
			default: iFlagSaveCount = ERRORSAVECOUNT; return ERROR_SAVECOUNT; break;
		}
		}break;
		
		default: iFlagSaveCount = ERRORSAVECOUNT; return ERROR_SAVECOUNT; break;
	}
	switch (iFlagSaveCount)
	{
		case SAVECOUNT1: break;
	}
	
return SUCCESS;
}

int CSaveInfo::AssemblySI(void)
{
	if (aBufferTemp.capacity() > 1) {aBufferTemp.clear();} else {return FAILURE;}
	SaveInfoStructOne.header.numbersize = 0x0;
	int iPos = 0x0;
	for (int i = 0; i < 10; i++)
	{
		SaveInfoStructOne.header.numbersize += SaveInfoStructOne.data.aDataSave[i].size();
		Log.Log(L"\r\n aDataSave[%i].size = %X (%i)", i, SaveInfoStructOne.data.aDataSave[i].size(), SaveInfoStructOne.data.aDataSave[i].size());
	}
	aBufferTemp.resize(SaveInfoStructOne.header.numbersize + iSave[iFlagSaveCount]);
	
	memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.header.reserved, 4); iPos += 0x4;
	memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.header.const02, 4); iPos += 0x4;
	memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.header.const01, 2); iPos += 0x2;
	switch (iFlagSaveCount)
	{
		case SAVECOUNT1:
		{
			memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.listfile.iConst2[0], 4); iPos += 0x4;
		}break;
		
		case SAVECOUNT2:
		{
			memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.listfile.iConst2[1], 4); iPos += 0x4;
			short int temp = (short int) (SaveInfoStructOne.count.iCount[0] << 8 | 0x01);
			memcpy(&aBufferTemp[iPos], &temp, 2); iPos += 0x2;
		}break;
		
		
		default: return ERRORSAVECOUNT;	
	}

	SaveInfoStructOne.header.numbersize += iPos;
	
	
	for(int i = 0; i < 10; i++)
	{
		memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.data.aDataSave[i][0x0], (size_t)SaveInfoStructOne.data.aDataSave[i].size());
		iPos += SaveInfoStructOne.data.aDataSave[i].size();
	}
	
	
	
	
	
	
	
	
	#ifdef DEBUG
	Log.Log(L"\r\n SaveInfoStructOne.header.numbersize = %i", SaveInfoStructOne.header.numbersize);
	for(int i = 0; i < SaveInfoStructOne.header.numbersize; i++)
	{
		if (i == 0) {Log.Log(L"\r\n");} else {}
		Log.Log(L"%02X, ", aBufferTemp[i] );
	}
	#endif

	
	return SUCCESS;	
}


int CSaveInfo::InitVectorSI(int num)
{
	if (iFlagSaveCount == ERROR_SAVECOUNT) {return ERROR_SAVECOUNT;}
	int position = iSave[iFlagSaveCount];
	
	SaveInfoStructOne.data.aDataSave[num].reserve( SaveInfoStructOne.count.iCount[num] );
	SaveInfoStructOne.data.aDataSave[num].clear();
	SaveInfoStructOne.data.aDataSave[num].resize( SaveInfoStructOne.count.iCount[num] );

	memcpy(&SaveInfoStructOne.data.aDataSave[num][0x0], &aBufferTemp[SaveInfoStructOne.listfile.iOffset[num]], SaveInfoStructOne.count.iCount[num]);
		
	CSaveInfoWndControlOne.SetWndLong(num);
	
#ifdef DEBUG
	Log.Log(L"\r\n size data = %X ", SaveInfoStructOne.data.aDataSave[num].size() );
	Log.Log(L"\r\nInitVectorSI, num = %i", num);
	Log.Log(L"\r\nposition = %i", position);
	Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%i] = %i", num, SaveInfoStructOne.count.iCount[num]);
	Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%i] = %i(0x%X)", num, SaveInfoStructOne.count.iCount[num], SaveInfoStructOne.count.iCount[num]);
	for(int l = 0; l < SaveInfoStructOne.count.iCount[num]; l++)
	{
		if (l == 0) {Log.Log(L"\r\n");} else {}
		Log.Log(L"%x, ", SaveInfoStructOne.data.aDataSave[num][l] );
	}
	
#endif

return SUCCESS;
}