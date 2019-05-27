#include "global.hpp"

#define	ERRORSAVECOUNT	-0x0011
#define	SAVECOUNT1		0x0000
#define	SAVECOUNT2		0x0001
#define	SAVECOUNT3		0x0002
#define	SAVECOUNT4		0x0003
#define	SAVECOUNT5		0x0004
#define	SAVECOUNT6		0x0005
#define	SAVECOUNT7		0x0006
#define	SAVECOUNT8		0x0007
#define	SAVECOUNT9		0x0008
#define	SAVECOUNT10		0x0009

typedef struct
{
	struct
	{
	const unsigned int reserved = 0x00000001;
	const unsigned int const02 = 0x4F534900;
	unsigned int numbersize = 0x00000000;
	const unsigned short int const01 = 0x0101;
	unsigned short int count = 0x00000000; // 0x0000xx00, 0x0082xx00
	} header;
	
	struct
	{
	unsigned int iConst[10] = {0x00000000, 0x00000001, 0x02000000, 0x03000000, 0x04000000, 0x05000000, 0x06000000, 0x07000000, 0x08000000, 0x09000000};
	unsigned int iOffset[10];
	} listfile;
	
	struct
	{
	vector <unsigned char> aDataSave [10];
	} data;
	
	struct
	{
	unsigned int iCount [10];
	} count;
	
} SaveInfoStruct, *lpSaveInfoStruct;

class CSaveInfo
{
	
public:
	CSaveInfo();
	~CSaveInfo();
	
	// public value
	SaveInfoStruct SaveInfoStructOne;

	// function
	int InitVectorSI(int num);
	int DisassemblySI(void); // Расщепляет saveinfo на отдельные записи. Вызывается явно
	void StringConvert(void);
	void ClearClass(void);
	//Get, Set
	vector <unsigned char> *lpGetBuffer(void); //

private:
using offset = unsigned int;
vector <unsigned char> aBufferTemp;
int iFlagSaveCount = 0;
offset iHead = 0xE;
offset iSave [10] = 
{
	iHead,
	iHead+0x2,
	iHead+0x6+0x8,
	iHead+0x6+0x8*2,
	iHead+0x6+0x8*3,
	iHead+0x6+0x8*4,
	iHead+0x6+0x8*5,
	iHead+0x6+0x8*6,
	iHead+0x6+0x8*7,
	iHead+0x6+0x8*8
};


};