#include <stdio.h> 		// C
#include "main.h" 		//project
#include "overlord.h" 	// project
#include "funcs.h" 		//project

int main(int argc, char **argv) 
{
	check_main(argc, argv);
	switch_lia();
	file_inspection();
	if (f_comp == 1){compression();} else {}
	if (f_decom == 1){decompression();} else {}

return 0;
}