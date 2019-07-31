#include <cstring>			// Language C++
//#include <string>			// Language C++
#include <iostream>			// Language C++
#include <vector>			// Language C++
#include <cmath>			// Language C++
//#include <cwchar>			// Language C++
using std::vector;

#include "saveinfo.hpp"		// project
#include "debug.hpp"		// project
#include "logging.hpp"		// project

vector <unsigned char> *CSaveInfoOverlord::lpGetBuffer(void)
{
	return &aBufferTemp;
}

CSaveInfoOverlord::CSaveInfoOverlord()
{
	
}

CSaveInfoOverlord::~CSaveInfoOverlord()
{
	//ClearClass();
	//aBufferTemp.~vector();
	//for (int i = 0; i < 10; i++) {SIS.data.aDataSave[i].~vector();}
}

void CSaveInfoOverlord::ClearClass(void)
{
	if (aBufferTemp.capacity() > 0) {aBufferTemp.clear();} else {}
	
	for (int i = 0; i < 10; i++)
	{
		if (SIS.data.aDataSave[i].capacity() > 0)
		{
			SIS.data.aDataSave[i].clear();
			SIS.data.aDataSave[i].resize(0);
		}

		SIS.count.iCount[i] = 0x0;
		SIS.data.iFlagSaveNum[i] = 0x0;
	}
	SIS.header.count = 0x0;
	SIS.header.numbersize = 0x0;
	
	memset(aTempOne, 0, 64);
}

int CSaveInfoOverlord::SetErrorStatus (int iError)
{
	iErrorStatus = iError;
	return iErrorStatus;
}

int CSaveInfoOverlord::GetErrorStatus (void)
{
	return iErrorStatus;
}

void CSaveInfoOverlord::ClearErrorStatus (void)
{
	iErrorStatus = 0;
}

