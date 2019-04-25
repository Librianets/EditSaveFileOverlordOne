#include "overlord.h"
#include "funcsmain.h"

void check_main(int argc, char *argv[num_arg])
{
	if (argc == 1){error(unknown);}
	if (argc > num_arg){error(overload);}
	for (int i = 1; i < argc; i++) 
	{
	if (strlen(argv[i])<len_arg_min){error(len_arg_min);}
	if (strlen(argv[i])>len_arg_max){error(len_arg_max);}
	}

	for (int i = 0; i < argc; i++) {argv_lia[i]=argv[i];} //copy argv
	argc_lia = argc;
	
	int a = strlen(argv_lia[0]); //temp variable
	int b = 0; //temp variable
	for (int i = a, flag = 0; flag == 0 & i > 0; i--)
	{
		if (argv_lia[0][i]=='\\')
		{
			if (b==0){b = (i+1);}
		}
	}
	if ((a-b)<5){error(unknown);}
	for (int i = b, c = 0; i <= a; i++, c++){filename[c] = argv_lia[0][i];}
}

int error(int val)
{
	switch(val)
	{
		case 1: printf("\n Error %i: not correct arguments \n", val); break; 
		case 2: printf("\n Error %i: not correct length arguments (<2) \n", val); break; 
		case 3: printf("\n Error %i: false open file input \n", val); break; 
		case 4: printf("\n Error %i: false creation(open) file output \n", val); break; 
		case 5: printf("\n Error %i: false check crc32 \n", val); break; 
		case 6: printf("\n Error %i: checksum incorrect \n", val); break; 
		case 127: printf("\n Error %i: not correct length arguments (>127) \n", val); break;
		case 253: printf("\n Error %i. Compression(-C) or decompression(-D) ?\n", val); break;
		case 254: printf("\n Error %i: Unknown command. Use -f for show help \n",val); break;
		case 255: printf("\n Error %i: many arguments \n", val); break; 
		default: printf("\n Error def \n"); break; 
	}
	exit(1);
}

void help_lia (void)
{
	printf("\n"
			"Compressed/uncompressed save data""\n"
			"Game: Overlord - Raising Hell""\n"
			"Version program: %s""\n"
			"Version game check: %s""\n", VERprog, VERgame);
	printf("\n"
			"%s -i input -o output option	""\n\n"
			"-i name 	: name file input	""\n"
			"-o name 	: name file output	""\n"
			"-C 		: compressed		""\n"
			"-D 		: uncompressed		""\n"
			"-f 		: help				""\n"
			"Sample: %s -D -i SaveInfo.osi.tzf -o SaveInfo_uncompress.osi.tzf \n"
			"Sample: %s -C -i SaveInfo_uncompress.osi.tzf -o SaveInfo.osi.tzf \n",
			filename, filename, filename);
	
	exit(1);
}

void switch_lia (void)
{
	for(int i = 1; i < argc_lia; i++)
	{
		if (argv_lia[i][0] == '-')
		{
			switch (argv_lia[i][1]) 
			{
			case 'i': file_in_num = (i+1); break; //file input
			case 'o': file_out_num = (i+1); break; //file output
			case 'C': f_comp = 1; break; // compression
			case 'D': f_decom = 1; break; //decompression
			case 'f': help_lia(); break; //help
			default: error(unknown); break;
			}
		}
	}
	
	if ( (f_comp || f_decom) == 0 ){error(CD);}
	if ( (file_in_num == 0) || (file_out_num == 0) ){error(arg_fail);}
	else {
		file_input = argv_lia[file_in_num];
		file_output = argv_lia[file_out_num];
		}
}

void file_inspection (void)
{
	FILE *fi = NULL;
	fi = fopen(file_input, "rb");
	if (fi == NULL) {error(file_in);}
	for(int i = 0; i < 16; i++){data_info.i[i]=0;} // clear union data_info
	
	fseek(fi,0x0,SEEK_END);
	data_info.info.lenfile = ftell(fi);
	fseek(fi,0x0,SEEK_SET);
	
	if (f_decom == 1)
	{
	fread(&data_info.i[0],4,1,fi);
	fseek(fi,-0x8,SEEK_END);
	fread(&data_info.i[4],4,1,fi);
	fseek(fi,-0x14,SEEK_END);
	fread(&data_info.i[8],4,1,fi);
	}

	fclose(fi);
}

