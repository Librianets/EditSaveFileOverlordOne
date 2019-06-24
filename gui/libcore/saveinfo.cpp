#include <cstring>			// Language C++
#include <vector>			// Language C++
using std::vector;

#include "saveinfo.hpp"		// project
#include "debug.hpp"		// project
#include "logging.hpp"		// project

vector <unsigned char> *CSaveInfoOverlordOne::lpGetBuffer(void)
{
	return &aBufferTemp;
}

CSaveInfoOverlordOne::CSaveInfoOverlordOne()
{
	
}

CSaveInfoOverlordOne::~CSaveInfoOverlordOne()
{
	//ClearClass();
	//aBufferTemp.~vector();
	//for (int i = 0; i < 10; i++) {SaveInfoStructOne.data.aDataSave[i].~vector();}
}

void CSaveInfoOverlordOne::ClearClass(void)
{
	if (aBufferTemp.capacity() > 0) {aBufferTemp.clear();} else {}
	
	for (int i = 0; i < 10; i++)
	{
		if (SaveInfoStructOne.data.aDataSave[i].capacity() > 0)
		{
			SaveInfoStructOne.data.aDataSave[i].clear();
			SaveInfoStructOne.data.aDataSave[i].resize(0);
		}

		SaveInfoStructOne.count.iCount[i] = 0x0;
		SaveInfoStructOne.data.iFlagSaveNum[i] = 0x0;
	}
	SaveInfoStructOne.header.count = 0x0;
	SaveInfoStructOne.header.numbersize = 0x0;
	
	memset(aTempOne, 0, 64);
}

void CSaveInfoOverlordOne::StringConvert(int iNumVector, int iLanguage)
{
	int iSizeString = 0;
	
	for (int i = 0; i < 20; i++)
	{
		if ( SaveInfoStructOne.data.aDataSave[iNumVector][SaveInfoStructOne.count.iCount[iNumVector]-1-i] == 0)
			{
				iSizeString = SaveInfoStructOne.data.aDataSave[iNumVector][SaveInfoStructOne.count.iCount[iNumVector]-1-i-3];
				break;
			}
	}
	memcpy(aTempOne, &SaveInfoStructOne.data.aDataSave[iNumVector][SaveInfoStructOne.count.iCount[iNumVector]-iSizeString], iSizeString);
	debug(L"\r\n %x", iSizeString);


if (iLanguage == 1)
{
	char asd = 0xD0;
	for (int i = 0; i < iSizeString/2; i++)
	{
		if ( memcmp( &aTempOne[i*2], &asd, 1) == 0)
			{aTempOne[i*2]-=0xCC; aTempOne[i*2+1]-=0x80;} 
			else
			{aTempOne[i*2]-=0xCD; aTempOne[i*2+1]-=0x40;}
	}
	
	for (int i = 0; i < iSizeString/2; i++)
	{
		unsigned char temp = 0x0;
		temp = aTempOne[i*2];
		aTempOne[i*2] = aTempOne[i*2+1];
		aTempOne[i*2+1] = temp;
	}

debug(L"\r\n aTempOne = ", L"");
#ifdef DEBUGMODE
	for (int i = 0; i < iSizeString; i++){debug(L"%02X, ", aTempOne[i]);}
#endif
} else
{
	char aTemp [64];
	for(int i = 0; i < iSizeString; i++)
	{
		aTemp[i] = aTempOne[i]; 
	}
	memset(aTempOne, 0, 64); // ?!
	for(int i = 0; i < iSizeString; i++)
	{
		aTempOne[i*2] = aTemp[i];
	}
	memset(aTemp, 0, 64); // ?!
	
debug(L"\r\n aTempOne = ", L"");
#ifdef DEBUGMODE
	for (int i = 0; i < iSizeString*2; i++){debug(L"%02X, ", aTempOne[i]);}
#endif
}

}

int CSaveInfoOverlordOne::DisassemblySI(void)
{
	memcpy (&SaveInfoStructOne.header.count, &aBufferTemp[0xA], 4);
	
debug(L"\r\nInfo->header.count = %i", SaveInfoStructOne.header.count);debug(L"\r\n0xB = %X, 0xC = %X", aBufferTemp[0xB], aBufferTemp[0xC]);

	switch (aBufferTemp[0xB])
	{
		case 0x01: 
		{
			iFlagSaveCount = SAVECOUNT1;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
		}break;
		
		case 0x02:
		{
			iFlagSaveCount = SAVECOUNT2;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0xF] + iSave[iFlagSaveCount];
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
			}break;
			
			case 0x02:
			{
			iFlagSaveCount = SAVECOUNT4;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x03:
			{
			iFlagSaveCount = SAVECOUNT5;
			
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SaveInfoStructOne.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
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
			}break;
			
			default: iFlagSaveCount = SAVECOUNT0; return ERR_SI_SAVECOUNT; break;
		}
		}break;
		
		default: iFlagSaveCount = SAVECOUNT0; return ERR_SI_SAVECOUNT; break;
	}
	