int CSaveInfoOverlord::DisassemblySI(void)
{
	memcpy (&SIS.header.count, &aBufferTemp[0xA], 4);
	
	debug(L"\r\nInfo->header.count = %i", SIS.header.count);
	debug(L"\r\n0xB = %X, 0xC = %X", aBufferTemp[0xB], aBufferTemp[0xC]);

	switch (aBufferTemp[0xB])
	{
		case 0x01: 
		{
			iFlagSaveCount = SAVECOUNT1;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
		}break;
		
		case 0x02:
		{
			iFlagSaveCount = SAVECOUNT2;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0xF] + iSave[iFlagSaveCount];
		}break;
		
		case 0x82:
		{
		switch (aBufferTemp[0xC])
		{
			case 0x01:
			{
			iFlagSaveCount = SAVECOUNT3;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x02:
			{
			iFlagSaveCount = SAVECOUNT4;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x03:
			{
			iFlagSaveCount = SAVECOUNT5;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x04:
			{
			iFlagSaveCount = SAVECOUNT6;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x05:
			{
			iFlagSaveCount = SAVECOUNT7;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x06:
			{
			iFlagSaveCount = SAVECOUNT8;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT8] = ((aBufferTemp[0x41] << 8) | aBufferTemp[0x40]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x07:
			{
			iFlagSaveCount = SAVECOUNT9;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT8] = ((aBufferTemp[0x41] << 8) | aBufferTemp[0x40]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT9] = ((aBufferTemp[0x49] << 8) | aBufferTemp[0x48]) + iSave[iFlagSaveCount];
			}break;
			
			case 0x08:
			{
			iFlagSaveCount = SAVECOUNT10;
			
			SIS.listfile.iOffset[SAVECOUNT1] = iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT2] = aBufferTemp[0x13] + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT3] = ((aBufferTemp[0x19] << 8) | aBufferTemp[0x18]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT4] = ((aBufferTemp[0x21] << 8) | aBufferTemp[0x20]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT5] = ((aBufferTemp[0x29] << 8) | aBufferTemp[0x28]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT6] = ((aBufferTemp[0x31] << 8) | aBufferTemp[0x30]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT7] = ((aBufferTemp[0x39] << 8) | aBufferTemp[0x38]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT8] = ((aBufferTemp[0x41] << 8) | aBufferTemp[0x40]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT9] = ((aBufferTemp[0x49] << 8) | aBufferTemp[0x48]) + iSave[iFlagSaveCount];
			SIS.listfile.iOffset[SAVECOUNT10] = ((aBufferTemp[0x51] << 8) | aBufferTemp[0x50]) + iSave[iFlagSaveCount];
			}break;
			
			default: iFlagSaveCount = SAVECOUNT0; return ERR_SI_SAVECOUNT; break;
		}
		}break;
		
		default: iFlagSaveCount = SAVECOUNT0; return ERR_SI_SAVECOUNT; break;
	}
	
debug(L"\r\niFlagSaveCount = %i", iFlagSaveCount);

	for (short int i = 0; i < iFlagSaveCount; i++)
	{
		SIS.count.iCount[i] = SIS.listfile.iOffset[i+1] - SIS.listfile.iOffset[i];
	}
	
	SIS.count.iCount[iFlagSaveCount] = SIS.header.numbersize - SIS.listfile.iOffset[iFlagSaveCount];
	
	for (int i = 0; i <= iFlagSaveCount; i++){InitVectorSI(i);}
	
#ifdef DEBUGMODE
	for (int l = 0; l <= iFlagSaveCount; l++)
	{
		debug(L"\r\nSIS.listfile.iOffset[%i] = %i", l, SIS.listfile.iOffset[l]);
		debug(L"\r\nSIS.count.iCount[%x] = %i", l, SIS.count.iCount[l]);
	}
#endif
	
	/*switch (iFlagSaveCount)
	{
		case SAVECOUNT1: break;
	}*/
	
return 0;
}

int CSaveInfoOverlord::InitVectorSI(int num)
{
	if (iFlagSaveCount == ERR_SI_SAVECOUNT) {return ERR_SI_SAVECOUNT;}
	int position = iSave[iFlagSaveCount];
	
	SIS.data.aDataSave[num].resize( SIS.count.iCount[num] );

	memcpy(&SIS.data.aDataSave[num][0x0], &aBufferTemp[SIS.listfile.iOffset[num]], SIS.count.iCount[num]);
	
	debug(L"\r\nSIS.data.aDataSave[num][0x15] = %i", SIS.data.aDataSave[num][0x15]);
	SIS.data.iFlagSaveNum [SIS.data.aDataSave[num][0x15]] = 1;
	
debug(L"\r\nsize data = %X ", SIS.data.aDataSave[num].size() );
debug(L"\r\nInitVectorSI, num = %i", num);
debug(L"\r\nposition = %i", position);
debug(L"\r\nSIS.count.iCount[%i] = %i", num, SIS.count.iCount[num]);
debug(L"\r\nSIS.count.iCount[%i] = %i(0x%X)", num, SIS.count.iCount[num], SIS.count.iCount[num]);
#ifdef DEBUGMODE
	for(int l = 0; l < SIS.count.iCount[num]; l++)
	{
		if (l == 0) {debug(L"\r\n", L"");} else {}
		debug(L"%x, ", SIS.data.aDataSave[num][l] );
	}
#endif

return 0;
}

void CSaveInfoOverlord::AssemblySI(void)
{
	ClearErrorStatus();
	
	aBufferTemp.clear();
	SIS.header.numbersize = 0;
	SIS.header.count = -0x1;
	
	for (int i = 0; i < 10; i++) 
	{
		if (SIS.data.iFlagSaveNum[i] == 1)
			{
				SIS.header.numbersize += SIS.count.iCount[i];
				SIS.header.count++;
			} else {}
	}
	
	SIS.header.numbersize += iSave[SIS.header.count];
	aBufferTemp.resize(SIS.header.numbersize);
debug(L"\r\naBufferTemp size =  %i", aBufferTemp.size());

	int iPos = 0x0;
	
	memcpy(&aBufferTemp[iPos], &SIS.header.reserved, 4);	iPos += 0x4;
	memcpy(&aBufferTemp[iPos], &SIS.header.const02, 4);		iPos += 0x4;
	memcpy(&aBufferTemp[iPos], &SIS.header.const01, 2);		iPos += 0x2;
	debug(L"\r\nSIS.header.count =  %i", SIS.header.count);
	
	int counter = -0x1;
	if (SIS.header.count < 0) {SetErrorStatus(-0x01); return;} else {}
	if (SIS.header.count < SAVECOUNT3) // #define	SAVECOUNT3		0x0002
	{
	switch (SIS.header.count)
	{
		case SAVECOUNT1:
		{
			memcpy(&aBufferTemp[iPos], &SIS.listfile.iConst2[0], 4); iPos += 0x4;
			for (int i = 0; i < 9; i++)
			{
				if (SIS.data.iFlagSaveNum[i] == 1)
				{
#ifdef DEBUGMODE
debug(L"\r\nCopyBuff SIS.data.iFlagSaveNum[%i]", i);
debug(L"\r\nCopyBuff SIS.count.iCount = %i", SIS.count.iCount[i]);
for(int ii = 0; ii < SIS.count.iCount[i]; ii++)
{
	if (ii == 0) {debug(L"\r\n", L"");} else {}
	debug(L"%02X, ", SIS.data.aDataSave[i][ii] );
}
#endif
				memcpy(&aBufferTemp[iPos], &SIS.data.aDataSave[i][0x0], SIS.count.iCount[i]); iPos += SIS.count.iCount[i];	
				break;
				} else {}
			}

		}break;
		
		case SAVECOUNT2:
		{
			memcpy(&aBufferTemp[iPos], &SIS.listfile.iConst2[1], 4);iPos += 0x4;
			
			for (int i = 0; i < 9; i++)
			{
				if (counter == 2) {break;} else {}
				if (SIS.data.iFlagSaveNum[i] == 1)
				{
					if (counter == -0x1) 
						{
							iPos += 2;
							memcpy(&aBufferTemp[iPos], &SIS.data.aDataSave[i][0x0], SIS.count.iCount[i]);
							//iPos += SIS.count.iCount[i];
							counter = i;
						} 
						else 
						{
							iPos -= 2;
							aBufferTemp[iPos] = 0x01;
							aBufferTemp[iPos+1] = SIS.count.iCount[counter];
							
							iPos += 2;
							iPos += SIS.count.iCount[counter];
							memcpy(&aBufferTemp[iPos], &SIS.data.aDataSave[i][0x0], SIS.count.iCount[i]);
							iPos += SIS.count.iCount[i];
							counter = 2;
						}	
#ifdef DEBUGMODE
debug(L"\r\nCopyBuff SIS.data.iFlagSaveNum[%i]", i);
debug(L"\r\nCopyBuff counter = %i", counter);
debug(L"\r\nCopyBuff SIS.count.iCount = %i", SIS.count.iCount[i]);
for(int ii = 0; ii < SIS.count.iCount[i]; ii++)
{
	if (ii == 0) {debug(L"\r\n", L"");} else {}
	debug(L"%02X, ", SIS.data.aDataSave[i][ii] );
}
#endif
				} else {}
			}
			
		}break;
		
		default: {SetErrorStatus(SAVECOUNT0); return;}
	}
	
	}
	else 
	{
	debug(L"\r\nSIS.header.count =  %i", SIS.header.count);
	
	memcpy(&aBufferTemp[iPos], &SIS.listfile.iConst2[2], 4);
	aBufferTemp[iPos+2] = (SIS.header.count-1);
	iPos += 0x4;
	iPos += 0x4; // >> const 0x00000000
	aBufferTemp[iPos] = 0x01;
	iPos += 0x1;
	
	counter = SIS.header.count; // 2...9
	int iCountConstValue = 2;
	int iPosTemp = 0;
	iPosTemp = iSave[SIS.header.count];
	for (int i = 0; i < 9; i++)
	{
		if (SIS.data.iFlagSaveNum[i] == 1)
		{
			memcpy(&aBufferTemp[iPosTemp], &SIS.data.aDataSave[i][0x0], SIS.count.iCount[i]);
			iPosTemp += SIS.count.iCount[i];
			SIS.listfile.iOffset[i] = iPosTemp-iSave[SIS.header.count];
			counter--;
			
			debug(L"\r\nSave > 2 ASSEMBLE", L"");
			debug(L"\r\nSIS.listfile.iOffset[%i] =  %x", i, SIS.listfile.iOffset[i]);
			debug(L"\r\niPosTemp =  %x", iPosTemp);

			if (counter >= 0)
			{
				
				if ( (counter+1) == SIS.header.count) 
				{
					memcpy(&aBufferTemp[iPos], &SIS.count.iCount[i], 1);
					iPos++;
				} else 
				{
					memcpy(&aBufferTemp[iPos], &SIS.listfile.iConst[iCountConstValue], 4);
					iPos+=4;

					debug(L"\r\nSIS.listfile.iOffset[%i] =  %x", i, SIS.listfile.iOffset[i]);
					memcpy(&aBufferTemp[iPos], &SIS.listfile.iOffset[i], 4);
					iPos+=4;
					
					iCountConstValue++;
				}
			} else {}

#ifdef DEBUGMODE
debug(L"\r\nCopyBuff iPos", iPos);
debug(L"\r\nCopyBuff counter = %i", counter);
debug(L"\r\nCopyBuff SIS.count.iCount = %i", SIS.count.iCount[i]);
for(int ii = 0; ii < SIS.count.iCount[i]; ii++)
{
	if (ii == 0) {debug(L"\r\n", L"");} else {}
	debug(L"%02X, ", SIS.data.aDataSave[i][ii] );
}
#endif
		} else {}
	}
	iPos = iPosTemp;
	}
		
	SIS.header.numbersize = iPos;
	
#ifdef DEBUGMODE
	debug(L"\r\nSIS.header.numbersize = %i", SIS.header.numbersize);
	debug(L"\r\niPos = %i", iPos);
	for(int i = 0; i < SIS.header.numbersize; i++)
	{
		if (i == 0) {debug(L"\r\n", L"");} else {}
		debug(L"%02X, ", aBufferTemp[i] );
	}
#endif

	return;
}// AssemblySI
	
float CSaveInfoOverlord::TimeDissambler(int iNumVector)
{
	debug(L"\r\nTime Dissambler, number vector %i", iNumVector);
	ClearErrorStatus();

	int iBufSize = SIS.count.iCount[iNumVector];
	float fltTime = 0;
	//int iPos = 0;
	offset iPosTime = 0;
	offset iPosUnkOne = 0; //cPointerUnknownOnePos
	debug(L"\r\niBufSize = %02X", iBufSize);
	
#ifdef DEBUGMODE
	for (int i = 4; i < (4+8*2); i++)
	{if (i == 4) {debug(L"\r\n", L"");} else {}
	debug(L"DataVal[%i] = %02X, ", i, SIS.data.aDataSave[iNumVector][i]);
	}
#endif
	
	for (int i = 4; i < (4+8*2); i++)
	{
		//#ifdef DEBUGMODE
		//if (i == 4) {debug(L"\r\n", L"");} else {}
		//debug(L"DataVal[%i] = %02X, ", i, SIS.data.aDataSave[iNumVector][i]);
		//#endif

		if (SIS.data.aDataSave[iNumVector][i] == cPointerTimePos)
		{
			iPosTime = SIS.data.aDataSave[iNumVector][i-1];
			debug(L"\r\nPos Time value %02X", iPosTime);
		} else {}

		if (SIS.data.aDataSave[iNumVector][i] == cPointerUnknownOnePos)
		{
			iPosUnkOne = i+1;
			debug(L"\r\nPos Unknown value %02X", iPosUnkOne);
		} else {}
	}
	iPosTime +=iPosUnkOne;
	debug(L"\r\nPos Time value %02X", iPosTime);
	if (iPosTime == 0 || iPosUnkOne == 0) {info(L"\r\nTime value not found", L""); SetErrorStatus(-0x01); return -0x01;} else {}

	unsigned short int iVal[4] = 
	{
		SIS.data.aDataSave[iNumVector][iPosTime+4],
		SIS.data.aDataSave[iNumVector][iPosTime+3],
		SIS.data.aDataSave[iNumVector][iPosTime+2],
		SIS.data.aDataSave[iNumVector][iPosTime+1]
	};
	
	debug(L"\r\nTime 1 = %02X, ", SIS.data.aDataSave[iNumVector][iPosTime+4]);
	debug(L"Time 2 = %02X, ", SIS.data.aDataSave[iNumVector][iPosTime+3]);
	debug(L"Time 3 = %02X, ", SIS.data.aDataSave[iNumVector][iPosTime+2]);
	debug(L"Time 4 = %02X", SIS.data.aDataSave[iNumVector][iPosTime+1]);

	unsigned int iExp = ((iVal[0] << 8 | iVal[1])-0x41F0) >> 8;
	debug(L"\r\niExp = %02X (%f, %i)", iExp, iExp);

	if (iExp > 11) {SetErrorStatus(-0x01); return -0x01;} else {}
	
	unsigned int iBasis = 0;
	unsigned int iBasisLow = 0;
	unsigned int iBasisHigh = 0;
	
	float iTwoVal = 0;
	float iThreeVal = 0;
	float iFourVal = 0;
		
	if (iExp > 0) 
	{
		iBasis = pow (2.0, (iExp*2-1));
		if (iVal[1] < 0x80)
		{
			iTwoVal = ((float)iVal[1]*0x2+0x10)/0xF0;
		} else
		{
			iTwoVal = ((float)iVal[1]*0x2+(((float)iVal[1]-0x80)*0x2-0x10))/0xF0;
		}
		
	} else {}
	
	if (iExp > 5) 
	{
		iBasisLow = pow (2.0, (iExp*2-1-8*1));
		iThreeVal = iBasisLow * (float)iVal[2]/0xF0;
	} else {}
	
	if (iExp > 9) 
	{
		iBasisHigh = pow (2.0, (iExp*2-1-8*2));
		iFourVal = iBasisHigh * ((float)iVal[3]*0x2+((float)iVal[3]-0x80)*2-0x10)/0xF0;
	} else {}
	
	debug(L"\r\niBasis = %02X (%i, %f)", iBasis, iBasis, iBasis);
	debug(L"\r\niBasisLow = %02X (%i, %f)", iBasisLow, iBasisLow, iBasisLow);
	debug(L"\r\niBasisHigh = %02X (%i, %f)", iBasisHigh, iBasisHigh, iBasisHigh);
	debug(L"\r\niTwoVal = %02X (%i, %f)", iTwoVal, iTwoVal, iTwoVal);
	debug(L"\r\niThreeVal = %02X (%i, %f)", iThreeVal, iThreeVal, iThreeVal);
	debug(L"\r\niFourVal = %02X (%i, %f)", iFourVal, iFourVal, iFourVal);
	
	
	
	fltTime = (float)iBasis + (float)iBasis*iTwoVal + (float)iBasisLow*iThreeVal + (float)iBasisHigh*iFourVal;
	
	debug(L"\r\niTime = %02X (%i, %f)", fltTime, fltTime, fltTime);
	debug(L"\r\nTime 1 = %02X, ", iVal[0]);
	debug(L"Time 2 = %02X, ", iVal[1]);
	debug(L"Time 3 = %02X, ", iVal[2]);
	debug(L"Time 4 = %02X", iVal[3]);
	
	return fltTime;
}

wchar_t* CSaveInfoOverlord::TimeConvector(int iTimeVal)
{
	memset(aTempTwo, 0, 32*2);
	swprintf(aTempTwo, 64, L"%i", iTimeVal);
	return &aTempTwo[0x0];
}

unsigned char* CSaveInfoOverlord::StringConvert(int iNumVector, int iLanguage)
{
	//if (iNumVector > (iFlagSaveCount)) {return -1;}
	int iSizeString = 0;
	
	for (int i = 0; i < 0x30; i++)
	{
		if ( SIS.data.aDataSave[iNumVector][SIS.count.iCount[iNumVector]-1-i] == 0)
			{
				iSizeString = SIS.data.aDataSave[iNumVector][SIS.count.iCount[iNumVector]-1-i-3];
				break;
			}
	}
	unsigned char aTempThree [64];
	memset(aTempOne, 0, 64);
	memset(aTempThree, 0, 64);
	memcpy(aTempThree, &SIS.data.aDataSave[iNumVector][SIS.count.iCount[iNumVector]-iSizeString], iSizeString);
	debug(L"\r\niSizeString=%x", iSizeString);
	
#ifdef DEBUGMODE
	debug(L"\r\naTempThree = ", L"");
	for (int i = 0; i < iSizeString; i++){debug(L"%02X, ", aTempThree[i]);}
#endif
	
unsigned char valueOne 	= 0xD0;
unsigned char valueTwo 	= 0xD1;
unsigned char space 	= 0x20;
unsigned char null	 	= 0x00;
//unsigned char aConstVal [3] = {0xD0, 0xD1, 0x20};

if (iLanguage == 1)
{
	for (int i = 0; i < (iSizeString-1); i++)
	{
		if (aTempThree[i] == valueOne)
		{
			aTempThree[i]-=0xCC;
			if (aTempThree[i+1] != valueOne && aTempThree[i+1] != valueTwo && aTempThree[i+1] != space) {aTempThree[i+1]-=0x80;} else {}
			continue;
		} else{}
		if (aTempThree[i] == valueTwo)
		{
			aTempThree[i]-=0xCD;
			if (aTempThree[i+1] != valueOne && aTempThree[i+1] != valueTwo && aTempThree[i+1] != space) {aTempThree[i+1]-=0x40;} else {}
			continue;
		}else{}
		if (aTempThree[i] == space){continue;}else{}
	}
	
	for (int i = 0, iSpace = 0; i < iSizeString; i++)
	{
		if (aTempThree[i] != space)
		{
			aTempOne[i+iSpace]=aTempThree[i];
		}
		else 
		{
			aTempOne[i]=null;
			aTempOne[i+1]=space;
			iSpace++;
		}
	}
	#ifdef DEBUGMODE
	debug(L"\r\naTempOne = ", L"");
	for (int i = 0; i < iSizeString; i++){debug(L"%02X, ", aTempOne[i]);}
	#endif

	for (int i = 0; i < iSizeString; i++)
	{
		aTempOne[63] = aTempOne[i];
		aTempOne[i] = aTempOne[i+1];
		aTempOne[i+1] = aTempOne[63];
		i++;		
	}
} else
{
	for(int i = 0; i < iSizeString; i++)
	{
		aTempOne[i*2] = aTempThree[i];
	}
	//memset(aTemp, 0, 64); // ?!
}

#ifdef DEBUGMODE
	debug(L"\r\naTempOne = ", L"");
	for (int i = 0; i < iSizeString; i++){debug(L"%02X, ", aTempOne[i]);}
#endif

return &aTempOne[0x0];
}