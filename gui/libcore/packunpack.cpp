#include "packunpack.hpp"	// project

const unsigned int aConstTableCrc32 [0x100] = 
{
0x77073096, 0xEE0E612C, 0x990951BA, 0x076DC419, 0x706AF48F, 0xE963A535, 
0x9E6495A3, 0x0EDB8832, 0x79DCB8A4, 0xE0D5E91E, 0x97D2D988, 0x09B64C2B, 
0x7EB17CBD, 0xE7B82D07, 0x90BF1D91, 0x1DB71064, 0x6AB020F2, 0xF3B97148, 
0x84BE41DE, 0x1ADAD47D, 0x6DDDE4EB, 0xF4D4B551, 0x83D385C7, 0x136C9856, 
0x646BA8C0, 0xFD62F97A, 0x8A65C9EC, 0x14015C4F, 0x63066CD9, 0xFA0F3D63, 
0x8D080DF5, 0x3B6E20C8, 0x4C69105E, 0xD56041E4, 0xA2677172, 0x3C03E4D1, 
0x4B04D447, 0xD20D85FD, 0xA50AB56B, 0x35B5A8FA, 0x42B2986C, 0xDBBBC9D6, 
0xACBCF940, 0x32D86CE3, 0x45DF5C75, 0xDCD60DCF, 0xABD13D59, 0x26D930AC, 
0x51DE003A, 0xC8D75180, 0xBFD06116, 0x21B4F4B5, 0x56B3C423, 0xCFBA9599, 
0xB8BDA50F, 0x2802B89E, 0x5F058808, 0xC60CD9B2, 0xB10BE924, 0x2F6F7C87, 
0x58684C11, 0xC1611DAB, 0xB6662D3D, 0x76DC4190, 0x01DB7106, 0x98D220BC, 
0xEFD5102A, 0x71B18589, 0x06B6B51F, 0x9FBFE4A5, 0xE8B8D433, 0x7807C9A2, 
0x0F00F934, 0x9609A88E, 0xE10E9818, 0x7F6A0DBB, 0x086D3D2D, 0x91646C97, 
0xE6635C01, 0x6B6B51F4, 0x1C6C6162, 0x856530D8, 0xF262004E, 0x6C0695ED, 
0x1B01A57B, 0x8208F4C1, 0xF50FC457, 0x65B0D9C6, 0x12B7E950, 0x8BBEB8EA, 
0xFCB9887C, 0x62DD1DDF, 0x15DA2D49, 0x8CD37CF3, 0xFBD44C65, 0x4DB26158, 
0x3AB551CE, 0xA3BC0074, 0xD4BB30E2, 0x4ADFA541, 0x3DD895D7, 0xA4D1C46D, 
0xD3D6F4FB, 0x4369E96A, 0x346ED9FC, 0xAD678846, 0xDA60B8D0, 0x44042D73, 
0x33031DE5, 0xAA0A4C5F, 0xDD0D7CC9, 0x5005713C, 0x270241AA, 0xBE0B1010, 
0xC90C2086, 0x5768B525, 0x206F85B3, 0xB966D409, 0xCE61E49F, 0x5EDEF90E, 
0x29D9C998, 0xB0D09822, 0xC7D7A8B4, 0x59B33D17, 0x2EB40D81, 0xB7BD5C3B, 
0xC0BA6CAD, 0xEDB88320, 0x9ABFB3B6, 0x03B6E20C, 0x74B1D29A, 0xEAD54739, 
0x9DD277AF, 0x04DB2615, 0x73DC1683, 0xE3630B12, 0x94643B84, 0x0D6D6A3E, 
0x7A6A5AA8, 0xE40ECF0B, 0x9309FF9D, 0x0A00AE27, 0x7D079EB1, 0xF00F9344, 
0x8708A3D2, 0x1E01F268, 0x6906C2FE, 0xF762575D, 0x806567CB, 0x196C3671, 
0x6E6B06E7, 0xFED41B76, 0x89D32BE0, 0x10DA7A5A, 0x67DD4ACC, 0xF9B9DF6F, 
0x8EBEEFF9, 0x17B7BE43, 0x60B08ED5, 0xD6D6A3E8, 0xA1D1937E, 0x38D8C2C4, 
0x4FDFF252, 0xD1BB67F1, 0xA6BC5767, 0x3FB506DD, 0x48B2364B, 0xD80D2BDA, 
0xAF0A1B4C, 0x36034AF6, 0x41047A60, 0xDF60EFC3, 0xA867DF55, 0x316E8EEF, 
0x4669BE79, 0xCB61B38C, 0xBC66831A, 0x256FD2A0, 0x5268E236, 0xCC0C7795, 
0xBB0B4703, 0x220216B9, 0x5505262F, 0xC5BA3BBE, 0xB2BD0B28, 0x2BB45A92, 
0x5CB36A04, 0xC2D7FFA7, 0xB5D0CF31, 0x2CD99E8B, 0x5BDEAE1D, 0x9B64C2B0, 
0xEC63F226, 0x756AA39C, 0x026D930A, 0x9C0906A9, 0xEB0E363F, 0x72076785, 
0x05005713, 0x95BF4A82, 0xE2B87A14, 0x7BB12BAE, 0x0CB61B38, 0x92D28E9B, 
0xE5D5BE0D, 0x7CDCEFB7, 0x0BDBDF21, 0x86D3D2D4, 0xF1D4E242, 0x68DDB3F8, 
0x1FDA836E, 0x81BE16CD, 0xF6B9265B, 0x6FB077E1, 0x18B74777, 0x88085AE6, 
0xFF0F6A70, 0x66063BCA, 0x11010B5C, 0x8F659EFF, 0xF862AE69, 0x616BFFD3, 
0x166CCF45, 0xA00AE278, 0xD70DD2EE, 0x4E048354, 0x3903B3C2, 0xA7672661, 
0xD06016F7, 0x4969474D, 0x3E6E77DB, 0xAED16A4A, 0xD9D65ADC, 0x40DF0B66, 
0x37D83BF0, 0xA9BCAE53, 0xDEBB9EC5, 0x47B2CF7F, 0x30B5FFE9, 0xBDBDF21C, 
0xCABAC28A, 0x53B39330, 0x24B4A3A6, 0xBAD03605, 0xCDD70693, 0x54DE5729, 
0x23D967BF, 0xB3667A2E, 0xC4614AB8, 0x5D681B02, 0x2A6F2B94, 0xB40BBE37, 
0xC30C8EA1, 0x5A05DF1B, 0x2D02EF8D, 0x00960244	
};