void decompression()
{
	unsigned long int inlen = 0;
	unsigned long int outlen = 0;
	unsigned char *address_file_in = NULL; 
	unsigned char *address_file_out = NULL; 
	int for_f = 0;
	FILE *fi = NULL;
	FILE *fo = NULL;
	
	fi = fopen(file_input, "rb");
	fo = fopen(file_output, "wb");
	if (fi == NULL) {error(file_in);}
	if (fo == NULL) {error(file_out);}
	
	z_stream stream_dec;
	memset(&stream_dec, 0, sizeof(stream_dec));
	stream_dec.next_in = NULL;
	stream_dec.next_out = NULL;
	stream_dec.zalloc = Z_NULL;
	stream_dec.zfree = Z_NULL;
	stream_dec.opaque = Z_NULL;
	inflateInit2(&stream_dec, windowBits);
	inflateReset(&stream_dec);

	stream_dec.avail_in = (data_info.info.lenfile-0x6-0x10-0x4);
	stream_dec.avail_out = data_info.info.unzip;
	
	address_file_in = malloc(data_info.info.lenfile);
	address_file_out = malloc(data_info.info.unzip);
	memset(address_file_in, 0, data_info.info.lenfile);
	memset(address_file_out, 0, data_info.info.unzip);
	
	for (int i = 0x0; i < (data_info.info.lenfile); i++)
	{
	unsigned char var = 0;
	fseek(fi,i,SEEK_SET);
	var = fgetc(fi);
	*address_file_in=var;
	*address_file_in++;
	for_f = 1;
	}
	if (for_f == 1) {address_file_in-=(data_info.info.lenfile);for_f = 0;}
	
#ifndef crcfail
if (check_crc32(address_file_in, 0) == 1){error(crc32_e);} 
else {address_file_in+=+0x6;}
#endif
	
	stream_dec.next_in = address_file_in;
	stream_dec.next_out = address_file_out;
	int status_dec = 255;
	status_dec = inflate(&stream_dec, Z_NO_FLUSH);
	inlen = stream_dec.total_in;
	outlen = stream_dec.total_out;
	
#ifndef checksumfail
	if (check_sum(address_file_out) == 1){error(checksum);} else {}
#endif

	fseek(fi,0,SEEK_SET);
	fwrite(address_file_out, 1, data_info.info.unzip, fo);
	
	inflateEnd(&stream_dec);
	free(address_file_in);
	free(address_file_out);
	fclose(fi);
	fclose(fo);

	if (status_dec < 2) 
	{
	printf("\n"
			"- %u bytes read \n"
			"- %u bytes write \n", inlen, outlen);
	} else {printf("\n decompression unsuccess \n");}
}

