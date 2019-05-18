#include "global.hpp"

using offset = unsigned int;

static offset head = 0xE;
static offset save2 = head+0x2; //0x10
static offset save3 = head+0x6+0x8; // 1c
static offset save4 = head+0x6+0x8*2; // 24
static offset save5 = head+0x6+0x8*3;
static offset save6 = head+0x6+0x8*4;
static offset save7 = head+0x6+0x8*5;
static offset save8 = head+0x6+0x8*6;
static offset save9 = head+0x6+0x8*7;
static offset save10 = head+0x6+0x8*8;

SaveInfoStruct SaveInfoStructOne;

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

void DefineSaveInfo(void* aBuf, lpSaveInfoStruct Info, unsigned int lenfileinfo)
{
	unsigned char *Buf = (unsigned char*) aBuf;
	unsigned int temp = 0;
	//memset (&Info, 0, sizeof(Info));
	log(L"memset Info = %x", sizeof(Info));
	Info->header.count = 0x0;
	Info->listfile.count0 = 0x0;	Info->listfile.count1 = 0x0;
	Info->listfile.count2 = 0x0;	Info->listfile.count3 = 0x0;
	Info->listfile.count4 = 0x0;	Info->listfile.count5 = 0x0;
	Info->listfile.count6 = 0x0;	Info->listfile.count7 = 0x0;
	Info->listfile.count8 = 0x0;	Info->listfile.count9 = 0x0;
	Info->data.save1.clear();	Info->data.save1.resize(0);
	Info->data.save2.clear();	Info->data.save2.resize(0);
	Info->data.save3.clear();	Info->data.save3.resize(0);
	Info->data.save4.clear();	Info->data.save4.resize(0);
	Info->data.save5.clear();	Info->data.save5.resize(0);
	Info->data.save6.clear();	Info->data.save7.resize(0);
	Info->data.save8.clear();	Info->data.save8.resize(0);
	Info->data.save9.clear();	Info->data.save9.resize(0);
	Info->data.save10.clear();	Info->data.save10.resize(0);
	
	memcpy (&Info->header.count, &Buf[0xA], 4);
	log(L"Info->header.count = %i", Info->header.count);

	switch (Buf[0xB])
	{
		case 0x01: 
		{
			iFlagSaveCount = SAVECOUNT1;
			Info->listfile.count0 = (lenfileinfo-head);
			InitVectorSI(Buf, Info, 10);
		}break;
		
		case 0x02:
		{
			iFlagSaveCount = SAVECOUNT2;
			memcpy (&Info->listfile.count0, &Buf[0xF], 1); // size save1
			log(L"Info->listfile.count0 = %x", Info->listfile.count0);
			Info->listfile.count1 = (lenfileinfo-Info->listfile.count0-save2); // размер save2
			log(L"Info->listfile.count1 = %x", Info->listfile.count1);
			InitVectorSI(Buf, Info, 10);
			log(L"????? = %x", save2+Info->listfile.count0+0x15);
			log(L"????? = %x",  Buf[save2+Info->listfile.count0+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save2+Info->listfile.count0+0x15]);
		}break;
		
		case 0x82:
		{
		switch (Buf[0xC])
		{
			case 0x01:
			{
			iFlagSaveCount = SAVECOUNT3; 
			memcpy (&Info->listfile.count0, &Buf[0x13], 1); // size save1
			memcpy (&Info->listfile.count1, &Buf[0x18], 1); // size save2
			Info->listfile.count2 = (lenfileinfo-Info->listfile.count0-Info->listfile.count1-save3); // размер save3

			InitVectorSI(Buf, Info, 10);
			InitVectorSI(Buf, Info, Buf[save3+Info->listfile.count0+0x15]);
			InitVectorSI(Buf, Info, Buf[save3+Info->listfile.count0+Info->listfile.count1+0x15]);
			}break;
			
			case 0x02:
			{
			iFlagSaveCount = SAVECOUNT4;
			memcpy (&Info->listfile.count0, &Buf[0x13], 1); // size save1
			memcpy (&Info->listfile.count1, &Buf[0x18], 1); // size save2
			memcpy (&Info->listfile.count2, &Buf[0x20], 1); // size save3

			Info->listfile.count2 = (lenfileinfo-Info->listfile.count0-Info->listfile.count1-Info->listfile.count2-save4); // размер save4

			InitVectorSI(Buf, Info, 10);
			InitVectorSI(Buf, Info, Buf[save4+Info->listfile.count0+0x15]);
			InitVectorSI(Buf, Info, Buf[save4+Info->listfile.count0+Info->listfile.count1+0x15]);
			InitVectorSI(Buf, Info, Buf[save4+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2+0x15]);
			}break;
			
			case 0x03:
			{
			iFlagSaveCount = SAVECOUNT5;
			}break;
			
			case 0x04:
			{
			iFlagSaveCount = SAVECOUNT6;
			}break;
			
			case 0x05:
			{
			iFlagSaveCount = SAVECOUNT7;
			}break;
			
			case 0x06:
			{
			iFlagSaveCount = SAVECOUNT8;
			}break;
			
			case 0x07:
			{
			iFlagSaveCount = SAVECOUNT9;
			}break;
			
			case 0x08:
			{
			iFlagSaveCount = SAVECOUNT10;
			}break;
			
			default: iFlagSaveCount = ERRORSAVECOUNT; Error(ERROR_SAVECOUNT, ERROR_NOTEXITAPP); break;
		}
		}break;
		default: iFlagSaveCount = ERRORSAVECOUNT; Error(ERROR_SAVECOUNT, ERROR_NOTEXITAPP); break;
	}
	log(L"iFlagSaveCount = %i", iFlagSaveCount);
	switch (iFlagSaveCount)
	{
		case SAVECOUNT1: break;
	}
}