CUnpackPack::CUnpackPack()
{
	ClearClass();
}
	
CUnpackPack::~CUnpackPack()
{
	ClearClass();
	aBufferOne.~vector();
	aBufferTemp.~vector();
}

vector <unsigned char> *CUnpackPack::lpGetBuffer(int numBuf)
{
	switch (numBuf)
	{
	case 1: return &aBufferOne;
	case 2: return &aBufferTemp;
	}
}

pUnionDataInfo CUnpackPack::lpGetDataInfo()
{
	return &UnionDataInfoOne;
}

int CUnpackPack::ClearClass()
{
	if (aBufferOne.capacity() > 1) {aBufferOne.clear();}
	memset(&UnionDataInfoOne, 0, sizeof(UnionDataInfo));
	iFlagDefSave = 0;
	iFlagDefSaveLang = 0;
}

unsigned int CUnpackPack::CheckCrc32 (size_t iLenFile, vector <unsigned char> aBuf)
{
	unsigned char edi = 0;
	unsigned int eax = 0xFFFFFFFF;
	unsigned int esi = 0;
	for (int i = 0x0; i < iLenFile; i++)
	{
		edi = aBuf[i];
		esi = eax;
		esi = esi & 0xFF;
		esi = esi ^ edi;
		esi-=1;
		eax = eax >> 8;
		eax = eax ^ aConstTableCrc32[esi];
	}

	return eax;
}