void compression(void)
{
	unsigned long int inlen = 0;
	unsigned long int outlen = 0;
	unsigned char *address_file_in = NULL; 
	unsigned char *address_file_out = NULL; 
	int status_com = 255;
	int for_f = 0;
	FILE *fi = NULL;
	FILE *fo = NULL;
		
	fi = fopen(file_input, "rb");
	fo = fopen(file_output, "wb");
	if (fi == NULL) {error(file_in);}
	if (fo == NULL) {error(file_out);}
	
	z_stream stream_dec;
	memset(&stream_dec, 0, sizeof(stream_dec));
	stream_dec.next_in = NULL;
	stream_dec.next_out = NULL;
	stream_dec.zalloc = Z_NULL;
	stream_dec.zfree = Z_NULL;
	stream_dec.opaque = Z_NULL;
	
	data_info.info.unzip = data_info.info.lenfile+256;
	stream_dec.avail_in = data_info.info.lenfile;
	stream_dec.avail_out = data_info.info.unzip;
	
	address_file_in = malloc(data_info.info.lenfile);
	address_file_out = malloc(data_info.info.unzip);
	memset(address_file_in, 0, data_info.info.lenfile);
	memset(address_file_out, 0, data_info.info.unzip);

	for (int i = 0; i<(data_info.info.lenfile); i++)
	{
	unsigned char var = 0;
	fseek(fi,i,SEEK_SET);
	var = fgetc(fi);
	*address_file_in=var;
	address_file_in++;
	for_f = 1;
	}
	
	if (for_f == 1) {address_file_in-=(data_info.info.lenfile);for_f = 0;}
	address_file_out+=6;
	stream_dec.next_in = address_file_in;
	stream_dec.next_out = address_file_out;
	status_com = 255;
	
	status_com = deflateInit2(&stream_dec, Z_LIA_SPEED, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY);
	deflateReset(&stream_dec);
	//printf("%x\n", status_com);
	status_com = deflate(&stream_dec, Z_FINISH);

	address_file_out-=6;

	inlen = stream_dec.total_in;
	memcpy(address_file_out, &inlen, 4);
	outlen = stream_dec.total_out;
	address_file_out+=4;
	data_info.info.signature = 0x5E78;
	memcpy(address_file_out, &data_info.info.signature, 2);
	address_file_out-=4;
	address_file_out+=(0x6+outlen);
	if (check_sum(address_file_in) == 1){error(checksum);} else {}
	data_info.info.const_1 = 0xDEADBEEF;
	data_info.info.const_2 = 0xFEEDDEAF;
	data_info.info.reserved = 0x00000002;
	memcpy(address_file_out, &data_info.info.checksim, 4);
	address_file_out+=4;
	memcpy(address_file_out, &data_info.info.const_1, 4);
	address_file_out+=4;
	memcpy(address_file_out, &data_info.info.const_2, 4);
	address_file_out+=4;
	address_file_out-=(4+4+4+6+outlen);
	
	if (check_crc32(address_file_out, outlen) == 1) {error(crc32_e);}
	else {address_file_out+=(4+4+4+6+outlen);}
	
	memcpy(address_file_out, &data_info.info.crc32_i, 4);
	address_file_out+=4;
	
	memcpy(address_file_out, &data_info.info.reserved, 4);
	address_file_out-=(outlen+0x4+0x4+0x4+0x4+0x6);
	fseek(fi,0,SEEK_SET);	
	fwrite(address_file_out, 1, (outlen+0x4+0x4+0x4+0x4+0x6+0x4), fo);
	
	deflateEnd(&stream_dec);
	free(address_file_in);
	free(address_file_out);
	fclose(fi);
	fclose(fo);
	
	if (status_com < 2) //отредактировать
	{
	printf("\n"
			"- %u bytes read \n"
			"- %u bytes write \n", inlen, outlen);
	} else {printf("\n compression unsuccess \n");}
}

int check_crc32(unsigned char *address, unsigned long int outlen)
{
	int check_crc32_currect = 0;
	rax crc32_b;

	if (f_decom == 1)
	{
		unsigned char edi = 0;
		unsigned int eax = 0xFFFFFFFF;
		int esi;
		for (int i = 0x0; i < (data_info.info.lenfile-0x10); i++)
		{
		edi = *address;
		esi = eax;
		esi = esi & 0xFF;
		esi = esi ^ edi;
		esi-=1;
		eax = eax >> 8;
		eax = eax ^ table[esi];
		*address++;
		}
		if (eax == data_info.info.crc32_i) {check_crc32_currect = 1;} 
		else {check_crc32_currect = 0;}
	}
	
	if (f_comp == 1)
	{
		unsigned char edi = 0;
		unsigned int eax = 0xFFFFFFFF;
		int esi;
		for (int i = 0x0; i < (outlen+0x4+0x2+0x4); i++)
		{
		edi = *address;
		esi = eax;
		esi = esi & 0xFF;
		esi = esi ^ edi;
		esi-=1;
		eax = eax >> 8;
		eax = eax ^ table[esi];
		*address++;
		}
		if (eax > 0x0) {check_crc32_currect = 1; data_info.info.crc32_i = eax;} 
		else {check_crc32_currect = 0;}
	}
	
	if (check_crc32_currect == 1) {return 0;} else {return 1;}
}

