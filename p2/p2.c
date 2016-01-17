#include <unistd.h>
#include <stdio.h>



void main(void){

	long page_size = sysconf (_SC_PAGESIZE);
	printf("page size %i\n",page_size);

	return;
}