unsigned int CUnpackPack::CheckSum(size_t iNumByte, vector <unsigned char> aBuf)
{
	RegisterVal64 ecx, edi, buf;
	
	edi.rax = 0x0;
	ecx.rax = 0x0;
	buf.rax = 0x0;
	
	unsigned int val_z = 1;
	unsigned int val_y = 0;
	int size = 0;
	int s_15B0 = 0;
	int s_div = 0;
	int f_div = 0;
	
	size = iNumByte;
	
	s_15B0 = size/0x15B0;
	
	if (s_15B0==0)
	{
		s_div = (size - (size/0x10)*0x10);
	} else {
			s_div = (size - (s_15B0*0x15B0)) - ((size - (s_15B0*0x15B0))/0x10)*0x10;
			}

	unsigned int global_i = 0;
	for (;global_i < size;)
	{
		if (s_15B0 > 0)
		{
			for (unsigned int ba = 0, x = 0, flag = 0; ba < 0x15B0; ba++, global_i++, flag = 0)
			{
				if (ba == (16*x)){val_z+=aBuf[global_i];x++;flag = 1;}
				if (flag == 0){val_y+=val_z;val_z+=aBuf[global_i];}
				if (ba == ((16*x)-1)){val_y+=val_z;}
	
				if (ba == 0x15AF)
				{
					buf.edx_eax.edx = val_y;
					buf.edx_eax.eax = val_z;
					
					edi.rax = buf.edx_eax.edx;
					edi.rax = edi.rax*0x80078071;
					edi.rax = edi.edx_eax.edx/0x8000;
					edi.rax = edi.rax*0xffff000f;
					edi.rax = edi.rax + buf.edx_eax.edx;
					
					ecx.rax = buf.edx_eax.eax;
					ecx.rax = ecx.rax*0x80078071;
					ecx.rax = ecx.edx_eax.edx/0x8000;
					ecx.rax = ecx.rax*0xffff000f;
					ecx.rax = ecx.rax + buf.edx_eax.eax;
					val_y = edi.rax;
					val_z = ecx.rax;
				}
			}
		s_15B0--;

		}
		else
		{	
			for (unsigned int bb = 0, x = 0, flag = 0, cc = (size - ((size/0x15B0)*0x15B0)); bb < cc; bb++, flag=0, global_i++)
			{
				if (s_div > 0 && bb == ((size - ((size/0x15B0)*0x15B0)) - s_div))
				{
					for (unsigned int a = 0; a < s_div; a++, global_i++, bb++)
					{
						val_z+=aBuf[global_i];
						val_y+=val_z;
					}

				buf.edx_eax.edx = val_y;
				buf.edx_eax.eax = val_z;
				f_div=1;
				goto lia;
				}
				
				if (bb == (16*x)){val_z+=aBuf[global_i];x++;flag = 1;}
				if (flag == 0){val_y+=val_z;val_z+=aBuf[global_i];}
				if (bb == ((16*x)-1)){val_y+=val_z;}
				#define yes_yes_yes 	i_use_goto
							
			}
			lia:
			if (f_div == 0){buf.edx_eax.edx = val_y;buf.edx_eax.eax = val_z;f_div=0;}
		}
	}
	edi.rax = buf.edx_eax.edx;
	edi.rax = edi.rax*0x80078071;
	edi.rax = edi.edx_eax.edx/0x8000;
	edi.rax = edi.rax*0xffff000f;
	edi.rax = edi.rax + buf.edx_eax.edx;

	ecx.rax = buf.edx_eax.eax;
	ecx.rax = ecx.rax*0x80078071;
	ecx.rax = ecx.edx_eax.edx/0x8000;
	ecx.rax = ecx.rax*0xFFFF000F;
	ecx.rax = ecx.rax + buf.edx_eax.eax;

	buf.rax = 0x0;
	buf.i[1] = edi.i[0];
	buf.i[0] = edi.i[1];
	buf.i[3] = ecx.i[0];
	buf.i[2] = ecx.i[1];
	
	return buf.edx_eax.eax;
}

