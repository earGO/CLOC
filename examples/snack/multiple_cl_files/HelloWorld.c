#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*  Include cloc-generated header files */
#include "hw.h"
#include "hw2.h"

int main(int argc, char* argv[]) {
	char* input1 = "Gdkkn\x1FGR@\x1FVnqkc";
	size_t strlength = strlen(input1);
	char *input = (char*) malloc_global(strlength + 1);
	char *output = (char*) malloc_global(strlength + 1);
	char *secode = (char*) malloc_global(strlength + 1);
	char *output2 = (char*) malloc_global(strlength + 1);
	memcpy(input, input1, strlength+1);

        /*
           Here we show how to initialize the kernel. It is not really 
           needed but it will make the first call go slightly faster. 
        */
        decode_init(0);

        SNK_INIT_LPARM(lparm,strlength);
	decode(input,output,lparm);
	output[strlength] = '\0';
	printf("Decoded       :%s\n",output);
	/* Show we can call multiple functions in the .cl file */
	super_encode(output,secode,lparm);
	printf("Super encoded :%s\n",secode);
	super_decode(secode,output2,lparm);
	printf("Super decoded :%s\n",output2);

        /*
            Here we show it is ok to Destroy a Kernel and call it 
            again after the Destroy.  It will just reinitialize 
            on the next call.  
        */
        decode_stop();

	/* Show we can call same function multiple times */
	decode(secode,output,lparm);
	decode(output,output2,lparm);
	printf("Decoded twice :%s\n",output2);
	free_global(output);
	free_global(secode);
	free_global(output2);
	return 0;
}