int check_sum(unsigned char *address_file)
{
	if ((data_info.info.lenfile || data_info.info.unzip) == 0){return 1;}
	
	int checksum_currect = 0;
	unsigned char *hex;
	hex = address_file;
	
	rax edi; edi.rax = 0x0;
	rax ecx; ecx.rax = 0x0;
	rax buf; buf.rax = 0x0;
	
	unsigned int val_z = 1;
	unsigned int val_y = 0;
	int size = 0;
	int s_15B0 = 0;
	int s_div = 0;
	int f_div = 0;
	
	if (f_comp == 1){size = data_info.info.lenfile;}
	if (f_decom == 1){size = data_info.info.unzip;}
	
	s_15B0 = size/0x15B0;
	if (s_15B0==0)
	{
		s_div = (size - (size/0x10)*0x10);
	} else {
			s_div = (size - (s_15B0*0x15B0)) - ((size - (s_15B0*0x15B0))/0x10)*0x10;
			}
	
#ifdef DEBUG
printf("size=%x, s_15B0=%x, s_div=%x\n", size, s_15B0, s_div);
#endif
	unsigned int global_i = 0;
	for (;global_i < size;)
	{//printf("start: hex[%i]=%x\n", global_i, hex[global_i]);
		//printf("global_i=%x, size=%x\n", global_i, size);
		if (s_15B0 > 0)
		{
			for (unsigned int ba = 0, x = 0, flag = 0; ba < 0x15B0; ba++, global_i++, flag = 0)
			{
				//printf("15b: hex[%i]=%x\n", global_i, hex[global_i]);

				if (ba == (16*x)){val_z+=hex[global_i];x++;flag = 1;}
				if (flag == 0){val_y+=val_z;val_z+=hex[global_i];}
				if (ba == ((16*x)-1)){val_y+=val_z;}
				
				
				if (ba == 0x15AF)
				{
					buf.edx_eax.edx = val_y;buf.edx_eax.eax = val_z;
					//printf("val_z=%x, val_y=%x\n", val_z, val_y);
					edi.rax = buf.edx_eax.edx;
					//printf("edi.rax=%x\n",edi.rax);
					edi.rax = edi.rax*0x80078071;
					//printf("edi.rax=%x\n",edi.rax);
					edi.rax = edi.edx_eax.edx/0x8000;
					//printf("edi.rax=%x\n",edi.rax);
					edi.rax = edi.rax*0xffff000f;
					//printf("edi.rax=%x\n",edi.rax);
					edi.rax = edi.rax + buf.edx_eax.edx;
					//printf("edi.rax=%x\n",edi.rax);
					
					ecx.rax = buf.edx_eax.eax;
					//printf("ecx.rax=%x\n", ecx.rax);
					ecx.rax = ecx.rax*0x80078071;
					//printf("ecx.rax=%x\n", ecx.rax);
					ecx.rax = ecx.edx_eax.edx/0x8000;
					//printf("ecx.rax=%x\n", ecx.rax);
					ecx.rax = ecx.rax*0xffff000f;
					//printf("ecx.rax=%x\n", ecx.rax);
					ecx.rax = ecx.rax + buf.edx_eax.eax;
					//printf("ecx.rax=%x\n", ecx.rax);
					val_y = edi.rax;
					val_z = ecx.rax;
					//printf("val_z=%x\n", val_z);
					//printf("val_y=%x\n", val_y);
				}
				//printf("global_i=%x, size=%x\n", global_i, size);
			}
		//global_i+=0x15B0;
		s_15B0--;

		}
		else
		{//printf("цикл 2 val_z=%x, val_y=%x\n", val_z, val_y);
		//global_i++;
		//printf("%i\n", (size - (s_15B0*0x15B0)));
		//printf("%i\n", ((size - (s_15B0*0x15B0)) - s_div));
		
			for (unsigned int bb = 0, x = 0, flag = 0, cc = (size - ((size/0x15B0)*0x15B0)); bb < cc; bb++, flag=0, global_i++)
			{//printf("--byte=(%x), val_z=%x, val_y=%x, hex[%i]=%x\n", (cc-bb), val_z, val_y, global_i, hex[global_i]);
				
				
				
				//printf("hex[%i]=%x\n", global_i, hex[global_i]);
				//printf("cc=%x, bb=%x\n", cc, bb);
				
				
				
				if (s_div > 0 && bb == ((size - ((size/0x15B0)*0x15B0)) - s_div))
				{//printf("1byte=(%x), val_z=%x, val_y=%x, hex[%i]=%x\n", (cc-bb), val_z, val_y, global_i, hex[global_i]);
					for (unsigned int a = 0; a < s_div; a++, global_i++, bb++)
					{
						//printf("div: hex[%i]=%x\n", global_i, hex[global_i]);
						val_z+=hex[global_i];
						val_y+=val_z;
					}
					
					//printf("val_y=%x, val_z=%x\n", val_y, val_z);
				buf.edx_eax.edx = val_y;
				buf.edx_eax.eax = val_z;
				f_div=1;
				goto lia;
				}
				//printf("other: hex[%i]=%x\n", global_i, hex[global_i]);
				
				if (bb == (16*x)){val_z+=hex[global_i];x++;flag = 1;}
				//printf("00byte=(%x), val_z=%x, val_y=%x, hex[%i]=%x\n", (cc-bb), val_z, val_y, global_i, hex[global_i]);
				if (flag == 0){val_y+=val_z;val_z+=hex[global_i];}
				//printf("albyte=(%x), val_z=%x, val_y=%x, hex[%i]=%x\n", (cc-bb), val_z, val_y, global_i, hex[global_i]);
				if (bb == ((16*x)-1)){val_y+=val_z;}
				//printf("15byte=(%x), val_z=%x, val_y=%x, hex[%i]=%x\n", (cc-bb), val_z, val_y, global_i, hex[global_i]);
				#define yes_yes_yes 	i_use_goto
				
			//	//bb = bb;				
			}
			//printf("i=%x, bb=\n", global_i);
			lia:
			//printf("hex[%i]=%x\n", global_i, hex[global_i]);
			if (f_div == 0){buf.edx_eax.edx = val_y;buf.edx_eax.eax = val_z;f_div=0;}
			
		}
	}
//printf("hex[%i]=%x\n", global_i, hex[global_i]);
	//printf("\n\nbuf.edx_eax.edx=%x\n", buf.edx_eax.edx);
	//printf("buf.edx_eax.eax=%x\n", buf.edx_eax.eax);
	edi.rax = buf.edx_eax.edx;	//printf("edi.rax=%x\n", edi.rax);
	edi.rax = edi.rax*0x80078071;//printf("edi.rax=%x\n", edi.rax);
	edi.rax = edi.edx_eax.edx/0x8000;//printf("edi.rax=%x\n", edi.rax);
	edi.rax = edi.rax*0xffff000f;//printf("edi.rax=%x\n", edi.rax);
	edi.rax = edi.rax + buf.edx_eax.edx;//printf("edi.rax=%x\n", edi.rax);

	ecx.rax = buf.edx_eax.eax;//printf("ecx.rax=%x\n", ecx.rax);
	ecx.rax = ecx.rax*0x80078071;//printf("ecx.rax=%x\n", ecx.rax);
	ecx.rax = ecx.edx_eax.edx/0x8000;//printf("ecx.rax=%x\n", ecx.rax);
	ecx.rax = ecx.rax*0xffff000f;//printf("ecx.rax=%x\n", ecx.rax);
	ecx.rax = ecx.rax + buf.edx_eax.eax;//printf("ecx.rax=%x\n", ecx.rax);

	buf.rax = 0x0;
	buf.i[3] = ecx.i[0];
	buf.i[2] = ecx.i[1];
	buf.i[1] = edi.i[0];
	buf.i[0] = edi.i[1];

#ifdef DEBUG
for (int i = 0; i < 8; i++) {printf("buf.i[%i]=%x\n", i, buf.i[i]);}
printf("\n");
#endif

	if (f_comp == 1)
	{
#ifdef DEBUG
printf("buf.edx_eax.eax=%x\n", buf.edx_eax.eax);
#endif
		if (buf.edx_eax.eax > 0)
		{
			checksum_currect = 1;
			data_info.info.checksim = buf.edx_eax.eax;
		}
		else {checksum_currect = 0;}
	}
	
	if (f_decom == 1)
	{
#ifdef DEBUG
printf("data_info.info.checksim=%x\n", data_info.info.checksim);
printf("buf.edx_eax.eax=%x\n", buf.edx_eax.eax);
#endif
		if (buf.edx_eax.eax == data_info.info.checksim) {checksum_currect = 1;} 
		else {checksum_currect = 0;}
	}

	if (checksum_currect == 1) {return 0;} else {return 1;}
}