int CUnpackPack::DefineTypeFile ()
{
	iFlagDefSave = 0;
	iFlagDefSaveLang = 0;
	
	unsigned char iSaveinfo [0x4] = {0x4F, 0x53, 0x49, 0x00};
	unsigned char iSaveSlot [0x4] = {0x4F, 0x53, 0x47, 0x00};
	unsigned char iReserved [0x4] = {0x00, 0x00, 0x00, 0x01};

	if (memcmp( &aBufferOne[0x0], &iReserved[0x0], 4) != 0) return ERROR_FAILCHECKCONST;
	if (memcmp( &aBufferOne[0x4], &iSaveinfo[0x0], 4) == 0) iFlagDefSave = SAVEINFO;
	if (memcmp( &aBufferOne[0x4], &iSaveSlot[0x0], 4) == 0) iFlagDefSave = SAVESLOT;
	if (iFlagDefSave == SAVEINFO) 
	{
		if (aBufferOne[UnionDataInfoOne.data.iUnzip-2] == (0xD0 | 0xD1))
		{
			iFlagDefSaveLang = LANGRU;
		} else {return ERROR_FAILCHECKLANG;}
	}
	if (iFlagDefSave == 0) return ERROR_FAILCHECKCONST;
	return 0;
}

int CUnpackPack::CheckFileSignature(void)
{
	pUnionDataInfo Info = &UnionDataInfoOne;
	Info->data.iConst1 		= 0xDEADBEEF;
	Info->data.iConst2 		= 0xFEEDDEAF;
	Info->data.iReserved 	= 0x00000002;
	Info->data.iSignature 	= 0x5E78;
	Info->data.iLenFile 	= aBufferOne.size();
	
	if 
	(
	memcmp( &aBufferOne[Info->data.iLenFile-0x10], 	&Info->data.iConst1, 	4) 	== 0 &&
	memcmp( &aBufferOne[Info->data.iLenFile-0xC], 	&Info->data.iConst2, 	4) 	== 0 &&
	memcmp( &aBufferOne[Info->data.iLenFile-0x4], 	&Info->data.iReserved, 	4) 	== 0 &&
	memcmp( &aBufferOne[0x4], 						&Info->data.iSignature, 2) == 0
	) {} else {return ERROR_CHECKCONST;}
	
	memcpy (&Info->data.iUnzip, 	&aBufferOne[0], 						4);
	memcpy (&Info->data.iCrc32, 	&aBufferOne[Info->data.iLenFile-0x8], 	4);
	memcpy (&Info->data.iChecksum, 	&aBufferOne[Info->data.iLenFile-0x14], 	4);

	if (CheckCrc32( (Info->data.iLenFile-(0x4+0x4+0x8)), aBufferOne) != Info->data.iCrc32 ) return ERROR_CHECKCRC32;
	
	return 0;
}