debug(L"\r\niFlagSaveCount = %i", iFlagSaveCount);

	for (short int i = 0; i < iFlagSaveCount; i++)
	{
		SaveInfoStructOne.count.iCount[i] = SaveInfoStructOne.listfile.iOffset[i+1] - SaveInfoStructOne.listfile.iOffset[i];
	}
	
	SaveInfoStructOne.count.iCount[iFlagSaveCount] = SaveInfoStructOne.header.numbersize - SaveInfoStructOne.listfile.iOffset[iFlagSaveCount];
	
	for (int l = 0; l <= iFlagSaveCount; l++){InitVectorSI(l);}
	
#ifdef DEBUGMODE
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		debug(L"\r\nSaveInfoStructOne.listfile.iOffset[%i] = %i", l, SaveInfoStructOne.listfile.iOffset[l]);
		debug(L"\r\nSaveInfoStructOne.count.iCount[%x] = %i", l, SaveInfoStructOne.count.iCount[l]);
	}
#endif
	
	switch (iFlagSaveCount)
	{
		case SAVECOUNT1: break;
	}
	
return 0;
}

int CSaveInfoOverlordOne::AssemblySI(void)
{
	if (aBufferTemp.capacity() > 1) {aBufferTemp.clear();} else {return -0x01;}
	SaveInfoStructOne.header.numbersize = 0x0;
	int iPos = 0x0;
	for (int i = 0;i < 10;i++)
	{
		SaveInfoStructOne.header.numbersize += SaveInfoStructOne.data.aDataSave[i].size();
		debug(L"\r\n aDataSave[%i].size = %X (%i)", i, SaveInfoStructOne.data.aDataSave[i].size(), SaveInfoStructOne.data.aDataSave[i].size());
	}
	aBufferTemp.resize(SaveInfoStructOne.header.numbersize + iSave[iFlagSaveCount]);
	
	memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.header.reserved, 4);iPos += 0x4;
	memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.header.const02, 4);iPos += 0x4;
	memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.header.const01, 2);iPos += 0x2;
	switch (iFlagSaveCount)
	{
		case SAVECOUNT1:
		{
			memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.listfile.iConst2[0], 4);iPos += 0x4;
		}break;
		
		case SAVECOUNT2:
		{
			memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.listfile.iConst2[1], 4);iPos += 0x4;
			short int temp = (short int) (SaveInfoStructOne.count.iCount[0] << 8 | 0x01);
			memcpy(&aBufferTemp[iPos], &temp, 2);iPos += 0x2;
		}break;
		
		
		default: return SAVECOUNT0;	
	}

	SaveInfoStructOne.header.numbersize += iPos;
	
	for(int i = 0;i < 10;i++)
	{
		memcpy(&aBufferTemp[iPos], &SaveInfoStructOne.data.aDataSave[i][0x0], (size_t)SaveInfoStructOne.data.aDataSave[i].size());
		iPos += SaveInfoStructOne.data.aDataSave[i].size();
	}
	
#ifdef DEBUGMODE
	debug(L"\r\n SaveInfoStructOne.header.numbersize = %i", SaveInfoStructOne.header.numbersize);
	for(int i = 0; i < SaveInfoStructOne.header.numbersize; i++)
	{
		if (i == 0) {debug(L"\r\n", L"");} else {}
		debug(L"%02X, ", aBufferTemp[i] );
	}
#endif

	return 0;	
}

int CSaveInfoOverlordOne::InitVectorSI(int num)
{
	if (iFlagSaveCount == ERR_SI_SAVECOUNT) {return ERR_SI_SAVECOUNT;}
	int position = iSave[iFlagSaveCount];
	
	SaveInfoStructOne.data.aDataSave[num].resize( SaveInfoStructOne.count.iCount[num] );

	memcpy(&SaveInfoStructOne.data.aDataSave[num][0x0], &aBufferTemp[SaveInfoStructOne.listfile.iOffset[num]], SaveInfoStructOne.count.iCount[num]);
	
	debug(L"\r\nSaveInfoStructOne.data.aDataSave[num][0x15] = %i", SaveInfoStructOne.data.aDataSave[num][0x15]);
	SaveInfoStructOne.data.iFlagSaveNum [SaveInfoStructOne.data.aDataSave[num][0x15]] = 1;
	
debug(L"\r\n size data = %X ", SaveInfoStructOne.data.aDataSave[num].size() );
debug(L"\r\nInitVectorSI, num = %i", num);
debug(L"\r\nposition = %i", position);
debug(L"\r\nSaveInfoStructOne.count.iCount[%i] = %i", num, SaveInfoStructOne.count.iCount[num]);
debug(L"\r\nSaveInfoStructOne.count.iCount[%i] = %i(0x%X)", num, SaveInfoStructOne.count.iCount[num], SaveInfoStructOne.count.iCount[num]);
#ifdef DEBUGMODE
	for(int l = 0; l < SaveInfoStructOne.count.iCount[num]; l++)
	{
		if (l == 0) {debug(L"\r\n", L"");} else {}
		debug(L"%x, ", SaveInfoStructOne.data.aDataSave[num][l] );
	}
#endif

return 0;
}

