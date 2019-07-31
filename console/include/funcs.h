#ifndef __FUNCS_H__
#define __FUNCS_H__

void check_main(int argc, char *argv[num_arg]);
int error(int val);
void help_lia (void);
void switch_lia (void);
void file_inspection (void);
void decompression();
void compression(void);
int check_crc32(unsigned char *address, unsigned long int outlen);
int check_sum(unsigned char *address_file);

#endif // __FUNCS_H__