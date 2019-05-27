#include "global.hpp"

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
	}
	memset(&SaveInfoStructOne, 0, sizeof(SaveInfoStruct));
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
	Log.Log(L"\r\nInfo->header.count = %i", SaveInfoStructOne.header.count);
	Log.Log(L"\r\n0xB = %i, 0xC = %i", aBufferTemp[0xB], aBufferTemp[0xC]);
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
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.header.numbersize - iSave[iFlagSaveCount] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];

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
	Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = %i", SaveInfoStructOne.listfile.iOffset[SAVECOUNT1]);
	Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = %i", SaveInfoStructOne.listfile.iOffset[SAVECOUNT2]);
	Log.Log(L"\r\nSaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = %i", SaveInfoStructOne.listfile.iOffset[SAVECOUNT3]);
	Log.Log(L"\r\nSaveInfoStructOne.count.iCount[SAVECOUNT1] = %i", SaveInfoStructOne.count.iCount[SAVECOUNT1]);
	Log.Log(L"\r\nSaveInfoStructOne.count.iCount[SAVECOUNT2] = %i", SaveInfoStructOne.count.iCount[SAVECOUNT2]);
	Log.Log(L"\r\nSaveInfoStructOne.count.iCount[SAVECOUNT3] = %i", SaveInfoStructOne.count.iCount[SAVECOUNT3]);
	
#endif
			InitVectorSI(SAVECOUNT1);
			InitVectorSI(SAVECOUNT2);
			InitVectorSI(SAVECOUNT3);
			}break;
			
			case 0x02:
/*			{
			iFlagSaveCount = SAVECOUNT4;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = (unsigned int)aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = (unsigned int)aBufferTemp[0x18] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = (unsigned int)aBufferTemp[0x20] + iSave[iFlagSaveCount];
			
			SaveInfoStructOne.count.iCount[SAVECOUNT1] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT1];
			SaveInfoStructOne.count.iCount[SAVECOUNT2] = SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];
			SaveInfoStructOne.count.iCount[SAVECOUNT3] = SaveInfoStructOne.header.numbersize - iSave[iFlagSaveCount] - SaveInfoStructOne.listfile.iOffset[SAVECOUNT2];

			InitVectorSI(SAVECOUNT1);
			InitVectorSI(SAVECOUNT2);
			InitVectorSI(SAVECOUNT3);
			
			
			
			
			
			
			
			
			
			
			SaveInfoStructOne.count.count0 = Buf[0x13];
			SaveInfoStructOne.listfile.offset0 = (save4);
			
			memcpy (&SaveInfoStructOne.listfile.offset1, &Buf[0x13], 1);
			memcpy (&SaveInfoStructOne.listfile.offset2, &Buf[0x18], 4);
			memcpy (&SaveInfoStructOne.listfile.offset3, &Buf[0x20], 4);
			SaveInfoStructOne.count.count1 = SaveInfoStructOne.listfile.offset2 - SaveInfoStructOne.listfile.offset1;
			SaveInfoStructOne.count.count2 = SaveInfoStructOne.listfile.offset3 - SaveInfoStructOne.listfile.offset2;
			SaveInfoStructOne.count.count3 = lenfileinfo-SaveInfoStructOne.listfile.offset3-save4;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save4+SaveInfoStructOne.listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save4+SaveInfoStructOne.listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save4+SaveInfoStructOne.listfile.offset3+0x15]);
			}break;
			
			case 0x03:
			{
			iFlagSaveCount = SAVECOUNT5;
			SaveInfoStructOne.count.count0 = Buf[0x13];
			SaveInfoStructOne.listfile.offset0 = (save5);
			
			memcpy (&SaveInfoStructOne.listfile.offset1, &Buf[0x13], 1);
			memcpy (&SaveInfoStructOne.listfile.offset2, &Buf[0x18], 4);
			memcpy (&SaveInfoStructOne.listfile.offset3, &Buf[0x20], 4);
			memcpy (&SaveInfoStructOne.listfile.offset4, &Buf[0x28], 4);
			SaveInfoStructOne.count.count1 = SaveInfoStructOne.listfile.offset2 - SaveInfoStructOne.listfile.offset1;
			SaveInfoStructOne.count.count2 = SaveInfoStructOne.listfile.offset3 - SaveInfoStructOne.listfile.offset2;
			SaveInfoStructOne.count.count3 = SaveInfoStructOne.listfile.offset4 - SaveInfoStructOne.listfile.offset3;
			SaveInfoStructOne.count.count4 = lenfileinfo-SaveInfoStructOne.listfile.offset4-save5;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+SaveInfoStructOne.listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+SaveInfoStructOne.listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+SaveInfoStructOne.listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+SaveInfoStructOne.listfile.offset4+0x15]);
			}break;
			
			case 0x04:
			{
			iFlagSaveCount = SAVECOUNT6;
			SaveInfoStructOne.count.count0 = Buf[0x13];
			SaveInfoStructOne.listfile.offset0 = (save6);
			
			memcpy (&SaveInfoStructOne.listfile.offset1, &Buf[0x13], 1);
			memcpy (&SaveInfoStructOne.listfile.offset2, &Buf[0x18], 4);
			memcpy (&SaveInfoStructOne.listfile.offset3, &Buf[0x20], 4);
			memcpy (&SaveInfoStructOne.listfile.offset4, &Buf[0x28], 4);
			memcpy (&SaveInfoStructOne.listfile.offset5, &Buf[0x30], 4);
			SaveInfoStructOne.count.count1 = SaveInfoStructOne.listfile.offset2 - SaveInfoStructOne.listfile.offset1;
			SaveInfoStructOne.count.count2 = SaveInfoStructOne.listfile.offset3 - SaveInfoStructOne.listfile.offset2;
			SaveInfoStructOne.count.count3 = SaveInfoStructOne.listfile.offset4 - SaveInfoStructOne.listfile.offset3;
			SaveInfoStructOne.count.count4 = SaveInfoStructOne.listfile.offset5 - SaveInfoStructOne.listfile.offset4;
			SaveInfoStructOne.count.count5 = lenfileinfo-SaveInfoStructOne.listfile.offset5-save6;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+SaveInfoStructOne.listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+SaveInfoStructOne.listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+SaveInfoStructOne.listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+SaveInfoStructOne.listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+SaveInfoStructOne.listfile.offset5+0x15]);
			}break;
			
			case 0x05:
			{
			iFlagSaveCount = SAVECOUNT7;
			SaveInfoStructOne.count.count0 = Buf[0x13];
			SaveInfoStructOne.listfile.offset0 = (save7);
			
			memcpy (&SaveInfoStructOne.listfile.offset1, &Buf[0x13], 1);
			memcpy (&SaveInfoStructOne.listfile.offset2, &Buf[0x18], 4);
			memcpy (&SaveInfoStructOne.listfile.offset3, &Buf[0x20], 4);
			memcpy (&SaveInfoStructOne.listfile.offset4, &Buf[0x28], 4);
			memcpy (&SaveInfoStructOne.listfile.offset5, &Buf[0x30], 4);
			memcpy (&SaveInfoStructOne.listfile.offset6, &Buf[0x38], 4);
			SaveInfoStructOne.count.count1 = SaveInfoStructOne.listfile.offset2 - SaveInfoStructOne.listfile.offset1;
			SaveInfoStructOne.count.count2 = SaveInfoStructOne.listfile.offset3 - SaveInfoStructOne.listfile.offset2;
			SaveInfoStructOne.count.count3 = SaveInfoStructOne.listfile.offset4 - SaveInfoStructOne.listfile.offset3;
			SaveInfoStructOne.count.count4 = SaveInfoStructOne.listfile.offset5 - SaveInfoStructOne.listfile.offset4;
			SaveInfoStructOne.count.count5 = SaveInfoStructOne.listfile.offset6 - SaveInfoStructOne.listfile.offset5;
			SaveInfoStructOne.count.count6 = lenfileinfo-SaveInfoStructOne.listfile.offset6-save7;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+SaveInfoStructOne.listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+SaveInfoStructOne.listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+SaveInfoStructOne.listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+SaveInfoStructOne.listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+SaveInfoStructOne.listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+SaveInfoStructOne.listfile.offset6+0x15]);
			}break;
			
			case 0x06:
			{
			iFlagSaveCount = SAVECOUNT8;
			SaveInfoStructOne.count.count0 = Buf[0x13];
			SaveInfoStructOne.listfile.offset0 = (save8);
			
			memcpy (&SaveInfoStructOne.listfile.offset1, &Buf[0x13], 1);
			memcpy (&SaveInfoStructOne.listfile.offset2, &Buf[0x18], 4);
			memcpy (&SaveInfoStructOne.listfile.offset3, &Buf[0x20], 4);
			memcpy (&SaveInfoStructOne.listfile.offset4, &Buf[0x28], 4);
			memcpy (&SaveInfoStructOne.listfile.offset5, &Buf[0x30], 4);
			memcpy (&SaveInfoStructOne.listfile.offset6, &Buf[0x38], 4);
			memcpy (&SaveInfoStructOne.listfile.offset7, &Buf[0x40], 4);
			SaveInfoStructOne.count.count1 = SaveInfoStructOne.listfile.offset2 - SaveInfoStructOne.listfile.offset1;
			SaveInfoStructOne.count.count2 = SaveInfoStructOne.listfile.offset3 - SaveInfoStructOne.listfile.offset2;
			SaveInfoStructOne.count.count3 = SaveInfoStructOne.listfile.offset4 - SaveInfoStructOne.listfile.offset3;
			SaveInfoStructOne.count.count4 = SaveInfoStructOne.listfile.offset5 - SaveInfoStructOne.listfile.offset4;
			SaveInfoStructOne.count.count5 = SaveInfoStructOne.listfile.offset6 - SaveInfoStructOne.listfile.offset5;
			SaveInfoStructOne.count.count6 = SaveInfoStructOne.listfile.offset7 - SaveInfoStructOne.listfile.offset6;
			SaveInfoStructOne.count.count7 = lenfileinfo-SaveInfoStructOne.listfile.offset7-save8;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+SaveInfoStructOne.listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+SaveInfoStructOne.listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+SaveInfoStructOne.listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+SaveInfoStructOne.listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+SaveInfoStructOne.listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+SaveInfoStructOne.listfile.offset6+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+SaveInfoStructOne.listfile.offset7+0x15]);
			}break;
			
			case 0x07:
			{
			iFlagSaveCount = SAVECOUNT9;
			SaveInfoStructOne.count.count0 = Buf[0x13];
			SaveInfoStructOne.listfile.offset0 = (save9);
			
			memcpy (&SaveInfoStructOne.listfile.offset1, &Buf[0x13], 1);
			memcpy (&SaveInfoStructOne.listfile.offset2, &Buf[0x18], 4);
			memcpy (&SaveInfoStructOne.listfile.offset3, &Buf[0x20], 4);
			memcpy (&SaveInfoStructOne.listfile.offset4, &Buf[0x28], 4);
			memcpy (&SaveInfoStructOne.listfile.offset5, &Buf[0x30], 4);
			memcpy (&SaveInfoStructOne.listfile.offset6, &Buf[0x38], 4);
			memcpy (&SaveInfoStructOne.listfile.offset7, &Buf[0x40], 4);
			memcpy (&SaveInfoStructOne.listfile.offset8, &Buf[0x48], 4);
			SaveInfoStructOne.count.count1 = SaveInfoStructOne.listfile.offset2 - SaveInfoStructOne.listfile.offset1;
			SaveInfoStructOne.count.count2 = SaveInfoStructOne.listfile.offset3 - SaveInfoStructOne.listfile.offset2;
			SaveInfoStructOne.count.count3 = SaveInfoStructOne.listfile.offset4 - SaveInfoStructOne.listfile.offset3;
			SaveInfoStructOne.count.count4 = SaveInfoStructOne.listfile.offset5 - SaveInfoStructOne.listfile.offset4;
			SaveInfoStructOne.count.count5 = SaveInfoStructOne.listfile.offset6 - SaveInfoStructOne.listfile.offset5;
			SaveInfoStructOne.count.count6 = SaveInfoStructOne.listfile.offset7 - SaveInfoStructOne.listfile.offset6;
			SaveInfoStructOne.count.count7 = SaveInfoStructOne.listfile.offset8 - SaveInfoStructOne.listfile.offset7;
			SaveInfoStructOne.count.count8 = lenfileinfo-SaveInfoStructOne.listfile.offset8-save9;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset6+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset7+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+SaveInfoStructOne.listfile.offset8+0x15]);
			}break;
			
			case 0x08:
			{
			iFlagSaveCount = SAVECOUNT10;
			SaveInfoStructOne.count.count0 = Buf[0x13];
			SaveInfoStructOne.listfile.offset0 = (save10);
			
			memcpy (&SaveInfoStructOne.listfile.offset1, &Buf[0x13], 1);
			memcpy (&SaveInfoStructOne.listfile.offset2, &Buf[0x18], 4);
			memcpy (&SaveInfoStructOne.listfile.offset3, &Buf[0x20], 4);
			memcpy (&SaveInfoStructOne.listfile.offset4, &Buf[0x28], 4);
			memcpy (&SaveInfoStructOne.listfile.offset5, &Buf[0x30], 4);
			memcpy (&SaveInfoStructOne.listfile.offset6, &Buf[0x38], 4);
			memcpy (&SaveInfoStructOne.listfile.offset7, &Buf[0x40], 4);
			memcpy (&SaveInfoStructOne.listfile.offset8, &Buf[0x48], 4);
			memcpy (&SaveInfoStructOne.listfile.offset9, &Buf[0x50], 4);
			SaveInfoStructOne.count.count1 = SaveInfoStructOne.listfile.offset2 - SaveInfoStructOne.listfile.offset1;
			SaveInfoStructOne.count.count2 = SaveInfoStructOne.listfile.offset3 - SaveInfoStructOne.listfile.offset2;
			SaveInfoStructOne.count.count3 = SaveInfoStructOne.listfile.offset4 - SaveInfoStructOne.listfile.offset3;
			SaveInfoStructOne.count.count4 = SaveInfoStructOne.listfile.offset5 - SaveInfoStructOne.listfile.offset4;
			SaveInfoStructOne.count.count5 = SaveInfoStructOne.listfile.offset6 - SaveInfoStructOne.listfile.offset5;
			SaveInfoStructOne.count.count6 = SaveInfoStructOne.listfile.offset7 - SaveInfoStructOne.listfile.offset6;
			SaveInfoStructOne.count.count7 = SaveInfoStructOne.listfile.offset8 - SaveInfoStructOne.listfile.offset7;
			SaveInfoStructOne.count.count8 = SaveInfoStructOne.listfile.offset9 - SaveInfoStructOne.listfile.offset8;
			SaveInfoStructOne.count.count9 = lenfileinfo-SaveInfoStructOne.listfile.offset9-save10;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset6+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset7+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset8+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+SaveInfoStructOne.listfile.offset9+0x15]);
			}break;*/
			
			default: iFlagSaveCount = ERRORSAVECOUNT; return ERROR_SAVECOUNT; break;
		}
		}break;
		default: iFlagSaveCount = ERRORSAVECOUNT; return ERROR_SAVECOUNT; break;
	}
	switch (iFlagSaveCount)
	{
		case SAVECOUNT1: break;
	}
}

