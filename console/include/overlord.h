#ifndef __OVERLORD_H__
#define __OVERLORD_H__

#define VERprog			"0.1"
#define VERgame			"1.4"
#define num_arg			6 		//exe, input*2, output*2, flag
#define num_filname		30

#define overload 255
#define arg_fail 1
#define len_arg_min 2
#define len_arg_max 127
#define unknown 254
#define CD 253
#define file_in 3
#define file_out 4
#define crc32_e 5
#define checksum 6

#define Z_LIA_SPEED	2

typedef union val64 rax;

union val64
{
unsigned char i[8];
long long rax;
	struct
	{
		unsigned int eax; // 4
		unsigned int edx; // 4
	} edx_eax;
};

union
{
	unsigned char i[30];
	struct
	{
		int unzip;
		int crc32_i;
		int checksim;
		int lenfile;
		short int signature;
		int const_1;
		int const_2;
		int reserved;
	} info;
} data_info;

extern int argc_lia;
extern char *argv_lia[num_arg];
extern char filename[len_arg_max];

extern int check_status;

extern char *file_input;
extern char *file_output;
extern char *file_offset;
extern int windowBits;

extern int file_in_num;
extern int file_out_num;
extern int f_comp;
extern int f_decom;
extern unsigned int table [256];


#endif // __OVERLORD_H__