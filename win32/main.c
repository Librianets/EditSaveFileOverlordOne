#include "overlord.h"
#include "main.h"

int main(int argc, char *argv[num_arg]) 
{
	check_main(argc, argv);
	switch_lia();
	file_inspection();
	if (f_comp == 1){compression();}
	if (f_decom == 1){decompression();}

return 0;
}