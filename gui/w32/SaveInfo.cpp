#include "global.hpp"
/*
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
	Info->count.count0 = 0x0;	Info->count.count1 = 0x0;
	Info->count.count2 = 0x0;	Info->count.count3 = 0x0;
	Info->count.count4 = 0x0;	Info->count.count5 = 0x0;
	Info->count.count6 = 0x0;	Info->count.count7 = 0x0;
	Info->count.count8 = 0x0;	Info->count.count9 = 0x0;
	Info->listfile.offset0 = 0x0;	Info->listfile.offset1 = 0x0;
	Info->listfile.offset2 = 0x0;	Info->listfile.offset3 = 0x0;
	Info->listfile.offset4 = 0x0;	Info->listfile.offset5 = 0x0;
	Info->listfile.offset6 = 0x0;	Info->listfile.offset7 = 0x0;
	Info->listfile.offset8 = 0x0;	Info->listfile.offset9 = 0x0;
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
	log (L"0xB = %i, 0xC = %i", Buf[0xB], Buf[0xC]);
	switch (Buf[0xB])
	{
		case 0x01: 
		{
			iFlagSaveCount = SAVECOUNT1;
			Info->count.count0 = (lenfileinfo-head);
			Info->listfile.offset0 = (head);
			InitVectorSI(Buf, Info, 10);
		}break;
		
		case 0x02:
		{
			iFlagSaveCount = SAVECOUNT2;
			Info->count.count0 = Buf[0xF];
			Info->listfile.offset0 = (save2);
			
			Info->count.count1 = lenfileinfo-save2-Buf[0xF];
			Info->listfile.offset1 = Buf[0xF];
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save2+Info->listfile.offset1+0x15]);
		}break;
		
		case 0x82:
		{
		switch (Buf[0xC])
		{
			case 0x01:
			{
			iFlagSaveCount = SAVECOUNT3; 
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save3);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			Info->count.count1 = Info->listfile.offset2-Info->listfile.offset1;
			Info->count.count2 = lenfileinfo-Info->listfile.offset2-save3;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save3+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save3+Info->listfile.offset2+0x15]);
			}break;
			
			case 0x02:
			{
			iFlagSaveCount = SAVECOUNT4;
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save4);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			memcpy (&Info->listfile.offset3, &Buf[0x20], 4);
			Info->count.count1 = Info->listfile.offset2 - Info->listfile.offset1;
			Info->count.count2 = Info->listfile.offset3 - Info->listfile.offset2;
			Info->count.count3 = lenfileinfo-Info->listfile.offset3-save4;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save4+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save4+Info->listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save4+Info->listfile.offset3+0x15]);
			}break;
			
			case 0x03:
			{
			iFlagSaveCount = SAVECOUNT5;
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save5);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			memcpy (&Info->listfile.offset3, &Buf[0x20], 4);
			memcpy (&Info->listfile.offset4, &Buf[0x28], 4);
			Info->count.count1 = Info->listfile.offset2 - Info->listfile.offset1;
			Info->count.count2 = Info->listfile.offset3 - Info->listfile.offset2;
			Info->count.count3 = Info->listfile.offset4 - Info->listfile.offset3;
			Info->count.count4 = lenfileinfo-Info->listfile.offset4-save5;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+Info->listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+Info->listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save5+Info->listfile.offset4+0x15]);
			}break;
			
			case 0x04:
			{
			iFlagSaveCount = SAVECOUNT6;
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save6);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			memcpy (&Info->listfile.offset3, &Buf[0x20], 4);
			memcpy (&Info->listfile.offset4, &Buf[0x28], 4);
			memcpy (&Info->listfile.offset5, &Buf[0x30], 4);
			Info->count.count1 = Info->listfile.offset2 - Info->listfile.offset1;
			Info->count.count2 = Info->listfile.offset3 - Info->listfile.offset2;
			Info->count.count3 = Info->listfile.offset4 - Info->listfile.offset3;
			Info->count.count4 = Info->listfile.offset5 - Info->listfile.offset4;
			Info->count.count5 = lenfileinfo-Info->listfile.offset5-save6;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+Info->listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+Info->listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+Info->listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save6+Info->listfile.offset5+0x15]);
			}break;
			
			case 0x05:
			{
			iFlagSaveCount = SAVECOUNT7;
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save7);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			memcpy (&Info->listfile.offset3, &Buf[0x20], 4);
			memcpy (&Info->listfile.offset4, &Buf[0x28], 4);
			memcpy (&Info->listfile.offset5, &Buf[0x30], 4);
			memcpy (&Info->listfile.offset6, &Buf[0x38], 4);
			Info->count.count1 = Info->listfile.offset2 - Info->listfile.offset1;
			Info->count.count2 = Info->listfile.offset3 - Info->listfile.offset2;
			Info->count.count3 = Info->listfile.offset4 - Info->listfile.offset3;
			Info->count.count4 = Info->listfile.offset5 - Info->listfile.offset4;
			Info->count.count5 = Info->listfile.offset6 - Info->listfile.offset5;
			Info->count.count6 = lenfileinfo-Info->listfile.offset6-save7;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+Info->listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+Info->listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+Info->listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+Info->listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save7+Info->listfile.offset6+0x15]);
			}break;
			
			case 0x06:
			{
			iFlagSaveCount = SAVECOUNT8;
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save8);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			memcpy (&Info->listfile.offset3, &Buf[0x20], 4);
			memcpy (&Info->listfile.offset4, &Buf[0x28], 4);
			memcpy (&Info->listfile.offset5, &Buf[0x30], 4);
			memcpy (&Info->listfile.offset6, &Buf[0x38], 4);
			memcpy (&Info->listfile.offset7, &Buf[0x40], 4);
			Info->count.count1 = Info->listfile.offset2 - Info->listfile.offset1;
			Info->count.count2 = Info->listfile.offset3 - Info->listfile.offset2;
			Info->count.count3 = Info->listfile.offset4 - Info->listfile.offset3;
			Info->count.count4 = Info->listfile.offset5 - Info->listfile.offset4;
			Info->count.count5 = Info->listfile.offset6 - Info->listfile.offset5;
			Info->count.count6 = Info->listfile.offset7 - Info->listfile.offset6;
			Info->count.count7 = lenfileinfo-Info->listfile.offset7-save8;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+Info->listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+Info->listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+Info->listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+Info->listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+Info->listfile.offset6+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save8+Info->listfile.offset7+0x15]);
			}break;
			
			case 0x07:
			{
			iFlagSaveCount = SAVECOUNT9;
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save9);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			memcpy (&Info->listfile.offset3, &Buf[0x20], 4);
			memcpy (&Info->listfile.offset4, &Buf[0x28], 4);
			memcpy (&Info->listfile.offset5, &Buf[0x30], 4);
			memcpy (&Info->listfile.offset6, &Buf[0x38], 4);
			memcpy (&Info->listfile.offset7, &Buf[0x40], 4);
			memcpy (&Info->listfile.offset8, &Buf[0x48], 4);
			Info->count.count1 = Info->listfile.offset2 - Info->listfile.offset1;
			Info->count.count2 = Info->listfile.offset3 - Info->listfile.offset2;
			Info->count.count3 = Info->listfile.offset4 - Info->listfile.offset3;
			Info->count.count4 = Info->listfile.offset5 - Info->listfile.offset4;
			Info->count.count5 = Info->listfile.offset6 - Info->listfile.offset5;
			Info->count.count6 = Info->listfile.offset7 - Info->listfile.offset6;
			Info->count.count7 = Info->listfile.offset8 - Info->listfile.offset7;
			Info->count.count8 = lenfileinfo-Info->listfile.offset8-save9;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset6+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset7+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save9+Info->listfile.offset8+0x15]);
			}break;
			
			case 0x08:
			{
			iFlagSaveCount = SAVECOUNT10;
			Info->count.count0 = Buf[0x13];
			Info->listfile.offset0 = (save10);
			
			memcpy (&Info->listfile.offset1, &Buf[0x13], 1);
			memcpy (&Info->listfile.offset2, &Buf[0x18], 4);
			memcpy (&Info->listfile.offset3, &Buf[0x20], 4);
			memcpy (&Info->listfile.offset4, &Buf[0x28], 4);
			memcpy (&Info->listfile.offset5, &Buf[0x30], 4);
			memcpy (&Info->listfile.offset6, &Buf[0x38], 4);
			memcpy (&Info->listfile.offset7, &Buf[0x40], 4);
			memcpy (&Info->listfile.offset8, &Buf[0x48], 4);
			memcpy (&Info->listfile.offset9, &Buf[0x50], 4);
			Info->count.count1 = Info->listfile.offset2 - Info->listfile.offset1;
			Info->count.count2 = Info->listfile.offset3 - Info->listfile.offset2;
			Info->count.count3 = Info->listfile.offset4 - Info->listfile.offset3;
			Info->count.count4 = Info->listfile.offset5 - Info->listfile.offset4;
			Info->count.count5 = Info->listfile.offset6 - Info->listfile.offset5;
			Info->count.count6 = Info->listfile.offset7 - Info->listfile.offset6;
			Info->count.count7 = Info->listfile.offset8 - Info->listfile.offset7;
			Info->count.count8 = Info->listfile.offset9 - Info->listfile.offset8;
			Info->count.count9 = lenfileinfo-Info->listfile.offset9-save10;
			
			InitVectorSI(Buf, Info, 10);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset1+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset2+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset3+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset4+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset5+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset6+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset7+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset8+0x15]);
			InitVectorSI(&Buf[0x0], Info, Buf[save10+Info->listfile.offset9+0x15]);
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
	log(L"InitVectorSI, num = %i", num);
	int position = head;
	switch (iFlagSaveCount)
	{
		case 0x01: position = head; break;
		case 0x02: position = save2; break;
		case 0x03: position = save3; break;
		case 0x04: position = save4; break;
		case 0x05: position = save5; break;
		case 0x06: position = save6; break;
		case 0x07: position = save7; break;
		case 0x08: position = save8; break;
		case 0x09: position = save9; break;
		case 0x0A: position = save10; break;
		default: Error(ERROR_SAVECOUNT, ERROR_NOTEXITAPP); break;
	}
	
	switch (num)
	{
		case 1:
		{
		Info->data.save2.reserve(Info->count.count1);
		log(L"Info->count.count1 = %x", Info->count.count1);
		memcpy (&Info->data.save2[0x0], &Buf[position+Info->listfile.offset1], Info->count.count1);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count1; l++) {log(L"data.save2 = %x",  (unsigned char)Info->data.save2[l]);}
		}break;
		
		case 2:
		{
		Info->data.save3.reserve(Info->count.count2);
		log(L"Info->count.count2 = %x", Info->count.count2);
		memcpy (&Info->data.save3[0x0], &Buf[position+Info->listfile.offset2], Info->count.count2);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count2; l++) {log(L"data.save3 = %x",  (unsigned char)Info->data.save3[l]);}
		}break;
		
		case 3:
		{
		Info->data.save4.reserve(Info->count.count3);
		log(L"Info->count.count3 = %x", Info->count.count3);
		memcpy (&Info->data.save4[0x0], &Buf[position+Info->listfile.offset3], Info->count.count3);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count3; l++) {log(L"data.save4 = %x",  (unsigned char)Info->data.save4[l]);}
		}break;

		case 4:
		{
		Info->data.save5.reserve(Info->count.count4);
		log(L"Info->count.count4 = %x", Info->count.count4);
		memcpy (&Info->data.save5[0x0], &Buf[position+Info->listfile.offset4], Info->count.count4);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count4; l++) {log(L"data.save5 = %x",  (unsigned char)Info->data.save5[l]);}
		}break;
		
		case 5:
		{
		Info->data.save6.reserve(Info->count.count5);
		log(L"Info->count.count5 = %x", Info->count.count5);
		memcpy (&Info->data.save6[0x0], &Buf[position+Info->listfile.offset5], Info->count.count5);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count5; l++) {log(L"data.save6 = %x",  (unsigned char)Info->data.save6[l]);}
		}break;
		
		case 6:
		{
		Info->data.save7.reserve(Info->count.count6);
		log(L"Info->count.count6 = %x", Info->count.count6);
		memcpy (&Info->data.save7[0x0], &Buf[position+Info->listfile.offset6], Info->count.count6);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count6; l++) {log(L"data.save7 = %x",  (unsigned char)Info->data.save7[l]);}
		}break;

		case 7:
		{
		Info->data.save8.reserve(Info->count.count7);
		log(L"Info->count.count7 = %x", Info->count.count7);
		memcpy (&Info->data.save8[0x0], &Buf[position+Info->listfile.offset7], Info->count.count7);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count7; l++) {log(L"data.save8 = %x",  (unsigned char)Info->data.save8[l]);}
		}break;
		
		case 8:
		{
		Info->data.save9.reserve(Info->count.count8);
		log(L"Info->count.count8 = %x", Info->count.count8);
		memcpy (&Info->data.save9[0x0], &Buf[position+Info->listfile.offset8], Info->count.count8);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count8; l++) {log(L"data.save9 = %x",  (unsigned char)Info->data.save9[l]);}
		}break;

		case 9:
		{
		Info->data.save10.reserve(Info->count.count9);
		log(L"Info->count.count9 = %x", Info->count.count9);
		memcpy (&Info->data.save10[0x0], &Buf[position+Info->listfile.offset9], Info->count.count9);
		
		SetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num+1], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		//for(int l = 0; l < Info->count.count9; l++) {log(L"data.save10 = %x",  (unsigned char)Info->data.save10[l]);}
		}break;
		
		case 10:
		{
		Info->data.save1.reserve(Info->count.count0);
		log(L"Info->count.count0 = %x", Info->count.count0);
		memcpy (&Info->data.save1[0x0], &Buf[position], Info->count.count0);
		//for(int l = 0; l < Info->count.count0; l++) {log(L"data.save1 = %x",  (unsigned char)Info->data.save1[l]);}
		SetWindowLong(HWNDSAVEINFO[num-9], GWL_STYLE, (GetWindowLong(HWNDSAVEINFO[num-9], GWL_STYLE) - BS_3STATE + BS_AUTOCHECKBOX));
		}break;
	}
	
}*/