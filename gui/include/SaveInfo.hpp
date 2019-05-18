#include "global.hpp"

typedef struct
{
	struct {
	const unsigned int reserved = 0x00000001;
	const unsigned int const02 = 0x4F534900;
	const unsigned short int const01 = 0x0101;
	unsigned short int count; // 0x0000xx00, 0x0082xx00
	} header;
	
	struct{
	unsigned int count0 = 0x00000000;
	
	const unsigned int const1 = 0x00000000;
	unsigned short int count1 = 0x0000;
	
	const unsigned int const2 = 0x02000000;
	unsigned int count2 = 0x00000000;
	const unsigned int const3 = 0x03000000;
	unsigned int count3 = 0x00000000;
	const unsigned int const4 = 0x04000000;
	unsigned int count4 = 0x00000000;
	const unsigned int const5 = 0x05000000;
	unsigned int count5 = 0x00000000;
	const unsigned int const6 = 0x06000000;
	unsigned int count6 = 0x00000000;
	const unsigned int const7 = 0x07000000;
	unsigned int count7 = 0x00000000;
	const unsigned int const8 = 0x08000000;
	unsigned int count8 = 0x00000000;
	const unsigned int const9 = 0x09000000;
	unsigned int count9 = 0x00000000;
	} listfile;
	
	struct{
	vector <char> save1;
	vector <char> save2;
	vector <char> save3;
	vector <char> save4;
	vector <char> save5;
	vector <char> save6;
	vector <char> save7;
	vector <char> save8;
	vector <char> save9;
	vector <char> save10;
	} data;

} SaveInfoStruct, *lpSaveInfoStruct;

void StringConvert();
void InitVectorSI(unsigned char *Buf, lpSaveInfoStruct Info, unsigned char num);

void DefineSaveInfo(void* aBuf, lpSaveInfoStruct Info, unsigned int lenfileinfo);

extern SaveInfoStruct SaveInfoStructOne;