int CSaveInfo::InitVectorSI(int num)
{
	int position = iSave[iFlagSaveCount];
	
	SaveInfoStructOne.data.aDataSave[num].reserve( SaveInfoStructOne.count.iCount[num] );
	SaveInfoStructOne.data.aDataSave[num].clear();
	memcpy(&SaveInfoStructOne.data.aDataSave[num][0x0], &aBufferTemp[SaveInfoStructOne.listfile.iOffset[num]], SaveInfoStructOne.count.iCount[num]);
	
	CSaveInfoWndControlOne.SetWndLong(num);
	
#ifdef DEBUG
	Log.Log(L"\r\nInitVectorSI, num = %i", num);
	Log.Log(L"\r\nposition = %i", position);
	Log.Log(L"\r\nSaveInfoStructOne.count.iCount[num] = %i", SaveInfoStructOne.count.iCount[num]);
	Log.Log(L"\r\nSaveInfoStructOne.count.iCount[%i] = %i(0x%x)", num, SaveInfoStructOne.count.iCount[num], SaveInfoStructOne.count.iCount[num]);
	for(int l = 0; l < SaveInfoStructOne.count.iCount[num]; l++) 
	{
		if (l == 0) {Log.Log(L"\r\n");} else {}
		Log.Log(L"%x, ", SaveInfoStructOne.data.aDataSave[num][l] );
	}
#endif


/*
	switch (num)
	{
		case 1:
		{
		Info->data.save2.reserve(Info->count.count1);
		//Log(L"Info->count.count1 = %x", Info->count.count1);
		memcpy (&Info->data.save2[0x0], &Buf[position+Info->listfile.offset1], Info->count.count1);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count1; l++) {//Log(L"data.save2 = %x",  (unsigned char)Info->data.save2[l]);}
		}break;
		
		case 2:
		{
		Info->data.save3.reserve(Info->count.count2);
		//Log(L"Info->count.count2 = %x", Info->count.count2);
		memcpy (&Info->data.save3[0x0], &Buf[position+Info->listfile.offset2], Info->count.count2);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count2; l++) {//Log(L"data.save3 = %x",  (unsigned char)Info->data.save3[l]);}
		}break;
		
		case 3:
		{
		Info->data.save4.reserve(Info->count.count3);
		//Log(L"Info->count.count3 = %x", Info->count.count3);
		memcpy (&Info->data.save4[0x0], &Buf[position+Info->listfile.offset3], Info->count.count3);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count3; l++) {//Log(L"data.save4 = %x",  (unsigned char)Info->data.save4[l]);}
		}break;

		case 4:
		{
		Info->data.save5.reserve(Info->count.count4);
		//Log(L"Info->count.count4 = %x", Info->count.count4);
		memcpy (&Info->data.save5[0x0], &Buf[position+Info->listfile.offset4], Info->count.count4);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count4; l++) {//Log(L"data.save5 = %x",  (unsigned char)Info->data.save5[l]);}
		}break;
		
		case 5:
		{
		Info->data.save6.reserve(Info->count.count5);
		//Log(L"Info->count.count5 = %x", Info->count.count5);
		memcpy (&Info->data.save6[0x0], &Buf[position+Info->listfile.offset5], Info->count.count5);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count5; l++) {//Log(L"data.save6 = %x",  (unsigned char)Info->data.save6[l]);}
		}break;
		
		case 6:
		{
		Info->data.save7.reserve(Info->count.count6);
		//Log(L"Info->count.count6 = %x", Info->count.count6);
		memcpy (&Info->data.save7[0x0], &Buf[position+Info->listfile.offset6], Info->count.count6);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count6; l++) {//Log(L"data.save7 = %x",  (unsigned char)Info->data.save7[l]);}
		}break;

		case 7:
		{
		Info->data.save8.reserve(Info->count.count7);
		//Log(L"Info->count.count7 = %x", Info->count.count7);
		memcpy (&Info->data.save8[0x0], &Buf[position+Info->listfile.offset7], Info->count.count7);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count7; l++) {//Log(L"data.save8 = %x",  (unsigned char)Info->data.save8[l]);}
		}break;
		
		case 8:
		{
		Info->data.save9.reserve(Info->count.count8);
		//Log(L"Info->count.count8 = %x", Info->count.count8);
		memcpy (&Info->data.save9[0x0], &Buf[position+Info->listfile.offset8], Info->count.count8);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count8; l++) {//Log(L"data.save9 = %x",  (unsigned char)Info->data.save9[l]);}
		}break;

		case 9:
		{
		Info->data.save10.reserve(Info->count.count9);
		//Log(L"Info->count.count9 = %x", Info->count.count9);
		memcpy (&Info->data.save10[0x0], &Buf[position+Info->listfile.offset9], Info->count.count9);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count9; l++) {//Log(L"data.save10 = %x",  (unsigned char)Info->data.save10[l]);}
		}break;
		
		case 10:
		{
		Info->data.save1.reserve(Info->count.count0);
		//Log(L"Info->count.count0 = %x", Info->count.count0);
		memcpy (&Info->data.save1[0x0], &Buf[position], Info->count.count0);
		//for(int l = 0; l < Info->count.count0; l++) {//Log(L"data.save1 = %x",  (unsigned char)Info->data.save1[l]);}
		SetWindowLong(HWNDSAVEINFO[num-9], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num-9], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
	}
	*/
}