void InitVectorSI(unsigned char *Buf, lpSaveInfoStruct Info, unsigned char num)
{	
	switch (num)
	{
		case 1:
		{
		Info->data.save2.reserve(Info->listfile.count1);
		memcpy (&Info->data.save2[0x0], &Buf[save2+Info->listfile.count0], Info->listfile.count1);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		for(int l = 0; l < Info->listfile.count1; l++) {log(L"data.save2 = %x",  (unsigned char)Info->data.save2[l]);}
		}break;
		
		case 2:
		{
		Info->data.save3.reserve(Info->listfile.count2);
		memcpy (&Info->data.save3[0x0], &Buf[save3+Info->listfile.count0+Info->listfile.count1], Info->listfile.count2);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
		
		case 3:
		{
		Info->data.save4.reserve(Info->listfile.count3);
		memcpy (&Info->data.save4[0x0], &Buf[save4+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2], Info->listfile.count3);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;

		case 4:
		{
		Info->data.save5.reserve(Info->listfile.count4);
		memcpy (&Info->data.save5[0x0], &Buf[save5+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2+Info->listfile.count3], Info->listfile.count4);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
		
		case 5:
		{
		Info->data.save6.reserve(Info->listfile.count5);
		memcpy (&Info->data.save6[0x0], &Buf[save6+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2+Info->listfile.count3+Info->listfile.count4], Info->listfile.count5);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
		
		case 6:
		{
		Info->data.save7.reserve(Info->listfile.count7);
		memcpy (&Info->data.save7[0x0], &Buf[save7+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2+Info->listfile.count3+Info->listfile.count4+Info->listfile.count5], Info->listfile.count6);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;

		case 7:
		{
		Info->data.save8.reserve(Info->listfile.count8);
		memcpy (&Info->data.save8[0x0], &Buf[save8+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2+Info->listfile.count3+Info->listfile.count4+Info->listfile.count5+Info->listfile.count6], Info->listfile.count7);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
		
		case 8:
		{
		Info->data.save9.reserve(Info->listfile.count9);
		memcpy (&Info->data.save9[0x0], &Buf[save9+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2+Info->listfile.count3+Info->listfile.count4+Info->listfile.count5+Info->listfile.count6+Info->listfile.count8], Info->listfile.count9);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;

		case 9:
		{
		Info->data.save10.reserve(Info->listfile.count6);
		memcpy (&Info->data.save10[0x0], &Buf[save10+Info->listfile.count0+Info->listfile.count1+Info->listfile.count2+Info->listfile.count3+Info->listfile.count4+Info->listfile.count5+Info->listfile.count6+Info->listfile.count7+Info->listfile.count8], Info->listfile.count9);
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
		
		case 10:
		{
		Info->data.save1.reserve(Info->listfile.count0);
		int position = head;
		switch (iFlagSaveCount)
		{
			case 1: position = head; break;
			case 2: position = save2; break;
			case 3: position = save3; break;
			case 4: position = save4; break;
			case 5: position = save5; break;
			case 6: position = save6; break;
			case 7: position = save7; break;
			case 8: position = save8; break;
			case 9: position = save9; break;
			case 10: position = save10; break;
		}
		
		memcpy (&Info->data.save1[0x0], &Buf[position], Info->listfile.count0);
		//for(int l = 0; l < Info->listfile.count0; l++) {log(L"data.save1 = %x",  (unsigned char)Info->data.save1[l]);}
		SetWindowLong(HWNDSAVEINFO[num-9], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num-9], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
	}
	
}