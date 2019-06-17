#include <stdio.h> // C
#include <stdlib.h> // C
#include <stdint.h> // C
#include <string.h> // C
#include <ctype.h> // C
#include <sys/stat.h> // ??C
//#include <direct.h> // win32

#include <zlib.h>

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

void check_main(int argc, char *argv[num_arg]);
int error(int val);
void help_lia (void);
void switch_lia (void);
void file_inspection (void);
void decompression();
void compression(void);
int check_crc32(unsigned char *address, unsigned long int outlen);
int check_sum(unsigned char *address_file);

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

int argc_lia;
char *argv_lia[num_arg];
char filename[len_arg_max];

int check_status;

unsigned char *file_input;
unsigned char *file_output;
unsigned char *file_offset;
int windowBits;

int file_in_num;
int file_out_num;
int f_comp;
int f_decom;
int table [256];