int CUnpackPack::Compression()
{
	if (aBufferTemp.capacity() > 1) {aBufferTemp.clear();}
	aBufferTemp.reserve(UnionDataInfoOne.data.iUnzip+0x1A*2);
	aBufferTemp.resize(UnionDataInfoOne.data.iUnzip+0x1A*2);
	UnionDataInfoOne.data.iConst1 		= 0xDEADBEEF;
	UnionDataInfoOne.data.iConst2 		= 0xFEEDDEAF;
	UnionDataInfoOne.data.iReserved 	= 0x00000002;
	UnionDataInfoOne.data.iSignature 	= 0x5E78;
	
	z_stream stream_dec;
	memset(&stream_dec, 0, sizeof(stream_dec));
	stream_dec.next_in = &aBufferOne[0x0]; //4R+2S
	stream_dec.next_out = &aBufferTemp[0x6];
	stream_dec.zalloc = Z_NULL;
	stream_dec.zfree = Z_NULL;
	stream_dec.opaque = Z_NULL;
	stream_dec.avail_in = UnionDataInfoOne.data.iUnzip;
	stream_dec.avail_out = (UnionDataInfoOne.data.iUnzip+0x1A*2);
	int iWindowBits = -15;
		
	if (deflateInit2(&stream_dec, Z_OVERLORD_SPEED, Z_DEFLATED, iWindowBits, 8, Z_DEFAULT_STRATEGY) != Z_OK) {deflateEnd(&stream_dec); return ERROR_COMPRESS;} else {}
	deflateReset(&stream_dec);
	
	if (deflate(&stream_dec, Z_FINISH) != Z_STREAM_END) 
	{deflateEnd(&stream_dec); return ERROR_COMPRESS;} else {}
	
	memcpy(&aBufferTemp[0x0], &UnionDataInfoOne.i[0x0], 4);
	memcpy(&aBufferTemp[0x4], &UnionDataInfoOne.i[0x1C], 2);

	UnionDataInfoOne.data.iChecksum = CheckSum(stream_dec.total_in, aBufferOne);
	memcpy(&aBufferTemp[stream_dec.total_out+0x6], &UnionDataInfoOne.i[0x8], 4);
	
	UnionDataInfoOne.data.iCrc32 = CheckCrc32((stream_dec.total_out+0xA), aBufferTemp);
	
	memcpy(&aBufferTemp[stream_dec.total_out+0xA], &UnionDataInfoOne.i[0x10], 4);
	memcpy(&aBufferTemp[stream_dec.total_out+0xE], &UnionDataInfoOne.i[0x14], 4);
	memcpy(&aBufferTemp[stream_dec.total_out+0x12], &UnionDataInfoOne.i[0x4], 4);
	memcpy(&aBufferTemp[stream_dec.total_out+0x16], &UnionDataInfoOne.i[0x18], 4);

	UnionDataInfoOne.data.iLenFile = (stream_dec.total_out+0x6+0x4+0x4+0x8+0x4);
	
	deflateEnd(&stream_dec);

	aBufferOne.clear();
	aBufferOne.resize(UnionDataInfoOne.data.iLenFile);
	
	aBufferOne = aBufferTemp;
	aBufferTemp.clear();
	
	return 0;
}

int CUnpackPack::Decompression()
{
	if (aBufferTemp.capacity() > 1) {aBufferTemp.clear();}
	aBufferTemp.reserve(UnionDataInfoOne.data.iUnzip);
	aBufferTemp.resize(UnionDataInfoOne.data.iUnzip);
	
	z_stream stream_dec;
	memset(&stream_dec, 0, sizeof(stream_dec));
	stream_dec.next_in = &aBufferOne[0x6]; //4R+2S
	stream_dec.next_out = &aBufferTemp[0x0];
	stream_dec.zalloc = Z_NULL;
	stream_dec.zfree = Z_NULL;
	stream_dec.opaque = Z_NULL;
	stream_dec.avail_in = (UnionDataInfoOne.data.iLenFile-0x1A); // 4R+4CRC+8CONST12+4R+2S+4SUM=0x1A
	stream_dec.avail_out = UnionDataInfoOne.data.iUnzip;
	
	int iWindowBits = -15;
	
	if ( inflateInit2(&stream_dec, iWindowBits) != Z_OK ) return ERROR_DECOMPRESS;
	inflateReset(&stream_dec);

	if (inflate(&stream_dec, Z_NO_FLUSH) != Z_STREAM_END) return ERROR_DECOMPRESS;
	inflateEnd(&stream_dec);
	
	if ( CheckSum(UnionDataInfoOne.data.iUnzip, aBufferTemp) != UnionDataInfoOne.data.iChecksum) return ERROR_CHECKSUM;
	
	aBufferOne.clear();
	aBufferOne.resize(UnionDataInfoOne.data.iUnzip);
	
	aBufferOne = aBufferTemp;
	
	aBufferTemp.clear();
	aBufferTemp.resize(1);
	
	return 0;
}

